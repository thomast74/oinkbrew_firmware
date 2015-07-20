/**
 ******************************************************************************
 * @file    TcpListener.cpp
 * @authors Thomas Trageser
 * @version V0.1
 * @date    2015-03-28
 * @brief   Oink Brew Spark Core Firmware
 ******************************************************************************
 Copyright (c) 2015 Oink Brew;  All rights reserved.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation, either
 version 3 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this program; if not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************
 */

#include "TcpListener.h"
#include "Configuration.h"
#include "devices/DeviceManager.h"
#include "controller/ControllerManager.h"
#include "controller/ControllerConfiguration.h"
#include "Helper.h"
#include "Settings.h"
#include "SparkInfo.h"
#include "spark_wiring_tcpclient.h"
#include "spark_wiring_tcpserver.h"
#include "rgbled.h"
#include <stdint.h>


#define MAX_DATA_BYTES 4096
#define ACK 6

TCPServer server = TCPServer(LOCAL_LISTENER_PORT);
TCPClient client;

void TcpListener::init()
{
	server.begin();
}

bool TcpListener::connected()
{
	bool needsScreenUpdate = false;

	if (client.connected()) {
		if (client.available()) {
			needsScreenUpdate = processRequest(client.read());
		}

		unsigned long startTime = millis();
	    while (client.available() != 0 && (millis() - startTime) < 1000) {
	    	client.read();
	    	delay(20);
	    }

	    client.stop();
	    delay(20);

	} else {
		client = server.available();
	}

	return needsScreenUpdate;
}

bool TcpListener::processRequest(char action)
{
	char response[50];

	switch (action) {
	// do nothing wrong request
	case ' ':
	case '\n':
	case '\r':
		break;
	// request one sensor data
	case 'a':
		DeviceRequest dr1;
		parseJson(&TcpListener::receiveDeviceRequest, &dr1);
		deviceManager.sendDevice(client, dr1);
		client.write(ACK);
		break;
	// request the device list
	case 'd':
		deviceManager.searchAndSendDeviceList(client);
		client.write(ACK);
		break;
	// remove device from Spark
	case 'e':
		DeviceRequest dr2;
		parseJson(&TcpListener::receiveDeviceRequest, &dr2);
		deviceManager.removeDevice(dr2, response);
		client.write(response);
		break;
	// receive new firmware
	case 'f':
		updateFirmware();
		break;
	// receive and set device mode
	case 'm':
		parseJson(&TcpListener::processSparkInfo, NULL);
		conf.storeSparkInfo();
		client.write("Ok");
		return true;
	// set offset for temp sensor
	case 'o':
		DeviceRequest dr3;
		parseJson(&TcpListener::receiveDeviceRequest, &dr3);
		deviceManager.setOffset(dr3);
		client.write(ACK);
		break;
	// add or update a current configuration
	case 'p':
		ControllerConfiguration cr1;
		parseJson(&TcpListener::receiveControllerRequest, &cr1);
		controllerManager.changeController(cr1);
		client.write(ACK);
		break;
	// remove a configuration
	case 'q':
		ControllerConfiguration cr2;
		parseJson(&TcpListener::receiveControllerRequest, &cr2);
		controllerManager.removeController(cr2.id);
		client.write(ACK);
		break;
	// reset settings
	case 'r':
		resetSettings();
		client.write("Ok");
		return true;
	// receive and process spark info
	case 's':
		parseJson(&TcpListener::processSparkInfo, NULL);
		conf.storeSparkInfo();
		client.write("Ok");
		return true;
	// toggle actuator
	case 't':
		DeviceRequest dr4;
		parseJson(&TcpListener::receiveDeviceRequest, &dr4);
		deviceManager.toggleActuator(dr4, response);
		client.write(response);
		break;
	// bootloader mode
	case '$':
		System.bootloader();
		break;
	// reset spark
	case '!':
		System.reset();
		break;
	}

	return false;
}

void TcpListener::processSparkInfo(const char * key, const char * val, void* pv)
{
	if (strcmp(key, "name") == 0)
		memcpy(&sparkInfo.name, val, strlen(val) + 1);
	else if (strcmp(key, "mode") == 0)
		sparkInfo.mode = val[0];
	else if (strcmp(key, "tempType") == 0)
		sparkInfo.tempType = val[0];
	else if (strcmp(key, "oinkweb") == 0) {
		uint8_t address[4];
		Helper::getRawIp(val, address);
		memcpy(&sparkInfo.oinkWeb, &address, 4);
	} else if (strcmp(key, "oinkwebport") == 0)
		sparkInfo.oinkWebPort = atoi(val);
	else if (strcmp(key, "datetime") == 0) {
		Time.setTime(atoi(val));
	}
}

void TcpListener::setDeviceMode(const char * key, const char * val, void* pv)
{
	if (strcmp(key, "mode") == 0) {
		sparkInfo.mode = val[0];
	}
}

void TcpListener::resetSettings()
{
	memcpy(&sparkInfo.name, "", 1);
	sparkInfo.mode = 'M';
	sparkInfo.tempType = 'C';
	sparkInfo.oinkWeb[0] = 0;
	sparkInfo.oinkWeb[1] = 0;
	sparkInfo.oinkWeb[2] = 0;
	sparkInfo.oinkWeb[3] = 0;
	sparkInfo.oinkWebPort = 80;

	conf.storeSparkInfo();
	conf.removeDevices();
	conf.removeControllers();
	deviceManager.clearActiveDevices();

	System.reset();
}

void TcpListener::receiveDeviceRequest(const char * key, const char * val, void* pv)
{
	DeviceRequest *pDeviceRequest = static_cast<DeviceRequest*>(pv);

	if (strcmp(key, "pin_nr") == 0)
		pDeviceRequest->pin_nr = atoi(val);
	else if (strcmp(key, "hw_address") == 0)
		Helper::setBytes(pDeviceRequest->hw_address, val, 8);
	else if (strcmp(key, "is_invert") == 0)
		pDeviceRequest->is_invert = strcmp(val, "1") == 0 ? true : false;
	else if (strcmp(key, "value") == 0)
		pDeviceRequest->value = atoi(val);
	else if (strcmp(key, "offset") == 0) {
		int pOffset = atoi(val);
		float offset = (float) pOffset / 10000.0000;

		String sOffset = "Offset: ";
		sOffset.concat(pOffset);
		sOffset.concat("   ");
		sOffset.concat(offset);
		Helper::serialDebug(sOffset.c_str());

		pDeviceRequest->offset = offset;
	}
}

void TcpListener::receiveControllerRequest(const char * key, const char * val, void* pv)
{
	ControllerConfiguration *pControllerRequest = static_cast<ControllerConfiguration*>(pv);

	String debug(key);
	debug.concat(":");
	debug.concat(val);
	Helper::serialDebug(debug.c_str());

	if (strcmp(key, "config_id") == 0)
		pControllerRequest->id = atoi(val);
	else if (strcmp(key, "name") == 0)
		memcpy(&pControllerRequest->name, val, strlen(val) + 1);
	else if (strcmp(key, "config_type") == 0)
		pControllerRequest->type = static_cast<ControllerType>(atoi(val));
	else if (strcmp(key, "temp_sensor") == 0)
		parseActingDeviceString(&TcpListener::parseActingDevice, &pControllerRequest->tempSensor, val);
	else if (strcmp(key, "heat_actuator") == 0)
		parseActingDeviceString(&TcpListener::parseActingDevice, &pControllerRequest->heatActuator, val);
	else if (strcmp(key, "cool_actuator") == 0)
		parseActingDeviceString(&TcpListener::parseActingDevice, &pControllerRequest->coolActuator, val);
	else if (strcmp(key, "fan_actuator") == 0)
		parseActingDeviceString(&TcpListener::parseActingDevice, &pControllerRequest->fanActuator, val);
	else if (strcmp(key, "temp_phases") == 0) {
		parseTempPhasesString(pControllerRequest->temperaturePhases, val);
	}
}

void TcpListener::parseActingDevice(ActingDevice* av, const char * key, const char * val)
{
	if (strcmp(key, "pin_nr") == 0)
		av->pin_nr = atoi(val);
	else if (strcmp(key, "hw_address") == 0)
		Helper::setBytes(av->hw_address, val, 8);
	else if (strcmp(key, "function") == 0)
		av->function = static_cast<DeviceFunction>(atoi(val));
}

void TcpListener::updateFirmware()
{
}

void TcpListener::parseJson(ParseJsonCallback fn, void* data)
{
	char key[30];
	char val[300];
	*key = 0;
	*val = 0;
	bool next = true;
	// read first open brace
	int c = readNext();
	if (c != '{') {
		return;
	}
	do {
		next = parseJsonToken(key) && parseJsonToken(val);
		if (val[0] && key[0]) {
			fn(key, val, data);
		}
	} while (next);
}

bool TcpListener::parseJsonToken(char* val)
{
	uint8_t index = 0;
	val[0] = 0;
	bool result = true;
	for (;;) // get value
			{
		int character = readNext();
		if (index == 299 || character == '}' || character == -1) {
			result = false;
			break;
		}
		if (character == ',' || character == ':') // end of value
			break;
		if (character == '"') {
			// skip spaces and apostrophes
		} else
			val[index++] = character;
	}
	val[index] = 0; // null terminate string
	return result;
}

int TcpListener::readNext()
{
	uint8_t retries = 0;
	while (client.available() == 0) {
		delay(50);
		retries++;
		if (retries >= 20) {
			return -1;
		}
	}
	return client.read();
}

void TcpListener::parseActingDeviceString(ParseActingDeviceCallback fn, ActingDevice* av, const char * data)
{
	char val[30];
	int type = 0;
	int index = 0;
	int length = strlen(data);

	for (int i=0; i < length; i++) {
		if (data[i] == ';') {
			val[index] = 0;

			if (type == 0)
				fn(av, "pin_nr", val);
			else if (type == 1)
				fn(av, "hw_address", val);

			type++;
			index = 0;
		}
		else {
			val[index] = data[i];
			index++;
		}
	}

	val[index] = 0;
	fn(av, "function", val);
}

void TcpListener::parseTempPhasesString(TemperaturePhase *tempPhases, const char * data)
{
	char val[30];
	int type = 0;
	int index = 1;
	int index_val = 0;
	int length = strlen(data);

	tempPhases[0].time = 0;
	tempPhases[0].duration = 0;
	tempPhases[0].done = false;

	for (int i=0; i < length; i++) {
		if (data[i] == ';') {
			val[index_val] = 0;

			if (type == 0)
				tempPhases[index].time = atol(val);
			else if (type == 1)
				tempPhases[index].duration = atol(val);
			else if (type == 2)
				tempPhases[index].targetTemperature = (float) atoi(val) / 1000.0000;

			type++;
			index_val = 0;
		}
		else if (data[i] == '|') {
			val[index_val] = 0;

			tempPhases[index].done = atoi(val) == 1 ? true : false;

			type = 0;
			index++;
			index_val = 0;

			if (index == MAX_PHASES)
				break;
		}
		else {
			val[index_val] = data[i];
			index_val++;
		}
	}

	if (type == 2 && index_val > 0) {
		val[index_val] = 0;
		tempPhases[index].done = atoi(val) == 1 ? true : false;
	}
}
