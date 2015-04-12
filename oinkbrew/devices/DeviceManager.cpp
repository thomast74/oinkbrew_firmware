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
#include "DS18B20.h"
#include "OneWire.h"
#include "DigitalActuator.h"
#include "PwmActuator.h"
#include <string.h>

ActiveDevice DeviceManager::activeDevices[MAX_DEVICES] = {};

void DeviceManager::loadDevicesFromEEPROM() {

	uint8_t no_devices = conf.getNumberDevices();
	Device devices[no_devices];

	conf.fetchDevices(devices);

	for(uint8_t i=0; i < no_devices; i++) {

		activeDevices[i].pin_nr = devices[i].hardware.pin_nr;
		memcpy(activeDevices[i].hw_address, devices[i].hardware.hw_address, 8);
		activeDevices[i].pin_nr = devices[i].hardware.pin_nr;

		if (devices[i].type == DEVICE_HARDWARE_ACTUATOR_DIGITAL) {
			DigitalActuator actuator = DigitalActuator(devices[i].hardware.pin_nr, devices[i].hardware.is_invert);
			activeDevices[i].device = &actuator;
			activeDevices[i].value = actuator.isActive() ? 1 : 0;
		}
		else if (devices[i].type == DEVICE_HARDWARE_ACTUATOR_PWM) {
			PwmActuator actuator = PwmActuator(devices[i].hardware.pin_nr);
			activeDevices[i].device = &actuator;
			activeDevices[i].value = actuator.getValue()/255*100;
		}
		else if (devices[i].type == DEVICE_HARDWARE_ONEWIRE_TEMP) {
			DS18B20 sensor = DS18B20(ONE_WIRE_PIN, devices[i].hardware.hw_address);
			activeDevices[i].device = &sensor;
			activeDevices[i].value = sensor.getTemperature();
		}
	}

	for(; no_devices < MAX_DEVICES; no_devices++) {
		conf.clear((uint8_t*) &activeDevices[no_devices], sizeof(activeDevices[no_devices]));
		activeDevices[no_devices].type = DEVICE_HARDWARE_NONE;
	}
}

void DeviceManager::readValues() {
	for(uint8_t i=0; i < MAX_DEVICES; i++) {
		if (activeDevices[i].type == DEVICE_HARDWARE_ACTUATOR_DIGITAL) {
			DigitalActuator *actuator = static_cast<DigitalActuator*>(activeDevices[i].device);
			activeDevices[i].value = actuator->isActive() ? 1 : 0;
		}
		else if (activeDevices[i].type == DEVICE_HARDWARE_ACTUATOR_PWM) {
			PwmActuator *actuator = static_cast<PwmActuator*>(activeDevices[i].device);
			activeDevices[i].value = actuator->getValue()/255*100;
		}
		else if (activeDevices[i].type == DEVICE_HARDWARE_ONEWIRE_TEMP) {
			DS18B20 *sensor = static_cast<DS18B20*>(activeDevices[i].device);
			activeDevices[i].value = sensor->getTemperature();
		}
	}
}

void DeviceManager::removeDevice(DeviceRequest& deviceRequest, char* response) {
	// check if part of any configuration
	// if yes return error

	for(uint8_t i=0;i < MAX_DEVICES; i++) {
		if (activeDevices[i].pin_nr == deviceRequest.pin_nr && Helper::matchAddress(deviceRequest.hw_address, activeDevices[i].hw_address, 8)) {
			ActiveDevice activeDevice;
			conf.clear((uint8_t*) &activeDevice, sizeof(activeDevice));

			conf.clear((uint8_t*) &activeDevices[i].device, sizeof(activeDevices[i].device));
			activeDevices[i] = activeDevice;

			conf.removeDevice(deviceRequest.pin_nr, deviceRequest.hw_address);

			strcpy(response, "OK");

			return;
		}
	}

	strcpy(response, "Device not found");
}

void DeviceManager::sendDevice(TCPClient& client, DeviceRequest& deviceRequest) {

	Device device;
	ActiveDevice active;

	conf.clear((uint8_t*) &device, sizeof(device));

	device.hardware.pin_nr = deviceRequest.pin_nr;
	memcpy(&device.hardware.hw_address, deviceRequest.hw_address, 8);

	fetchDeviceFromConfig(device);
	getDevice(device.hardware.pin_nr, device.hardware.hw_address, active);

	bool first = true;
	printDevice(client, device, active, first);

	conf.storeDevice(device);
}

void DeviceManager::searchAndSendDeviceList(TCPClient& client) {

	client.write("[");

	bool first = true;
	uint8_t slot = 0;
	Device devices[MAX_DEVICES];
	ActiveDevice actives[MAX_DEVICES];

	processActuators(client, devices, actives, slot, first);
	processOneWire(client, devices, actives, slot, first);

	client.write("]");

	memcpy(activeDevices, actives, sizeof(actives));
	conf.storeDevices(devices, slot);
}

void DeviceManager::toggleActuator(DeviceRequest& deviceRequest, char* response) {

	ActiveDevice active;

	getDevice(deviceRequest.pin_nr, deviceRequest.hw_address, active);

	if (active.type == DEVICE_HARDWARE_ACTUATOR_DIGITAL) {
		DigitalActuator *actuator = static_cast<DigitalActuator*>(active.device);
		actuator->toggle();
		strcpy(response, actuator->isActive() ? "1" : "0");
	}
	else if (active.type == DEVICE_HARDWARE_ACTUATOR_PWM) {
		PwmActuator *actuator = static_cast<PwmActuator*>(active.device);
		actuator->setValue(deviceRequest.value*2.55);
		sprintf(response, "%2.2f", ((double)actuator->getValue() / 255) * 100);
	}
}

void DeviceManager::processActuators(TCPClient& client, Device devices[], ActiveDevice actives[], uint8_t& slot, bool& first) {

	Device device;
	ActiveDevice active;

	conf.clear((uint8_t*) &device, sizeof(device));

	int8_t pin_nr;
	for (uint8_t count = 0; (pin_nr = enumerateActuatorPins(count)) >= 0; count++) {

		device.hardware.pin_nr = pin_nr;

		fetchDeviceFromConfig(device);
		getDevice(device.hardware.pin_nr, device.hardware.hw_address, active);

		if (active.type == DEVICE_HARDWARE_NONE) {
			active.pin_nr = device.hardware.pin_nr;
			active.type = device.type;
			DigitalActuator actuator = DigitalActuator(device.hardware.pin_nr, false);
			active.device = &actuator;
			active.value = 0;
		}

		if (client) {
			printDevice(client, device, active, first);
		}

		devices[slot] = device;
		actives[slot] = active;
		slot++;
	}
}

void DeviceManager::processOneWire(TCPClient& client, Device devices[], ActiveDevice actives[], uint8_t& slot, bool& first) {
	OneWire* wire = new OneWire(ONE_WIRE_PIN);

	if (wire != NULL) {

		Device device;
		ActiveDevice active;
		conf.clear((uint8_t*) &device, sizeof(device));

		device.hardware.pin_nr = ONE_WIRE_PIN;
		device.hardware.is_invert = false;

		wire->reset_search();

		while (wire->search(device.hardware.hw_address)) {

			fetchDeviceFromConfig(device);
			getDevice(device.hardware.pin_nr, device.hardware.hw_address, active);

			// if not in active devices already, add it and read initial value
			if (active.type == DEVICE_HARDWARE_NONE) {
				active.pin_nr = device.hardware.pin_nr;
				memcpy(active.hw_address, device.hardware.hw_address, 8);
				active.type = device.type;
				if (device.type == DEVICE_HARDWARE_ONEWIRE_TEMP) {
					DS18B20 sensor = DS18B20(device.hardware.pin_nr, device.hardware.hw_address);
					active.device = &sensor;
				}
				active.value = 0;
			}

			if (client) {
				printDevice(client, device, active, first);
			}

			devices[slot] = device;
			slot++;
		}
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

void DeviceManager::getDevice(uint8_t& pin_nr, DeviceAddress& hw_address, ActiveDevice& active) {
	for(uint8_t i=0;i < MAX_DEVICES; i++) {
		if (activeDevices[i].pin_nr == pin_nr && Helper::matchAddress(hw_address, activeDevices[i].hw_address, 8)) {
			memcpy(&active, &activeDevices[i], sizeof(activeDevices[i]));
			return;
		}
	}
	conf.clear((uint8_t*) &active, sizeof(active));
	active.type = DEVICE_HARDWARE_NONE;
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
	printTouple(client, "offset", device.hardware.offset, false);
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
