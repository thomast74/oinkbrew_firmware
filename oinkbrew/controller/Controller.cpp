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
	this->pid = NULL;
	this->heatActuator = NULL;

	this->output = 0.0;
	this->targetTemperature = 0.0;
	this->currentTemperature = 0.0;
}

Controller::~Controller()
{
}

void Controller::dispose()
{
	turnOffHeater();

	delete this->heatActuator;
	delete this->pid;
}

void Controller::setConfig(ControllerConfiguration& config)
{
	memcpy(&this->config, &config, sizeof(config));

	setTempSensor(this->config.tempSensor);
	setHeatActuator(this->config.heatActuator);

	this->pid = new PID(&currentTemperature, &output, &targetTemperature, this->config.p, this->config.i, this->config.d, PID_DIRECT);
}

ControllerConfiguration& Controller::getConfig()
{
	return this->config;
}

void Controller::process()
{
	if (pid->GetMode() == PID_MANUAL)
		return;

	Device tempSensorDevice;
	deviceManager.getDevice(this->tempSensor.pin_nr, this->tempSensor.hw_address, tempSensorDevice);
	if (tempSensorDevice.value > DEVICE_DISCONNECTED_C)
	{
		this->currentTemperature = tempSensorDevice.value;

		if (pid->Compute()) {
			doProcess();
		}
	}
}

void Controller::update()
{
	this->heatActuator->updatePwm();
}

void Controller::setTempSensor(ActingDevice activeDevice)
{
	memcpy(&this->tempSensor, &activeDevice, sizeof(ActingDevice));
}

void Controller::setHeatActuator(ActingDevice actingDevicer)
{
	this->heatActuator = new PwmActuator(actingDevicer.pin_nr, actingDevicer.hw_address, 0);
}

bool Controller::isHeaterOn()
{
	return this->heatActuator->isActive();
}

void Controller::turnOnHeater(float pwm)
{
	this->heatActuator->setPwm(pwm);
	deviceManager.setDeviceValue(this->heatActuator->getPin(), this->heatActuator->getHwAddress(), pwm);
}

void Controller::turnOffHeater()
{
	if (isHeaterOn()) {
		this->heatActuator->setPwm(0.0);
		this->heatActuator->updatePwm();

		deviceManager.setDeviceValue(this->heatActuator->getPin(), this->heatActuator->getHwAddress(), 0);
	}
}

float Controller::getTargetTemperature()
{
	return this->targetTemperature;
}

void Controller::setTargetTemperature(float target)
{
	this->targetTemperature = target;
}

PID * Controller::getPID()
{
	return this->pid;
}

int Controller::getId()
{
	return this->config.id;
}

float Controller::getOutput()
{
	return this->output;
}
