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
#include "Helper.h"
#include "SparkInfo.h"
#include "controller/ControllerManager.h"
#include "devices/Device.h"
#include "devices/DeviceManager.h"
#include "spark_wiring_cloud.h"
#include "spark_wiring_ipaddress.h"
#include <string.h>

http_header_t headers[] = { { "Content-Type", "application/json" }, { "Accept", "*/*" }, { NULL, NULL } };

http_request_t request;
http_response_t response;

HttpClient http;

void TcpLogger::init()
{
}

void TcpLogger::logDeviceValues()
{
	IPAddress oinkWebIp(sparkInfo.oinkWeb);

	// only log if device is not in MANUAL mode
	if (oinkWebIp == IPAddress(0, 0, 0, 0))
		return;

	request.ip = oinkWebIp;
	request.port = sparkInfo.oinkWebPort;

	request.body.concat("{\"temperatures\":[");
	request.body.concat(deviceManager.getDeviceTemperatureJson());
	request.body.concat("],\"targets\":[");
	request.body.concat(controllerManager.getTargetTemperatureJson());
	request.body.concat("]}");


	request.path = "/api/logs/";
	request.path.concat(Particle.deviceID().c_str());
	request.path.concat("/");

	http.post(request, response, headers);

	request.body = "";
}

void TcpLogger::requestConfigurations()
{
	IPAddress oinkWebIp(sparkInfo.oinkWeb);

	// only log if device is not in MANUAL mode
	if (oinkWebIp == IPAddress(0, 0, 0, 0))
		return;

	request.ip = oinkWebIp;
	request.port = sparkInfo.oinkWebPort;

	request.path = "/api/configs/";
	request.path.concat(Particle.deviceID().c_str());
	request.path.concat("/request/");

	http.put(request, response, headers);

	request.body = "";
}

void TcpLogger::sendNewDevice(Device &device)
{
	if (prepareDeviceRequest(device))
	{
		http.put(request, response, headers);

		request.body = "";
	}
}

void TcpLogger::sendRemoveDevice(uint8_t& pin_nr, DeviceAddress& hw_address)
{
	Device device;

	device.pin_nr = pin_nr;
	memcpy(device.hw_address, hw_address, 8);

	if (prepareDeviceRequest(device))
	{
		http.del(request, response, headers);

		request.body = "";
	}
}

bool TcpLogger::prepareDeviceRequest(Device &device)
{
	IPAddress oinkWebIp(sparkInfo.oinkWeb);

	// Only send new device message if Oink Brew web app is known
	if (oinkWebIp == IPAddress(0, 0, 0, 0))
		return false;

	request.ip = oinkWebIp;
	request.port = sparkInfo.oinkWebPort;

	char hw_address[17];
	Helper::getBytes(device.hw_address, 8, hw_address);

	request.body.concat("{\"device_type\":");
	request.body.concat(device.type);
	request.body.concat(",\"value\":");
	request.body.concat(device.value);
	request.body.concat(",\"pin_nr\":");
	request.body.concat(device.pin_nr);
	request.body.concat(",\"hw_address\":\"");
	request.body.concat(hw_address);
	request.body.concat("\",\"offset_from_brewpi\":");
	request.body.concat(device.offset);
	request.body.concat("}");

	request.path = "/api/devices/";
	request.path.concat(Particle.deviceID().c_str());
	request.path.concat("/");

	return true;
}

