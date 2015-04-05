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
	DEVICE_HARDWARE_PIN=1,				// a digital pin, either input or output
	DEVICE_HARDWARE_ONEWIRE_TEMP=2,		// a onewire temperature sensor
};


struct Device {

	DeviceType type;
	char value[10];

	struct Hardware {
		uint8_t pin_nr;			// the arduino pin nr this device is connected to
		DeviceAddress address;	// for onewire devices, if address[0]==0 then use the first matching device type, otherwise use the device with the specific address
		int32_t offset;			// calibrated offset for temperatur sensor
		bool is_invert;			// for actuators/sensors, controls if the signal value is inverted.
		bool is_deactivate;		// In case device is deactivated. no logging or data collection will be done
	} hardware;

};

#endif	/* DEVICE_H */
