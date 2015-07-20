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

	IPAddress oinkWebIp(sparkInfo.oinkWeb);

	// only log if device is not in MANUAL mode
	if (sparkInfo.mode == SPARK_MODE_MANUAL || oinkWebIp == IPAddress(0, 0, 0, 0))
		return;

	request.ip = oinkWebIp;
	request.port = sparkInfo.oinkWebPort;

	ActiveDevice active;
	bool notFirst = false;
	short registered_devices = deviceManager.noRegisteredDevices();
	char buf[17];

	request.body.concat('[');

	for (short i = 0; i < registered_devices; i++) {
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

void TcpLogger::sendNewDevice(Device &device, float value) {

	prepareDeviceRequest(device, value);

	http.put(request, response, headers);

	request.body = "";
}

void TcpLogger::sendRemoveDevice(uint8_t& pin_nr, DeviceAddress& hw_address) {
	Device device;

	device.hardware.pin_nr = pin_nr;
	memcpy(device.hardware.hw_address, hw_address, 8);

	prepareDeviceRequest(device, 0);

	http.del(request, response, headers);

	request.body = "";
}

void TcpLogger::prepareDeviceRequest(Device &device, float value) {
	IPAddress oinkWebIp(sparkInfo.oinkWeb);

	// Only send new device message if Oink Brew web app is known
	if (oinkWebIp == IPAddress(0, 0, 0, 0))
		return;

	request.ip = oinkWebIp;
	request.port = sparkInfo.oinkWebPort;


	char hw_address[17];
	Helper::getBytes(device.hardware.hw_address, 8, hw_address);

	request.body.concat("{\"type\":");
	request.body.concat(device.type);
	request.body.concat(",\"value\":");
	request.body.concat(value);
	request.body.concat(",\"hardware\":{\"pin_nr\":");
	request.body.concat(device.hardware.pin_nr);
	request.body.concat(",\"hw_address\":\"");
	request.body.concat(hw_address);
	request.body.concat("\",\"offset\":");
	request.body.concat(device.hardware.offset);
	request.body.concat(",\"is_invert\":");
	request.body.concat(device.hardware.is_invert ? "true" : "false");
	request.body.concat(",\"is_deactivate\":");
	request.body.concat(device.hardware.is_deactivate ? "true" : "false");
	request.body.concat("}}");

	request.path = "/api/spark/";
	request.path.concat(Spark.deviceID().c_str());
	request.path.concat("/devices/");
}

