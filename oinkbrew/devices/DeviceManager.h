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


const int ACK = 6;


class DeviceManager {
public:
	static void printDeviceList(TCPClient& client);
private:
	static void processOneWire(TCPClient& client, bool& first);
	static void processActuators(TCPClient& client, bool& first);

	static int8_t enumOneWirePins(uint8_t offset);
	static int8_t enumerateActuatorPins(uint8_t offset);

	static void printDevice(TCPClient& client, Device& device, bool& first);
	static void printTouple(TCPClient& client, const char* name, const char* value, bool first);
	static void printTouple(TCPClient& client, const char* name, int32_t value, bool first);
	static void printTouple(TCPClient& client, const char* name, bool value, bool first);
	static void getBytes(const uint8_t* data, uint8_t len, char* buf);
};

extern DeviceManager deviceManager;

#endif /* OINKBREW_DEVICES_DEVICEMANAGER_H_ */
