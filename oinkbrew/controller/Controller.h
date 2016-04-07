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

#define OVERSHOOT_HEAT 0.0
#define OVERSHOOT_KEEP 0.0


#include "PID.h"
#include "ControllerConfiguration.h"
#include "../devices/PwmActuator.h"

enum ControllerState {
	IDLE,
	HEATING,
	COOLING
};


class Controller
{
public:
	Controller();
	virtual ~Controller();

	virtual void dispose();

	ControllerConfiguration& getConfig();
	virtual void setConfig(ControllerConfiguration& config);

	void process();
	virtual void update();

	float getTargetTemperature();
	void setTargetTemperature(float target);

	float getCurrentTemperature();

	int getId();

protected:
	virtual void doProcess() { };

	void setTempSensor(ActingDevice TempSensor);
	void setHeatActuator(ActingDevice HeatActuator);

	bool isHeaterOn();
	virtual void turnOnHeater(float pwm);
	virtual void turnOffHeater();

	PID* getPID();
	float getOutput();

	DeviceAddress DEVICE_ADDRESS_EMPTY = {0,0,0,0,0,0,0,0};

private:
	ActingDevice tempSensor;
	PwmActuator* heatActuator;
	ControllerConfiguration config;

	float targetTemperature;
	float currentTemperature;
	float output;
	PID* pid;
};

#endif /* OINKBREW_CONTROLLER_CONTROLLER_H_ */
