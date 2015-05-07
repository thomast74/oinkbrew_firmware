/**
 ******************************************************************************
 * @file    Controller.h
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

#ifndef OINKBREW_CONTROLLER_CONTROLLER_H_
#define OINKBREW_CONTROLLER_CONTROLLER_H_

#include "PID.h"
#include "../devices/Device.h"
#include "../devices/PwmActuator.h"
#include <stdint.h>


struct ActingDevice
{
	uint8_t pin_nr;
	DeviceAddress hw_address;
};

class Controller
{
public:
	Controller();
	Controller(ActingDevice tempSensor, ActingDevice heatActuator, float targetTemperature);
	virtual ~Controller();

	void process();
	void setTempSensor(ActingDevice TempSensor);
	void setHeatActuator(ActingDevice HeatActuator);
	void setTargetTemperatur(float PointTemperature);

protected:
	virtual void doProcess() {};

	ActingDevice tempSensor;
	PwmActuator* heatActuator;

	float targetTemperature;
	float currentTemperature;
	float output;
	PID* pid;
};

#endif /* OINKBREW_CONTROLLER_CONTROLLER_H_ */
