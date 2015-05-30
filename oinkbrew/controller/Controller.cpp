/**
 ******************************************************************************
 * @file    Controller.cpp
 * @authors Thomas Trageser
 * @version V0.3
 * @date    2015-05-03
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

#include "Controller.h"
#include "../SparkInfo.h"
#include "../Helper.h"
#include "../devices/DeviceManager.h"
#include "../devices/DallasTemperatureSensor.h"
#include "spark_wiring_time.h"
#include <string.h>

Controller::Controller()
{
	this->output = 0;
	this->pid = NULL;
	this->targetTemperature = 0;
	this->currentTemperature = 0;
	this->heatActuator = NULL;

	this->pid = new PID(&currentTemperature, &output, &targetTemperature,
			4.00, 0.20, 1.00,
			1.00, 0.05, 0.25,
			OVERSHOOT, PID_DIRECT);
}

Controller::~Controller()
{
	delete this->pid;
	delete this->heatActuator;
}

int Controller::getId()
{
	return this->config.id;
}

void Controller::setConfig(ControllerConfiguration& config)
{
	memcpy(&this->config, &config, sizeof(config));

	setTempSensor(this->config.tempSensor);
	setHeatActuator(this->config.heatActuator);

	calculateTargetTemperatur();
}

ControllerConfiguration& Controller::getConfig()
{
	return this->config;
}

void Controller::process()
{
	if (pid->GetMode() == PID_MANUAL)
		pid->SetMode(PID_AUTOMATIC);

	// get reading for temp sensor
	ActiveDevice tempSensorDevice;
	deviceManager.getDevice(this->tempSensor.pin_nr, this->tempSensor.hw_address, tempSensorDevice);
	if (tempSensorDevice.value > DEVICE_DISCONNECTED_C)
	{
		this->currentTemperature = tempSensorDevice.value;

		// calculate output
		if (pid->Compute()) {
			// act on output
			doProcess();
		}
	}
}

void Controller::setTempSensor(ActingDevice TempSensor)
{
	memcpy(&tempSensor, &TempSensor, sizeof(ActingDevice));
}

void Controller::setHeatActuator(ActingDevice HeatActuator)
{
	heatActuator = new PwmActuator(HeatActuator.pin_nr, 0);
}

void Controller:: setTargetTemperatur(float PointTemperature)
{
	targetTemperature = PointTemperature;
}
