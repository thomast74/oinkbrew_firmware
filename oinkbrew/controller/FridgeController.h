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


class FridgeController : public Controller
{
public:
	FridgeController(ControllerConfiguration& config);
	void dispose();

	void setConfig(ControllerConfiguration& config);
	void update();

protected:
	void doProcess();
	void turnOnHeater(float pwm);

private:
	void turnOnCooler(float pwm);
	void turnOffCooler();

	void turnOnFan();
	void turnOffFan();

	void setIdle();

	void setCoolActuator(ActingDevice CoolActuator);
	void setFanActuator(ActingDevice FanActuator);

	PwmActuator *coolActuator;
	PwmActuator *fanActuator;
	ControllerState state;

	unsigned long coolingOffTime;
	unsigned long coolingOnTime;
};



#endif /* OINKBREW_CONTROLLER_FRIDGECONTROLLER_H_ */
