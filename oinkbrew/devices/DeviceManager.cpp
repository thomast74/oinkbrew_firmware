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
#include "OneWireTempSensor.h"
#include "DigitalPinActuator.h"
#include "OneWire.h"
#include "Pins.h"
#include <string.h>


void DeviceManager::sendDevice(TCPClient& client, DeviceRequest& deviceRequest) {

	Device device;
	conf.clear((uint8_t*) &device, sizeof(device));

	device.hardware.pin_nr = deviceRequest.pin_nr;
	device.hardware.is_invert = deviceRequest.is_invert;
	device.hardware.is_deactivate = false;
	memcpy(&device.hardware.address, deviceRequest.address, 8);

	if (deviceRequest.pin_nr == oneWirePin) {

		switch (device.hardware.address[0]) {
			case DS18B20MODEL:
				device.type = DEVICE_HARDWARE_ONEWIRE_TEMP;
				break;
			default:
				device.type = DEVICE_HARDWARE_NONE;
		}

		OneWire* wire = new OneWire(deviceRequest.pin_nr);

		if (device.type == DEVICE_HARDWARE_ONEWIRE_TEMP) {
			OneWireTempSensor sensor(wire, device.hardware.address, 0);
			if (sensor.init()) {
				if (!sensor.isParasitePowerMode()) {
					temperature temp = sensor.read();
					tempToString(device.value, temp, 3, 9);
				}
			}
		}
	}
	else {
		device.type = DEVICE_HARDWARE_PIN;
		DigitalPinActuator actuator(device.hardware.pin_nr, device.hardware.is_invert);
		strcpy(device.value, (actuator.isActive() ? "On" : "Off"));
	}

	bool first = true;
	printDevice(client, device, first);
}

void DeviceManager::sendDeviceList(TCPClient& client) {

	client.write("[");

	bool first = true;

	processOneWire(client, first);
	processActuators(client, first);

	client.write("]");
}

const char* DeviceManager::toggleActuator(DeviceRequest& toggleRequest) {

	DigitalPinActuator actuator(toggleRequest.pin_nr, toggleRequest.is_invert);

	return actuator.toggle() ? "On" : "Off";
}

void DeviceManager::processOneWire(TCPClient& client, bool& first) {

	int8_t pin;

	for (uint8_t count = 0; (pin = enumOneWirePins(count)) >= 0; count++) {

		OneWire* wire = new OneWire(pin);

		if (wire != NULL) {

			Device device;
			conf.clear((uint8_t*) &device, sizeof(device));

			device.hardware.pin_nr = pin;
			device.hardware.is_invert = false;
			device.hardware.is_deactivate = false;

			wire->reset_search();

			while (wire->search(device.hardware.address)) {

				switch (device.hardware.address[0]) {
					case DS18B20MODEL:
						device.type = DEVICE_HARDWARE_ONEWIRE_TEMP;
						break;
					default:
						device.type = DEVICE_HARDWARE_NONE;
				}

				if (client) {
					if (device.type == DEVICE_HARDWARE_ONEWIRE_TEMP) {
						OneWireTempSensor sensor(wire, device.hardware.address, 0);
						if (sensor.init()) {
							if (!sensor.isParasitePowerMode()) {
								temperature temp = sensor.read();
								tempToString(device.value, temp, 3, 9);
								printDevice(client, device, first);
							}
						}
					}
					else {
						printDevice(client, device, first);
					}
				}
			}
		}
	}
}

void DeviceManager::processActuators(TCPClient& client, bool& first) {

	Device device;
	conf.clear((uint8_t*) &device, sizeof(device));

	device.type = DEVICE_HARDWARE_PIN;

	int8_t pin;
	for (uint8_t count = 0; (pin = enumerateActuatorPins(count)) >= 0; count++) {

		device.hardware.pin_nr = pin;
		device.hardware.is_invert = false;
		device.hardware.is_deactivate = false;

		DigitalPinActuator actuator(device.hardware.pin_nr, device.hardware.is_invert);
		strcpy(device.value, (actuator.isActive() ? "On" : "Off"));

		if (client) {
			printDevice(client, device, first);
		}
	}
}

int8_t DeviceManager::enumOneWirePins(uint8_t offset)
{
    if (offset==0)
        return oneWirePin;
    return -1;
}

int8_t DeviceManager::enumerateActuatorPins(uint8_t offset)
{
    switch (offset) {
        case 0: return actuatorPin1;
        case 1: return actuatorPin2;
        case 2: return actuatorPin3;
        default: return -1;
    }
}

void DeviceManager::printDevice(TCPClient& client, Device& device, bool& first) {

	char buf[17];

	if (!first)
		client.write(",");
	else
		first = false;

	client.write('{');

	printTouple(client, "type", (int32_t)device.type, true);
	printTouple(client, "value", device.value, false);

	client.write(",\"hardware\":{");
	printTouple(client, "pin_nr", (int32_t)device.hardware.pin_nr, true);
	printTouple(client, "offset", device.hardware.offset, false);
	printTouple(client, "is_invert", device.hardware.is_invert, false);
	printTouple(client, "is_deactivate", device.hardware.is_deactivate, false);

	client.write(",\"hw_address\":\"");
	Helper::getBytes(device.hardware.address, 8, buf);
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
