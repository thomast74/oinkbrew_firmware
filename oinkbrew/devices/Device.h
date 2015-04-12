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


enum DeviceType : uint8_t {
	DEVICE_HARDWARE_NONE=0,
	DEVICE_HARDWARE_ACTUATOR_DIGITAL=1, // digital pin, either on or off
	DEVICE_HARDWARE_ACTUATOR_PWM=2,		// analogue pin, used as PWM actuator
	DEVICE_HARDWARE_ONEWIRE_TEMP=3,		// a onewire temperature sensor

};

enum DeviceFunction : uint8_t {
	DEVICE_FUNCTION_NONE=0,
	DEVICE_FUNCTION_FRIDGE_COOLING_ACTUATOR=1,
	DEVICE_FUNCTION_FRIDGE_HEATING_ACTUATOR=2,
	DEVICE_FUNCTION_FRIDGE_FAN_ACTUATOR=3,

	DEVICE_FUNCTION_HLT_HEATING_ACTUATOR = 4,
	DEVICE_FUNCTION_BOIL_HEATING_ACTUATOR = 5,
	DEVICE_FUNCTION_PUMP_1_ACTUATOR = 6,
	DEVICE_FUNCTION_PUMP_2_ACTUATOR = 7,

	DEVICE_FUNCTION_FRIDGE_BEER_TEMP_SENSOR = 8,
	DEVICE_FUNCTION_FRIDGE_INSIDE_TEMP_SENSOR = 9,
	DEVICE_FUNCTION_FRIDGE_OUTSIDE_TEMP_SENSOR = 10,

	DEVICE_FUNCTION_HLT_IN_TEMP_SENSOR = 11,
	DEVICE_FUNCTION_HLT_OUT_TEMP_SENSOR = 12,
	DEVICE_FUNCTION_MASH_IN_TEMP_SENSOR = 13,
	DEVICE_FUNCTION_MACH_OUT_TEMP_SENSOR = 14,
	DEVICE_FUNCTION_BOIL_IN_TEMP_SENSOR = 15,
	DEVICE_FUNCTION_BOIL_INSIDE_TEMP_SENSOR = 16,
	DEVICE_FUNCTION_BOIL_OUT_TEMP_SENSOR = 17
};

struct ActiveDevice {
	uint8_t pin_nr;
	DeviceAddress hw_address;
	DeviceType type;
	void* device;
	float value;
};

struct Device {

	DeviceType type;
	DeviceFunction function;

	struct Hardware {
		uint8_t pin_nr;			// the arduino pin nr this device is connected to
		DeviceAddress hw_address;	// for onewire devices, if address[0]==0 then use the first matching device type, otherwise use the device with the specific address
		int32_t offset;			// calibrated offset for temperatur sensor
		bool is_invert;			// for actuators/sensors, controls if the signal value is inverted.
		bool is_deactivate;		// In case device is deactivated. no logging or data collection will be done
	} hardware;
	bool reserved;
};

#endif	/* DEVICE_H */
