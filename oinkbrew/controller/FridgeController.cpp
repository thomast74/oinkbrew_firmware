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
#include "spark_wiring_time.h"


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

	delete this->coolActuator;
	delete this->fanActuator;
}

void FridgeController::setConfig(ControllerConfiguration& config)
{
	Controller::setConfig(config);

	this->setCoolActuator(this->config.coolActuator);
	this->setFanActuator(this->config.fanActuator);

	getPID()->SetOutputLimits(-2, 100);
	getPID()->SetMode(PID_AUTOMATIC);

	setTargetTemperature(getConfig().temperature);

	turnOnFan();
}

void FridgeController::doProcess()
{
	float output = getOutput();

	if (this->state == COOLING)
	{
		if ((millis() - this->coolingOnTime) > MIN_COOL_ON_TIME) {
			if (output >= 0 || (millis() - this->coolingOnTime) > MAX_COOL_ON_TIME) {
				setIdle();
			}
		}
	}
	else if (this->state == HEATING) {
		if (output > 0) {
			turnOnHeater(output);
		}
		else if(output < 0) {
			turnOnCooler();
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
			turnOnCooler();
		}
	}
}

void FridgeController::turnOnHeater(float pwm)
{
	Controller::turnOnHeater(pwm);

	this->state = HEATING;
}

void FridgeController::turnOnCooler()
{
	if (!this->coolActuator->isActive() && (millis() - this->coolingOffTime) > MIN_COOL_OFF_TIME) {
		turnOffHeater();

		this->coolActuator->setActive(true);
		this->coolingOnTime = millis();

		deviceManager.setDeviceValue(this->coolActuator->getPin(), this->coolActuator->getHwAddress(), 1);

		this->state = COOLING;
	}
}

void FridgeController::turnOffCooler()
{
	if (this->coolActuator->isActive()) {
		this->coolActuator->setActive(false);
		this->coolingOffTime = millis();

		deviceManager.setDeviceValue(this->coolActuator->getPin(), this->coolActuator->getHwAddress(), 0);
	}
}

void FridgeController::turnOnFan()
{
	this->fanActuator->setPwm(getConfig().fanPwm);
}

void FridgeController::turnOffFan()
{
	this->fanActuator->setPwm(LOW);
}

void FridgeController::setIdle()
{
	turnOffHeater();
	turnOffCooler();

	this->state = IDLE;
}

void FridgeController::setCoolActuator(ActingDevice CoolActuator)
{
	this->coolActuator = new DigitalActuator(CoolActuator.pin_nr, CoolActuator.hw_address, false);
}

void FridgeController::setFanActuator(ActingDevice FanActuator)
{
	this->fanActuator = new PwmActuator(FanActuator.pin_nr, FanActuator.hw_address, 0, false);
	this->fanActuator->setMinMax(LOW, HIGH);
}
