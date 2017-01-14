/**
 ******************************************************************************
 * @file    Board.cpp
 * @authors Thomas Trageser
 * @version V0.5
 * @date    2017-01-14
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

#include "Platform.h"
#include "spark_wiring.h"

#define BREWPI_SHIELD_SPARK_V1 1
#define BREWPI_SHIELD_SPARK_V2 2


uint8_t getShieldVersion(){
	static uint8_t shield = 255;

	// only auto-detect once
	if(shield == 255){
		// V2 has a pull down resistor, V1 has a pull up resistor on the alarm pin
		// If the pin is low, it is V2
		pinMode(BUZZER_PIN, INPUT);
		delay(1);
		if(digitalRead(BUZZER_PIN)){
			shield = BREWPI_SHIELD_SPARK_V1;
		}
		else{
			shield = BREWPI_SHIELD_SPARK_V2;
		}
	}
	return shield;
}

bool shieldIsV2(){
	return getShieldVersion() == BREWPI_SHIELD_SPARK_V2;
}
