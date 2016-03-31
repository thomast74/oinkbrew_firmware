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
#include "devices/DeviceManager.h"
#include "controller/ControllerManager.h"
#include "controller/ControllerConfiguration.h"
#include "Helper.h"
#include "Settings.h"
#include "SparkInfo.h"
#include "spark_wiring_tcpclient.h"
#include "spark_wiring_tcpserver.h"
#include "spark_wiring_time.h"
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
	switch (action) {
	// set offset for temp sensor
	case 'o':
		DeviceRequest dr3;
		parseJson(&TcpListener::receiveDeviceRequest, &dr3);
		deviceManager.setOffset(dr3);
		client.write("Ok");
		delay(100);
		break;
	// add or update a current configuration
	case 'p':
		ControllerConfiguration cr1;
		parseJson(&TcpListener::receiveConfiguration, &cr1);
		controllerManager.changeController(cr1);
		client.write("Ok");
		delay(100);
		break;
	// remove a configuration
	case 'q':
		ControllerConfiguration cr2;
		parseJson(&TcpListener::receiveConfiguration, &cr2);
		controllerManager.removeController(cr2.id);
		client.write("Ok");
		delay(100);
		break;
	// reset
	case 'r':
		client.write("Ok");
		delay(100);
		System.reset();
		break;
	// receive and process spark info
	case 's':
		parseJson(&TcpListener::processDeviceInfo, NULL);
		sparkInfo.received = true;
		client.write("Ok");
		break;
	default:
		client.write("--");
	}

	return false;
}

void TcpListener::processDeviceInfo(const char * key, const char * val, void* pv)
{
	if (strcmp(key, "name") == 0)
		memcpy(&sparkInfo.name, val, strlen(val) + 1);
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

void TcpListener::receiveDeviceRequest(const char * key, const char * val, void* pv)
{
	DeviceRequest *pDeviceRequest = static_cast<DeviceRequest*>(pv);

	if (strcmp(key, "pin_nr") == 0)
		pDeviceRequest->pin_nr = atoi(val);
	else if (strcmp(key, "hw_address") == 0)
		Helper::setBytes(pDeviceRequest->hw_address, val, 8);
	else if (strcmp(key, "offset") == 0) {
		int pOffset = atoi(val);
		float offset = (float) pOffset / 10000.0000;

		String sOffset = "Offset: ";
		sOffset.concat(pOffset);
		sOffset.concat("   ");
		sOffset.concat(offset);

		pDeviceRequest->offset = offset;
	}
}

void TcpListener::receiveConfiguration(const char * key, const char * val, void* pv)
{
	ControllerConfiguration *pControllerRequest = static_cast<ControllerConfiguration*>(pv);

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
	else if (strcmp(key, "pump_1_actuator") == 0)
		parseActingDeviceString(&TcpListener::parseActingDevice, &pControllerRequest->pump1Actuator, val);
	else if (strcmp(key, "pump_2_actuator") == 0)
		parseActingDeviceString(&TcpListener::parseActingDevice, &pControllerRequest->pump2Actuator, val);

	else if (strcmp(key, "temperature") == 0)
		pControllerRequest->temperature = (float) atoi(val) / 10000.0000;

	else if (strcmp(key, "heat_pwm") == 0)
		pControllerRequest->heaterPwm = (float) atoi(val) / 10000.0000;
	else if (strcmp(key, "fan_pwm") == 0)
		pControllerRequest->fanPwm = (float) atoi(val) / 10000.0000;
	else if (strcmp(key, "pump_1_pwm") == 0)
		pControllerRequest->pump1Pwm = (float) atoi(val) / 10000.0000;
	else if (strcmp(key, "pump_2_pwm") == 0)
		pControllerRequest->pump2Pwm = (float) atoi(val) / 10000.0000;

	else if (strcmp(key, "heating_period") == 0)
		pControllerRequest->heatingPeriod = atol(val);

	else if (strcmp(key, "cooling_period") == 0)
		pControllerRequest->coolingPeriod = atol(val);
	else if (strcmp(key, "cooling_on_time") == 0)
		pControllerRequest->coolingOnTime = atol(val);
	else if (strcmp(key, "cooling_off_time") == 0)
		pControllerRequest->coolingOffTime = atol(val);

	else if (strcmp(key, "p") == 0)
		pControllerRequest->p = (float) atoi(val) / 10000.0000;
	else if (strcmp(key, "i") == 0)
		pControllerRequest->i = (float) atoi(val) / 10000.0000;
	else if (strcmp(key, "d") == 0)
		pControllerRequest->d = (float) atoi(val) / 10000.0000;
}

void TcpListener::parseActingDevice(ActingDevice* av, const char * key, const char * val)
{
	if (strcmp(key, "pin_nr") == 0)
		av->pin_nr = atoi(val);
	else if (strcmp(key, "hw_address") == 0)
		Helper::setBytes(av->hw_address, val, 8);
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
	int index = 0;
	int length = strlen(data);

	for (int i=0; i < length; i++) {
		if (data[i] == ';') {
			val[index] = 0;
			fn(av, "pin_nr", val);
			index = 0;
		}
		else {
			val[index] = data[i];
			index++;
		}
	}

	val[index] = 0;
	fn(av, "hw_address", val);
}
