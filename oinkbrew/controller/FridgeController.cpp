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
	this->idleStartTime = 0;
	this->coolingOnTime = 0;
	this->coolingOffTime = 0;
	this->coolActuator = NULL;
	this->fanActuator = NULL;
	this->until = 0;

	this->setConfig(config);

	pid->SetOutputLimits(-2, 100);
}

FridgeController::~FridgeController()
{
}

void FridgeController::setConfig(ControllerConfiguration& config)
{
	Controller::setConfig(config);

	this->setCoolActuator(this->config.coolActuator);
	this->setFanActuator(this->config.fanActuator);
}

int FridgeController::doProcess()
{
	if (this->state == COOLING)
	{
		if ((millis() - this->coolingOnTime) > MIN_COOL_ON_TIME) {
			if (this->output >= 0 || (millis() - this->coolingOnTime) > MAX_COOL_ON_TIME) {
				setIdle();
			}
		}
	}
	else if (this->state == HEATING) {
		if (this->output > 0) {
			turnOnHeating();
		}
		else if(this->output < 0) {
			setIdle();
		}
	}
	else if (this->state == IDLE) {
		if (this->output > 0) {
			turnOnHeating();
		}
		else if (this->output < 0) {
			turnOnCooling();
		}
	}

	checkFanActivity();

	if (this->until < Time.now()) {
		return this->calculateTargetTemperature();
	}

	return 0;
}

void FridgeController::update()
{
	this->heatActuator->updatePwm();
}

void FridgeController::dispose()
{
	this->heatActuator->setPwm(0);
	deviceManager.setDeviceValue(this->heatActuator->getPin(), this->heatActuator->getHwAddress(), 0);
	this->heatActuator->updatePwm();

	this->coolActuator->setActive(false);
	deviceManager.setDeviceValue(this->coolActuator->getPin(), this->coolActuator->getHwAddress(), 0);

	this->fanActuator->setPwm(0);
	deviceManager.setDeviceValue(this->coolActuator->getPin(), this->coolActuator->getHwAddress(), 0);

	delete this->heatActuator;
	delete this->coolActuator;
	delete this->fanActuator;
}

void FridgeController::turnOnHeating()
{
	this->heatActuator->setPwm(output);
	deviceManager.setDeviceValue(this->heatActuator->getPin(), this->heatActuator->getHwAddress(), output);
	this->state = HEATING;
}

void FridgeController::turnOnCooling()
{
	if (this->heatActuator->isActive()) {
		this->heatActuator->setPwm(0);
		deviceManager.setDeviceValue(this->heatActuator->getPin(), this->heatActuator->getHwAddress(), 0);
	}

	if (!this->coolActuator->isActive() && (millis() - this->coolingOffTime) > MIN_COOL_OFF_TIME) {
		this->coolActuator->setActive(true);
		deviceManager.setDeviceValue(this->coolActuator->getPin(), this->coolActuator->getHwAddress(), 1);
		this->coolingOnTime = millis();
		this->idleStartTime = 0;
		this->coolingOffTime = 0;
		this->state = COOLING;
		Helper::serialDebug("Cooling turned on");
	}
}

void FridgeController::setIdle()
{
	if (this->heatActuator->isActive()) {
		this->heatActuator->setPwm(0);
		deviceManager.setDeviceValue(this->heatActuator->getPin(), this->heatActuator->getHwAddress(), 0);
	}
	if (this->coolActuator->isActive()) {
		this->coolActuator->setActive(false);
		deviceManager.setDeviceValue(this->coolActuator->getPin(), this->coolActuator->getHwAddress(), 0);
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
		if (this->fanActuator->getPwm() != FAN_LOW && (millis() - this->idleStartTime) > WAIT_FAN_ON_TIME) {
			this->fanActuator->setPwm(FAN_LOW);
			deviceManager.setDeviceValue(this->fanActuator->getPin(), this->fanActuator->getHwAddress(), FAN_LOW);
		}
	}
	else {
		if (this->fanActuator->getPwm() != FAN_HIGH) {
			this->fanActuator->setPwm(FAN_HIGH);
			deviceManager.setDeviceValue(this->fanActuator->getPin(), this->fanActuator->getHwAddress(), FAN_HIGH);
		}
	}
}

void FridgeController::setCoolActuator(ActingDevice CoolActuator)
{
	Helper::serialDebug("set Cool Actuator", false);
	Helper::serialDebug(CoolActuator.pin_nr);

	this->coolActuator = new DigitalActuator(CoolActuator.pin_nr, CoolActuator.hw_address, false);
	deviceManager.setDeviceType(CoolActuator.pin_nr, CoolActuator.hw_address, DEVICE_HARDWARE_ACTUATOR_DIGITAL);
}

void FridgeController::setFanActuator(ActingDevice FanActuator)
{
	Helper::serialDebug("set Fan Actuator", false);
	Helper::serialDebug(FanActuator.pin_nr);

	this->fanActuator = new PwmActuator(FanActuator.pin_nr, FanActuator.hw_address, 0, false);
	this->fanActuator->setMinMax(0, 255);
	deviceManager.setDeviceType(FanActuator.pin_nr, FanActuator.hw_address, DEVICE_HARDWARE_ACTUATOR_PWM);
}

int FridgeController::calculateTargetTemperature()
{
	Helper::serialDebug("Calculate target temperature");
	long now = Time.now();

	for(int i=1; i < (MAX_PHASES-1); i++) {

		if (this->config.temperaturePhases[i].time < now &&
            this->config.temperaturePhases[i+1].time > now) {

			String debug("New Target Temperature ");
			debug.concat(i);
			debug.concat(": ");
			debug.concat(this->config.temperaturePhases[i+1].time);
			debug.concat(" ( ");
			debug.concat(now);
			debug.concat(" ) -> ");
			debug.concat(this->config.temperaturePhases[i].targetTemperature);
			Helper::serialDebug(debug.c_str());

			this->until = this->config.temperaturePhases[i+1].time;
			setTargetTemperature(this->config.temperaturePhases[i].targetTemperature);

			return (i-1);
		}
	}

	Helper::serialDebug("Finished");

	this->finished = true;
	setTargetTemperature(0);
	this->until = 0;

	return 0;
}
