/**
 ******************************************************************************
 * @file    Device.h
 * @authors Thomas Trageser
 * @version V0.1
 * @date    2015-04-03
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

#ifndef DEVICE_H
#define	DEVICE_H

#include <stdint.h>

typedef uint8_t DeviceAddress[8];

enum DeviceType : uint8_t
{
	DEVICE_HARDWARE_NONE = 0,
	DEVICE_HARDWARE_ACTUATOR_DIGITAL = 1, 	// digital pin, either on or off
	DEVICE_HARDWARE_ACTUATOR_PWM = 2,		// analogue pin, used as PWM actuator
	DEVICE_HARDWARE_ONEWIRE_TEMP = 3,		// a onewire temperature sensor
};

struct Device
{
	uint8_t pin_nr;
	DeviceAddress hw_address;
	DeviceType type;
	float value;
	float offset;
	bool newly_found;
	unsigned long lastSeen;
};

#endif	/* DEVICE_H */
