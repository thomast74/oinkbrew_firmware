/**
 ******************************************************************************
 * @file    DeviceManager.cpp
 * @authors Thomas Trageser
 * @version V0.1
 * @date    2015-04-03
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


#include "DeviceManager.h"
#include "../Configuration.h"
#include "../Helper.h"
#include "../Platform.h"
#include "../SparkInfo.h"
#include "../TcpLogger.h"
#include "OneWire.h"
#include "DallasTemperatureSensor.h"
#include "DigitalActuator.h"
#include "PwmActuator.h"
#include "spark_wiring.h"
#include <string.h>
#include <stddef.h>


ActiveDevice DeviceManager::activeDevices[MAX_DEVICES] = {};
short DeviceManager::registered_devices = 0;


OneWire oneWire(ONE_WIRE_PIN);
DallasTemperature sensors(&oneWire);


void DeviceManager::init() {

	// set all actuator to 0
	int8_t pin_nr;
	for (uint8_t count = 0; (pin_nr = enumerateActuatorPins(count)) >= 0; count++) {
		analogWrite(pin_nr, 0);
	}

	// Start up the OneWire Library and temp sensors library
	sensors.begin();
	sensors.setWaitForConversion(false);
	sensors.requestTemperatures();
	delay(100);
}

void DeviceManager::loadDevicesFromEEPROM()
{
	registered_devices = conf.fetchNumberDevices();
	Device devices[registered_devices];

	conf.fetchDevices(devices);

	for(short i=0; i < registered_devices; i++) {

		activeDevices[i].pin_nr = devices[i].hardware.pin_nr;
		memcpy(activeDevices[i].hw_address, devices[i].hardware.hw_address, 8);
		activeDevices[i].type = devices[i].type;
		activeDevices[i].function = devices[i].function;

		if (devices[i].type == DEVICE_HARDWARE_ACTUATOR_DIGITAL) {
			activeDevices[i].value = digitalRead(activeDevices[i].pin_nr);
		}
		else if (devices[i].type == DEVICE_HARDWARE_ACTUATOR_PWM) {
			activeDevices[i].value = analogRead(activeDevices[i].pin_nr);
		}
		else if (devices[i].type == DEVICE_HARDWARE_ONEWIRE_TEMP) {
			activeDevices[i].offset = devices[i].hardware.offset;
			activeDevices[i].value = sensors.getTempC(activeDevices[i].hw_address);
		}
	}

	for(short no_devices = registered_devices; no_devices < MAX_DEVICES; no_devices++) {
		conf.clear((uint8_t*) &activeDevices[no_devices], sizeof(activeDevices[no_devices]));
		activeDevices[no_devices].type = DEVICE_HARDWARE_NONE;
	}
}

short DeviceManager::noRegisteredDevices() {
	return registered_devices;
}

void DeviceManager::readValues() {

	for(short i=0; i < registered_devices; i++) {
		if (activeDevices[i].type == DEVICE_HARDWARE_ONEWIRE_TEMP) {

			activeDevices[i].value = sensors.getTempC(activeDevices[i].hw_address) + activeDevices[i].offset;

			if (activeDevices[i].value > DEVICE_DISCONNECTED_C) {
				activeDevices[i].lastSeen = millis();
			}
			else {
				// if no successful reading in 10 seconds remove device
				if ((millis() - activeDevices[i].lastSeen) > 10000) {
					removeDevice(activeDevices[i].pin_nr, activeDevices[i].hw_address);
				}
			}
		}
	}

	// send request for sensor data so theya re available next round in a second
	sensors.requestTemperatures();
}

bool DeviceManager::findNewDevices()
{
	bool new_device_found = false;
	uint8_t no_found_devices = 0;
	Device devices[MAX_DEVICES];
	ActiveDevice actives[MAX_DEVICES];

	// only find new devices if oinkweb is known
	if (sparkInfo.oinkWeb[0] == 0)
		return false;

	if (registered_devices == 0)
		processActuators(devices, actives, no_found_devices);

	processOneWire(devices, actives, no_found_devices);

	for(short i=0; i < no_found_devices; i++) {
		if (actives[i].newly_found) {
			if (actives[i].type == DEVICE_HARDWARE_NONE)
				continue;

			actives[i].newly_found = false;

			if (actives[i].type == DEVICE_HARDWARE_ONEWIRE_TEMP) {
				actives[i].value = sensors.getTempC(actives[i].hw_address);
				if (actives[i].value <= DEVICE_DISCONNECTED_C) {
					continue;
				}
			}

			memcpy(&activeDevices[registered_devices], &actives[i], sizeof(ActiveDevice));
			conf.storeDevice(devices[i]);
			registered_devices++;

			logger.sendNewDevice(devices[i], actives[i].value);

			new_device_found = true;
		}
	}

	return new_device_found;
}

void DeviceManager::removeDevice(DeviceRequest& deviceRequest, char* response)
{
	// check if part of any configuration
	// if yes return error

	if (removeDevice(deviceRequest.pin_nr, deviceRequest.hw_address))
		strcpy(response, "OK");
	else
		strcpy(response, "Device not found");
}

bool DeviceManager::removeDevice(uint8_t& pin_nr, DeviceAddress& hw_address)
{
	bool removed = false;
	short new_registered_devices = 0;
	ActiveDevice newActiveDevices[MAX_DEVICES];

	for(uint8_t slot=0;slot < registered_devices; slot++) {
		if (!(activeDevices[slot].pin_nr == pin_nr && Helper::matchAddress(hw_address, activeDevices[slot].hw_address, 8))) {
			newActiveDevices[new_registered_devices] = activeDevices[slot];
			new_registered_devices++;
		}
		else {
			conf.removeDevice(pin_nr, hw_address);
			removed = true;
		}
	}

	if (removed) {
		logger.sendRemoveDevice(pin_nr, hw_address);
		memcpy(activeDevices, newActiveDevices, sizeof(newActiveDevices));
		registered_devices = new_registered_devices;
	}

	return removed;
}

void DeviceManager::clearActiveDevices()
{
	uint32_t activeDevicesize = sizeof(ActiveDevice);
	registered_devices = 0;

	for(uint8_t i=0;i < MAX_DEVICES; i++) {
		conf.clear((uint8_t*)&activeDevices[i], activeDevicesize);
	}
}

void DeviceManager::sendDevice(TCPClient& client, DeviceRequest& deviceRequest) {

	Device device;
	ActiveDevice active;

	device.hardware.pin_nr = deviceRequest.pin_nr;
	memcpy(&device.hardware.hw_address, deviceRequest.hw_address, 8);

	fetchDeviceFromConfig(device);
	getDevice(device.hardware.pin_nr, device.hardware.hw_address, active);

	bool first = true;
	printDevice(client, device, active, first);

	conf.storeDevice(device);
}

void DeviceManager::searchAndSendDeviceList(TCPClient& client) {

	uint8_t slot = 0;
	Device devices[MAX_DEVICES];
	ActiveDevice actives[MAX_DEVICES];

	processActuators(devices, actives, slot);
	processOneWire(devices, actives, slot);

	registered_devices = slot;
	bool first = true;

	client.write("[");

	for(short i = 0; i < registered_devices; i++) {
		printDevice(client, devices[i], actives[i], first);
		memcpy(&activeDevices[i], &actives[i], sizeof(ActiveDevice));
	}

	client.write("]");
	client.flush();

	conf.storeDevices(devices, slot);
}

void DeviceManager::toggleActuator(DeviceRequest& deviceRequest, char* response) {

	ActiveDevice active;

	getDevice(deviceRequest.pin_nr, deviceRequest.hw_address, active);

	if (active.type == DEVICE_HARDWARE_ACTUATOR_DIGITAL) {
		DigitalActuator actuator = DigitalActuator(active.pin_nr, active.hw_address, false);
		actuator.toggle();
		strcpy(response, actuator.isActive() > 0 ? "1" : "0");
	}
	else if (active.type == DEVICE_HARDWARE_ACTUATOR_PWM) {
		PwmActuator actuator = PwmActuator(active.pin_nr, active.hw_address, deviceRequest.value*2.55, false);
		sprintf(response, "%2.2f", ((double)actuator.getPwm() / 255.0) * 100.0);
	}
}

void DeviceManager::setOffset(DeviceRequest& deviceRequest) {

	for(uint8_t i=0;i < registered_devices; i++) {
		if (activeDevices[i].pin_nr == deviceRequest.pin_nr && Helper::matchAddress(deviceRequest.hw_address, activeDevices[i].hw_address, 8)) {

			activeDevices[i].offset = deviceRequest.offset;

			String sOffset = "Set Active Offset: ";
			sOffset.concat(activeDevices[i].offset);
			Helper::serialDebug(sOffset.c_str());

			Device device;
			if (conf.fetchDevice(deviceRequest.pin_nr, deviceRequest.hw_address, device) != -1) {
				device.hardware.offset = deviceRequest.offset;

				String sOffset = "Set Device Offset: ";
				sOffset.concat(device.hardware.offset);
				Helper::serialDebug(sOffset.c_str());

				conf.storeDevice(device);
			}

			return;
		}
	}
}

void DeviceManager::setDeviceType(uint8_t& pin_nr, DeviceAddress& hw_address, DeviceType type)
{
	for(uint8_t i=0;i < registered_devices; i++) {
		if (activeDevices[i].pin_nr == pin_nr && Helper::matchAddress(hw_address, activeDevices[i].hw_address, 8)) {
			activeDevices[i].type = type;
			break;
		}
	}
}

void DeviceManager::setDeviceValue(uint8_t& pin_nr, DeviceAddress& hw_address, float value)
{
	for(uint8_t i=0;i < registered_devices; i++) {
		if (activeDevices[i].pin_nr == pin_nr && Helper::matchAddress(hw_address, activeDevices[i].hw_address, 8)) {
			activeDevices[i].value = value;
			break;
		}
	}
}

void DeviceManager::processActuators(Device devices[], ActiveDevice actives[], uint8_t& slot) {

	int8_t pin_nr;
	for (uint8_t count = 0; (pin_nr = enumerateActuatorPins(count)) >= 0; count++) {
		Device device;
		ActiveDevice active;

		device.hardware.pin_nr = pin_nr;
		conf.clear((uint8_t*)&device.hardware.hw_address, 8);

		fetchDeviceFromConfig(device);
		getDevice(device.hardware.pin_nr, device.hardware.hw_address, active);

		if (active.type == DEVICE_HARDWARE_NONE) {
			active.newly_found = true;
			active.pin_nr = device.hardware.pin_nr;
			active.type = device.type;
			active.function = device.function;
			active.value = 0;
		}

		memcpy(&devices[slot], &device, sizeof(Device));
		memcpy(&actives[slot], &active, sizeof(ActiveDevice));
		slot++;
	}
}

void DeviceManager::processOneWire(Device devices[], ActiveDevice actives[], uint8_t& slot) {

	DeviceAddress hw_address;

	oneWire.reset_search();

	while (oneWire.search(hw_address)) {

		Device device;
		ActiveDevice active;

		device.hardware.pin_nr = ONE_WIRE_PIN;
		memcpy(device.hardware.hw_address, hw_address, 8);

		fetchDeviceFromConfig(device);
		getDevice(device.hardware.pin_nr, device.hardware.hw_address, active);

		// if not in active devices already, add it and read initial value
		if (active.type == DEVICE_HARDWARE_NONE) {
			active.newly_found = true;

			active.pin_nr = device.hardware.pin_nr;
			memcpy(active.hw_address, device.hardware.hw_address, 8);

			active.type = device.type;
			active.function = device.function;
			active.value = 0;
		}

		memcpy(&devices[slot], &device, sizeof(Device));
		memcpy(&actives[slot], &active, sizeof(ActiveDevice));
		slot++;
	}
}

int8_t DeviceManager::enumerateActuatorPins(uint8_t offset)
{
    switch (offset) {
        case 0: return ACTUATOR_PIN_1;
        case 1: return ACTUATOR_PIN_2;
        case 2: return ACTUATOR_PIN_3;
        default: return -1;
    }
}

void DeviceManager::getDevice(short index, ActiveDevice& active) {
	if (index >=0 && index < MAX_DEVICES) {
		active = activeDevices[index];
	}
}

void DeviceManager::getDevice(uint8_t& pin_nr, DeviceAddress& hw_address, ActiveDevice& active)
{
	active.function = DEVICE_FUNCTION_NONE;
	active.type = DEVICE_HARDWARE_NONE;
	active.value = 0;

	for(uint8_t i=0;i < registered_devices; i++) {
		if (activeDevices[i].pin_nr == pin_nr && Helper::matchAddress(hw_address, activeDevices[i].hw_address, 8)) {
			memcpy(&active, &activeDevices[i], sizeof(ActiveDevice));
			break;
		}
	}
}

void DeviceManager::fetchDeviceFromConfig(Device& device) {
	if (conf.fetchDevice(device.hardware.pin_nr, device.hardware.hw_address, device) == -1) {
		if (device.hardware.pin_nr == ONE_WIRE_PIN) {

			device.function = DEVICE_FUNCTION_NONE;

			switch (device.hardware.hw_address[0]) {
				case DS18B20MODEL:
					device.type = DEVICE_HARDWARE_ONEWIRE_TEMP;
					break;
				default:
					device.type = DEVICE_HARDWARE_NONE;
			}
		}
		else {
			device.type = DEVICE_HARDWARE_ACTUATOR_DIGITAL;
			device.function = DEVICE_FUNCTION_NONE;
		}
		device.hardware.is_invert = false;
		device.hardware.is_deactivate = false;
		device.hardware.offset = 0.0;
	}
}

void DeviceManager::printDevice(TCPClient& client, Device& device, ActiveDevice& active, bool& first) {

	char buf[17];

	if (!first)
		client.write(",");
	else
		first = false;

	client.write('{');

	printTouple(client, "type", (int32_t)device.type, true);
	char value[10];
	sprintf(value, "%2.2f", active.value);
	printTouple(client, "value", value, false);

	client.write(",\"hardware\":{");
	printTouple(client, "pin_nr", (int32_t)device.hardware.pin_nr, true);

	sprintf(value, "%2.2f", device.hardware.offset);
	printTouple(client, "offset", value, false);
	printTouple(client, "is_invert", device.hardware.is_invert, false);
	printTouple(client, "is_deactivate", device.hardware.is_deactivate, false);

	client.write(",\"hw_address\":\"");
	Helper::getBytes(device.hardware.hw_address, 8, buf);
	client.write(buf);
	client.write('"');

	client.write("}}");
	delay(100);
}

void DeviceManager::printTouple(TCPClient& client, const char* name, const char* value, bool first) {

	if (!first)
		client.write(',');

	char tempString[32];
	sprintf(tempString, "\"%s\":\"%s\"", name, value);
	client.write(tempString);
}

void DeviceManager::printTouple(TCPClient& client, const char* name, int32_t value, bool first) {

	if (!first)
		client.write(',');

	char tempString[32];
	sprintf(tempString, "\"%s\":%ld", name, value);
	client.write(tempString);
}

void DeviceManager::printTouple(TCPClient& client, const char* name, bool value, bool first) {

	if (!first)
		client.write(',');

	char tempString[32];
	sprintf(tempString, "\"%s\":%s", name, value ? "true": "false");
	client.write(tempString);
}

const char* DeviceManager::getDeviceTemperatureJson()
{
	bool notFirst = false;
	char buf[17];
	String temperatureJson;

	for (short i = 0; i < registered_devices; i++) {
		if (activeDevices[i].type != DEVICE_HARDWARE_NONE) {

			if (notFirst) {
				temperatureJson.concat(',');
			} else {
				notFirst = true;
			}

			Helper::getBytes(activeDevices[i].hw_address, 8, buf);

			temperatureJson.concat("{\"pin_nr\":\"");
			temperatureJson.concat(activeDevices[i].pin_nr);
			temperatureJson.concat("\",\"hw_address\":\"");
			temperatureJson.concat(buf);
			temperatureJson.concat("\",\"value\":");
			temperatureJson.concat(activeDevices[i].value);
			temperatureJson.concat('}');
		}
	}

	return temperatureJson.c_str();
}
