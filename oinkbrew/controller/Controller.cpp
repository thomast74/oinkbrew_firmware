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
#include "../devices/DeviceManager.h"
#include "spark_wiring_time.h"
#include <string.h>

Controller::Controller()
{
	this->output = 0;
	this->pid = NULL;
	this->targetTemperature = 0;
	this->currentTemperature = 0;
	this->heatActuator = NULL;
}

Controller::Controller(ControllerConfiguration& config)
	: Controller()
{
	this->config = config;


	setTempSensor(this->config.tempSensor);
	setHeatActuator(this->config.heatActuator);

	calculateTargetTemperatur();

	this->pid = new PID(&currentTemperature, &output, &targetTemperature,
			20.000, 1.000, -10.000,
			2.000, 0.050, 1.000,
			PID_DIRECT);
}

Controller::~Controller()
{
	delete this->pid;
	delete this->heatActuator;
}


void Controller::process()
{
	// only go on if in automatic mode
	if (sparkInfo.mode != SPARK_MODE_AUTOMATIC)
	{
		return;
	}
	else
	{
		if (pid->GetMode() == PID_MANUAL)
			pid->SetMode(PID_AUTOMATIC);
	}

	// get reading for temp sensor
	ActiveDevice tempSensorDevice;
	deviceManager.getDevice(tempSensor.pin_nr, tempSensor.hw_address, tempSensorDevice);
	currentTemperature = tempSensorDevice.value;

	// calculate output
	if (pid->Compute()) {
		// act on output
		doProcess();
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
