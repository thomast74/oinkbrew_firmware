/**
 ******************************************************************************
 * @file    TcpLogger.cpp
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

#include "TcpLogger.h"
#include "Configuration.h"
#include "Helper.h"
#include "SparkInfo.h"
#include "devices/Device.h"
#include "devices/DeviceManager.h"
#include "spark_wiring_ipaddress.h"
#include <string.h>


http_header_t headers[] = {
	{ "Content-Type", "application/json" },
	{ "Accept", "*/*" },
	{ NULL, NULL }
};

http_request_t request;
http_response_t response;

HttpClient http;

void TcpLogger::init() {
	//request.ip = Helper::getIp(sparkInfo.oinkWeb);
	//request.port = sparkInfo.oinkWebPort;
}

void TcpLogger::logDeviceValues() {

	// only log if device is not in MANUAL mode
	if (strcmp(reinterpret_cast<const char*>(sparkInfo.mode), "MANUAL") == 0)
		return;

	IPAddress ipFromBytes(sparkInfo.oinkWeb);
	request.ip = ipFromBytes;
	request.port = sparkInfo.oinkWebPort;

	ActiveDevice active;
	bool notFirst = false;
	short registered_deviced = deviceManager.noRegisteredDevices();
	char buf[17];

	request.body.concat('[');

	for (short i = 0; i < registered_deviced; i++) {
		deviceManager.getDevice(i, active);
		if (active.type != DEVICE_HARDWARE_NONE) {

			if (notFirst) {
				request.body.concat(',');
			} else {
				notFirst = true;
			}

			Helper::getBytes(active.hw_address, 8, buf);

			request.body.concat("{\"pin_nr\":\"");
			request.body.concat(active.pin_nr);
			request.body.concat("\",\"hw_address\":\"");
			request.body.concat(buf);
			request.body.concat("\",\"value\":");
			request.body.concat(active.value);
			request.body.concat('}');
		}
	}

	request.body.concat(']');

	request.path = "/api/spark/";
	request.path.concat(Spark.deviceID().c_str());
	request.path.concat("/logs/");

	http.put(request, response, headers);

	request.body = "";
}
