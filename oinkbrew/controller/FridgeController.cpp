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

FridgeController::FridgeController(ControllerConfiguration& config)
	: Controller(config)
{
	this->state = IDLE;
	this->idleStartTime = 0;
	this->coolingOnTime = 0;
	this->coolingOffTime = 0;

	this->setCoolActuator(this->config.coolActuator);
	this->setFanActuator(this->config.fanActuator);

	pid->SetOutputLimits(-255, 255);
}

FridgeController::~FridgeController()
{
	delete this->coolActuator;
}

void FridgeController::doProcess()
{
	if (this->state == COOLING)
	{
		if ((millis() - this->coolingOnTime) > MIN_COOL_ON_TIME) {
			if (this->output >= -5 || (millis() - this->coolingOnTime) > MAX_COOL_ON_TIME) {
				setIdle();
			}
		}
	}
	else if (this->state == HEATING) {
		if (output > 5) {
			turnOnHeating();
		}
		else if(output <= 5) {
			setIdle();
		}
	}
	else if (this->state == IDLE) {
		if (this->output > 5) {
			turnOnHeating();
		}
		else if (this->output < -5) {
			turnOnCooling();
		}
	}

	checkFanActivity();
}

void FridgeController::turnOnHeating()
{
	if (this->output > 5 && this->heatActuator->getPwm() != output) {
		this->heatActuator->setPwm(output);
		this->state = HEATING;
	}
}

void FridgeController::turnOnCooling()
{
	if (this->heatActuator->isActive()) {
		this->heatActuator->setPwm(0);
	}
	if (!this->coolActuator->isActive() && (millis() - this->coolingOffTime) > MIN_COOL_OFF_TIME) {
		this->coolActuator->setActive(true);
		this->coolingOnTime = millis();
		this->idleStartTime = 0;
		this->coolingOffTime = 0;
		this->state = COOLING;
	}
}

void FridgeController::setIdle()
{
	if (this->heatActuator->isActive()) {
		this->heatActuator->setPwm(0);
	}
	if (this->coolActuator->isActive()) {
		this->coolActuator->setActive(false);
		this->coolingOffTime = millis();
		this->idleStartTime = 0;
		this->coolingOnTime = 0;
	}
	this->idleStartTime = millis();
	this->state = IDLE;
}

void FridgeController::checkFanActivity()
{
	if (this->state == IDLE) {
		if (this->fanActuator->isActive() && (millis() - this->idleStartTime) > WAIT_FAN_ON_TIME) {
			this->fanActuator->setPwm(0);
		}
	}
	else {
		if (!this->fanActuator->isActive()) {
			this->fanActuator->setPwm(125);
		}
	}
}

void FridgeController::setCoolActuator(ActingDevice CoolActuator)
{
	this->coolActuator = new DigitalActuator(CoolActuator.pin_nr, false);
}

void FridgeController::setFanActuator(ActingDevice FanActuator)
{
	this->fanActuator = new PwmActuator(FanActuator.pin_nr, 0, false);
}

void FridgeController::calculateTargetTemperatur()
{
	unsigned long now = Time.now();

	for(int i=0; i < MAX_PHASES; i++) {
		if (this->config.temperaturePhases[i].time <= now) {
			if (i > 0) {
				setTargetTemperatur(this->config.temperaturePhases[i-1].targetTemperature);
			}
		}
	}
}
