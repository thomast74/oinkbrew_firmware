/**
 ******************************************************************************
 * @file    TcpLogger.h
 * @authors Thomas Trageser
 * @version V0.1
 * @date    2015-04-17
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

#ifndef OINKBREW_TCPLOGGER_H_
#define OINKBREW_TCPLOGGER_H_

#include "HttpClient.h"
#include "devices/Device.h"
#include "controller/ControllerConfiguration.h"
#include <stddef.h>

class TcpLogger {
public:
	static void init();
	static void logDeviceValues();
	static void requestConfigurations();
	static void sendNewDevice(Device &device);
	static void sendRemoveDevice(uint8_t& pin_nr, DeviceAddress& hw_address);
private:
	static bool prepareDeviceRequest(Device &device);
};

extern TcpLogger logger;

#endif /* OINKBREW_TCPLOGGER_H_ */
