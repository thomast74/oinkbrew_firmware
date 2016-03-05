/**
 ******************************************************************************
 * @file    ControllerConfiguration.h
 * @authors Thomas Trageser
 * @version V0.3
 * @date    2015-05-14
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


#ifndef OINKBREW_CONTROLLER_CONTROLLERCONFIGURATION_H_
#define OINKBREW_CONTROLLER_CONTROLLERCONFIGURATION_H_


#include "../devices/Device.h"
#include <stdint.h>


const short MAX_CONTROLLERS = 3;


struct ActingDevice
{
	uint8_t pin_nr;
	DeviceAddress hw_address;
};

enum ControllerType : uint8_t
{
	TYPE_NONE = 0,
	TYPE_BREW = 1,
	TYPE_FRIDGE = 2
};

struct ControllerConfiguration {
	int id;
	char name[31];
	ControllerType type;
	ActingDevice tempSensor;
	ActingDevice heatActuator;
	ActingDevice coolActuator;
	ActingDevice fanActuator;
	float temperature;
	float heaterPwm;
	float fanPwm;
	uint32_t heatingPeriod;
	uint32_t coolingOnPeriod;
	uint32_t coolingOffPeriod;
	float p;
	float i;
	float d;
};


#endif /* OINKBREW_CONTROLLER_CONTROLLERCONFIGURATION_H_ */
