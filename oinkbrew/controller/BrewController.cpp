/**
 ******************************************************************************
 * @file    BrewController.cpp
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

#include "BrewController.h"
#include "../devices/Device.h"
#include "../devices/DeviceManager.h"
#include "../Helper.h"

BrewController::BrewController(ControllerConfiguration& config)
	: Controller()
{
	setConfig(config);
}

void BrewController::dispose()
{
	Controller::dispose();

	turnOffPump1();
	turnOffPump2();

	if (this->pump1Actuator)
		delete this->pump1Actuator;
	if (this->pump2Actuator)
		delete this->pump2Actuator;
}

void BrewController::setConfig(ControllerConfiguration& config)
{
	Controller::setConfig(config);

	getPID()->SetOutputLimits(0, 100);

	if (getConfig().temperature > 0) {
		getPID()->SetMode(PID_AUTOMATIC);
		setTargetTemperature(getConfig().temperature);
	}
	else {
		getPID()->SetMode(PID_MANUAL);
		turnOnHeater(getConfig().heaterPwm);
	}

	if (getConfig().pump1Pwm > 0) {
		this->setPump1Actuator(getConfig().pump1Actuator);
		this->turnOnPump1();
	}
	if (getConfig().pump2Pwm > 0) {
		this->setPump2Actuator(getConfig().pump2Actuator);
		this->turnOnPump2();
	}
}

void BrewController::doProcess()
{
	if (getConfig().temperature > 0)
	{
		turnOnHeater(getOutput());
	}
}

void BrewController::setPump1Actuator(ActingDevice Pump1Actuator)
{
	if (Pump1Actuator.pin_nr != 0 || !Helper::matchAddress(Pump1Actuator.hw_address , DEVICE_ADDRESS_EMPTY, 8) ) {
		this->pump1Actuator = new PwmActuator(Pump1Actuator.pin_nr, Pump1Actuator.hw_address, getConfig().pump1Pwm, getConfig().heatingPeriod, false);
	}
}

void BrewController::turnOnPump1()
{
	if (this->pump1Actuator) {
		this->pump1Actuator->setPwm(getConfig().pump1Pwm);
	}
}

void BrewController::turnOffPump1()
{
	if (this->pump1Actuator) {
		this->pump1Actuator->setPwm(0);
	}
}

void BrewController::setPump2Actuator(ActingDevice Pump2Actuator)
{
	if (Pump2Actuator.pin_nr != 0 || !Helper::matchAddress(Pump2Actuator.hw_address , DEVICE_ADDRESS_EMPTY, 8)) {
		this->pump1Actuator = new PwmActuator(Pump2Actuator.pin_nr, Pump2Actuator.hw_address, getConfig().pump2Pwm, getConfig().heatingPeriod, false);
	}
}

void BrewController::turnOnPump2()
{
	if (this->pump2Actuator) {
		this->pump2Actuator->setPwm(getConfig().pump2Pwm);
	}
}

void BrewController::turnOffPump2()
{
	if (this->pump2Actuator) {
		this->pump2Actuator->setPwm(0);
	}
}
