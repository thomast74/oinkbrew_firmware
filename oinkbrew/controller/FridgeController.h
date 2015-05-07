/**
 ******************************************************************************
 * @file    FridgeController.h
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

#ifndef OINKBREW_CONTROLLER_FRIDGECONTROLLER_H_
#define OINKBREW_CONTROLLER_FRIDGECONTROLLER_H_

#include "Controller.h"
#include "../devices/DigitalActuator.h"


const unsigned long MIN_COOL_OFF_TIME = 300000;	// 5 minutes
const unsigned long MIN_COOL_ON_TIME = 180000;	// 3 minutes
const unsigned long MAX_COOL_ON_TIME = 360000;	// 6 minutes
const unsigned long WAIT_FAN_ON_TIME = 180000;	// 3 minutes


enum State {
	IDLE,
	HEATING,
	COOLING
};

class FridgeController : Controller
{
private:
	DigitalActuator *coolActuator;
	PwmActuator *fanActuator;
	State state;
	unsigned long idleStartTime;
	unsigned long coolingOffTime;
	unsigned long coolingOnTime;
public:
	FridgeController(ActingDevice tempSensor, ActingDevice heatActuator, ActingDevice coolActuator, ActingDevice fanActuator, float targetTemperature);
	~FridgeController();

protected:
	void doProcess();

private:
	void turnOnHeating();
	void turnOnCooling();
	void setIdle();
	void checkFanActivity();
	void setCoolActuator(ActingDevice CoolActuator);
	void setFanActuator(ActingDevice FanActuator);
};



#endif /* OINKBREW_CONTROLLER_FRIDGECONTROLLER_H_ */
