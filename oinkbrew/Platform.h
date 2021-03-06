/**
 ******************************************************************************
 * @file    DeviceManager.cpp
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


#ifndef OINKBREW_PLATFORM_H_
#define OINKBREW_PLATFORM_H_


#include <stdio.h>


#define ONE_WIRE_PIN	0
#define ACTUATOR_PIN_1  10
#define ACTUATOR_PIN_2  11
#define ACTUATOR_PIN_3  16
#define ACTUATOR_PIN_4  17
#define BUZZER_PIN		12



#define strcpy_P strcpy
#define strlcpy_P strncpy
#define sprintf_P sprintf
#define strcmp_P strcmp
#define memcpy_P memcpy
#define vsnprintf_P vsnprintf
#define PROGMEM
#define pgm_read_byte(x)  (*(x))


uint8_t getShieldVersion();
bool shieldIsV2();

#endif /* OINKBREW_PLATFORM_H_ */
