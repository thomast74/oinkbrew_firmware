/**
 ******************************************************************************
 * @file    FridgeController.cpp
 * @authors Thomas Trageser
 * @version V0.3
 * @date    2015-05-05
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

#include "FridgeController.h"
#include "../Helper.h"
#include "../devices/DeviceManager.h"
#include "spark_wiring_ticks.h"


FridgeController::FridgeController(ControllerConfiguration& config)
	: Controller()
{
	this->state = IDLE;

	this->coolingOnTime = 0;
	this->coolingOffTime = 0;

	this->coolActuator = NULL;
	this->fanActuator = NULL;

	this->setConfig(config);
}

void FridgeController::dispose()
{
	Controller::dispose();

	turnOffHeater();
	turnOffCooler();
	turnOffFan();

	if (this->coolActuator)
		delete this->coolActuator;
	if (this->fanActuator)
		delete this->fanActuator;
}

void FridgeController::setConfig(ControllerConfiguration& config)
{
	Controller::setConfig(config);

	this->setCoolActuator(getConfig().coolActuator);
	this->setFanActuator(getConfig().fanActuator);

	getPID()->SetOutputLimits(-100, 100);
	getPID()->SetMode(PID_AUTOMATIC);

	setTargetTemperature(getConfig().temperature);

	turnOnFan();
}

void FridgeController::doProcess()
{
	float output = getOutput();

	if (this->state == COOLING || this->state == HEATING)
	{
		if (output > 0) {
			turnOnHeater(output);
		}
		else if(output < 0) {
			turnOnCooler(output);
		}
		else {
			setIdle();
		}
	}
	else if (this->state == IDLE) {
		if (output > 0) {
			turnOnHeater(output);
		}
		else if (output < 0) {
			turnOnCooler(output);
		}
	}
}

void FridgeController::turnOnHeater(float pwm)
{
	if (this->coolActuator->isActive() && (millis() - this->coolingOffTime) < getConfig().coolingOnPeriod)
		return;

	this->turnOffCooler();
	Controller::turnOnHeater(pwm);

	this->state = HEATING;
}

void FridgeController::turnOnCooler(float pwm)
{
	if (!this->coolActuator)
		return;

	if (!this->coolActuator->isActive() && (millis() - this->coolingOffTime) < getConfig().coolingOffPeriod)
		return;

	turnOffHeater();

	this->coolActuator->setPwm(pwm);
	this->coolingOnTime = millis();

	deviceManager.setDeviceValue(this->coolActuator->getPin(), this->coolActuator->getHwAddress(), 1);

	this->state = COOLING;
}

void FridgeController::turnOffCooler()
{
	if (this->coolActuator->isActive() && this->coolActuator) {
		this->coolActuator->setPwm(0);
		this->coolingOffTime = millis();

		deviceManager.setDeviceValue(this->coolActuator->getPin(), this->coolActuator->getHwAddress(), 0);
	}
}

void FridgeController::turnOnFan()
{
	if (this->fanActuator) {
		this->fanActuator->setPwm(getConfig().fanPwm);
	}
}

void FridgeController::turnOffFan()
{
	if (this->fanActuator) {
		this->fanActuator->setPwm(0);
	}
}

void FridgeController::setIdle()
{
	turnOffHeater();
	turnOffCooler();

	this->state = IDLE;
}

void FridgeController::setCoolActuator(ActingDevice CoolActuator)
{
	if (CoolActuator.pin_nr != 0 || !Helper::matchAddress(CoolActuator.hw_address, DEVICE_ADDRESS_EMPTY, 8)) {
		this->coolActuator = new PwmActuator(CoolActuator.pin_nr, CoolActuator.hw_address, 0, getConfig().coolingOnPeriod);
	}
}

void FridgeController::setFanActuator(ActingDevice FanActuator)
{
	if (FanActuator.pin_nr != 0 || !Helper::matchAddress(FanActuator.hw_address, DEVICE_ADDRESS_EMPTY, 8)) {
		this->fanActuator = new PwmActuator(FanActuator.pin_nr, FanActuator.hw_address, 0, getConfig().heatingPeriod, false);
	}
}
