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

Device DeviceManager::activeDevices[MAX_DEVICES] = { };
short DeviceManager::registered_devices = 0;

OneWire oneWire(ONE_WIRE_PIN);
DallasTemperature sensors(&oneWire);

void DeviceManager::init()
{
	// initialise actuator pins
	int8_t pin_nr;
	for (uint8_t count = 0; (pin_nr = enumerateActuatorPins(count)) >= 0; count++) {
		pinMode(pin_nr, OUTPUT);
		digitalWrite(pin_nr, 0);
	}

	// Start up the OneWire Library and temp sensors library
	sensors.begin();
	sensors.setWaitForConversion(false);
	sensors.requestTemperatures();
	delay(100);
}

void DeviceManager::readValues()
{
	for (short i = 0; i < registered_devices; i++) {
		if (activeDevices[i].type == DEVICE_HARDWARE_ONEWIRE_TEMP) {

			activeDevices[i].value = sensors.getTempC(activeDevices[i].hw_address) + activeDevices[i].offset;

			if (activeDevices[i].value > DEVICE_DISCONNECTED_C) {
				activeDevices[i].lastSeen = millis();
			} else {
				// if no successful reading in 60 seconds remove device
				if ((millis() - activeDevices[i].lastSeen) > 60000) {
					removeDevice(activeDevices[i].pin_nr, activeDevices[i].hw_address);
				}
			}
		}
	}

	// send request for sensor data so they are available next round in a second
	sensors.requestTemperatures();
}

bool DeviceManager::findNewDevices()
{
	bool new_device_found = false;
	uint8_t no_found_devices = 0;
	Device devices[MAX_DEVICES];

	// only find new devices if oinkweb is known
	if (sparkInfo.oinkWeb[0] == 0)
		return false;

	if (registered_devices == 0)
		processActuators(devices, no_found_devices);

	processOneWire(devices, no_found_devices);

	for (short i = 0; i < no_found_devices; i++) {
		if (devices[i].newly_found) {
			if (devices[i].type == DEVICE_HARDWARE_NONE)
				continue;

			devices[i].newly_found = false;

			if (devices[i].type == DEVICE_HARDWARE_ONEWIRE_TEMP) {
				devices[i].value = sensors.getTempC(devices[i].hw_address);
				if (devices[i].value <= DEVICE_DISCONNECTED_C) {
					continue;
				}
			}

			memcpy(&activeDevices[registered_devices], &devices[i], sizeof(Device));
			registered_devices++;

			logger.sendNewDevice(devices[i]);

			new_device_found = true;
		}
	}

	return new_device_found;
}

void DeviceManager::clearDevices()
{
	uint32_t devicesize = sizeof(Device);
	registered_devices = 0;

	for (uint8_t i = 0; i < MAX_DEVICES; i++) {
		memset(&activeDevices[i], 0, devicesize);
	}
}

bool DeviceManager::removeDevice(uint8_t& pin_nr, DeviceAddress& hw_address)
{
	bool removed = false;
	short new_registered_devices = 0;
	Device newActiveDevices[MAX_DEVICES];

	for(uint8_t slot=0;slot < registered_devices; slot++) {
		if (!(activeDevices[slot].pin_nr == pin_nr && Helper::matchAddress(hw_address, activeDevices[slot].hw_address, 8))) {
			newActiveDevices[new_registered_devices] = activeDevices[slot];
			new_registered_devices++;
		}
		else {
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

void DeviceManager::setOffset(DeviceRequest& deviceRequest)
{
	for (uint8_t i = 0; i < registered_devices; i++) {
		if (activeDevices[i].pin_nr == deviceRequest.pin_nr && Helper::matchAddress(deviceRequest.hw_address, activeDevices[i].hw_address, 8)) {
			activeDevices[i].offset = deviceRequest.offset;
			return;
		}
	}
}

void DeviceManager::setDeviceValue(uint8_t& pin_nr, DeviceAddress& hw_address, float value)
{
	for (uint8_t i = 0; i < registered_devices; i++) {
		if (activeDevices[i].pin_nr == pin_nr && Helper::matchAddress(hw_address, activeDevices[i].hw_address, 8)) {
			activeDevices[i].value = value;
			return;
		}
	}
}

void DeviceManager::processActuators(Device devices[], uint8_t& slot)
{
	int8_t pin_nr;
	for (uint8_t count = 0; (pin_nr = enumerateActuatorPins(count)) >= 0;
			count++) {
		Device device;

		device.pin_nr = pin_nr;

		getDevice(device.pin_nr, device.hw_address, device);

		if (device.type == DEVICE_HARDWARE_NONE) {
			device.newly_found = true;
			device.type = DEVICE_HARDWARE_ACTUATOR_DIGITAL;
			device.value = 0;
		}

		memcpy(&devices[slot], &device, sizeof(Device));
		slot++;
	}
}

void DeviceManager::processOneWire(Device devices[], uint8_t& slot)
{
	DeviceAddress hw_address;

	oneWire.reset_search();

	while (oneWire.search(hw_address)) {

		Device device;
		Device active;

		device.pin_nr = ONE_WIRE_PIN;
		memcpy(device.hw_address, hw_address, 8);

		getDevice(device.pin_nr, device.hw_address, active);

		// if not in active devices already, add it and read initial value
		if (active.type == DEVICE_HARDWARE_NONE) {
			active.newly_found = true;

			active.pin_nr = device.pin_nr;
			memcpy(active.hw_address, device.hw_address, 8);

			active.type = device.type;
			active.value = 0;
		}

		memcpy(&devices[slot], &device, sizeof(Device));
		slot++;
	}
}

int8_t DeviceManager::enumerateActuatorPins(uint8_t offset)
{
	switch (offset) {
	case 0:
		return ACTUATOR_PIN_1;
	case 1:
		return ACTUATOR_PIN_2;
	case 2:
		return ACTUATOR_PIN_3;
	default:
		return -1;
	}
}

void DeviceManager::getDevice(uint8_t& pin_nr, DeviceAddress& hw_address, Device& active)
{
	active.type = DEVICE_HARDWARE_NONE;
	active.value = 0;

	for (uint8_t i = 0; i < registered_devices; i++) {
		if (activeDevices[i].pin_nr == pin_nr && Helper::matchAddress(hw_address, activeDevices[i].hw_address, 8)) {
			memcpy(&active, &activeDevices[i], sizeof(Device));
			break;
		}
	}
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
