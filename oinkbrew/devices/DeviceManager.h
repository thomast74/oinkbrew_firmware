/**
 ******************************************************************************
 * @file    DeviceManager.h
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


#ifndef OINKBREW_DEVICES_DEVICEMANAGER_H_
#define OINKBREW_DEVICES_DEVICEMANAGER_H_

#include "Device.h"
#include "spark_wiring_tcpclient.h"


#define INVALID_TEMP -127.00000

const short MAX_DEVICES = 16;


struct DeviceRequest {
	uint8_t pin_nr;
	DeviceAddress hw_address;
	bool is_invert;
	uint8_t value;
};


class DeviceManager {
private:
	static ActiveDevice activeDevices[MAX_DEVICES];
	static short registered_devices;
public:
	static void init();
	static void loadDevicesFromEEPROM();
	static short noRegisteredDevices();
	static void getDevice(short index, ActiveDevice& active);
	static void getDevice(uint8_t& pin_nr, DeviceAddress& hw_address, ActiveDevice& active);
	static void readValues();

	static bool removeDevice(uint8_t& pin_nr, DeviceAddress& hw_address);
	static void removeDevice(DeviceRequest& deviceRequest, char* response);

	static void sendDevice(TCPClient& client, DeviceRequest& deviceRequest);
	static void searchAndSendDeviceList(TCPClient& client);
	static void toggleActuator(DeviceRequest& deviceRequest, char* response);
private:
	static void processActuators(TCPClient& client, Device devices[], ActiveDevice activeDevices[], uint8_t& slot, bool& first);
	static void processOneWire(TCPClient& client, Device devices[], ActiveDevice activeDevices[], uint8_t& slot, bool& first);

	static void fetchDeviceFromConfig(Device& device);

	static int8_t enumerateActuatorPins(uint8_t offset);

	static void printDevice(TCPClient& client, Device& device, ActiveDevice& active, bool& first);
	static void printTouple(TCPClient& client, const char* name, const char* value, bool first);
	static void printTouple(TCPClient& client, const char* name, int32_t value, bool first);
	static void printTouple(TCPClient& client, const char* name, bool value, bool first);
};

extern DeviceManager deviceManager;

#endif /* OINKBREW_DEVICES_DEVICEMANAGER_H_ */
