/**
 ******************************************************************************
 * @file    Buzzer.h
 * @authors Thomas Trageser
 * @version V0.1
 * @date    2015-03-27
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


#pragma once

#include "../Platform.h"
#include "spark_wiring.h"
#include <stdint.h>


#define BEEP_ON() digitalWrite(BUZZER_PIN, LOW);
#define BEEP_OFF() digitalWrite(BUZZER_PIN, HIGH);


class Buzzer {
private:
	bool active;
public:
	Buzzer() {
		pinMode(BUZZER_PIN, OUTPUT);
		active = false;
	}

	void beep(uint8_t numBeeps, uint16_t duration) {
	    for (uint8_t beepCount = 0; beepCount < numBeeps; beepCount++) {
	        BEEP_ON();
	        delay(duration);
	        BEEP_OFF();
	        if (beepCount < numBeeps - 1) {
	            delay(duration);
	        }
	    }
	}

	void setActive(bool active) {
	    if (active != this->active) {
	        this->active = active;
	        if (active) {
	            BEEP_ON();
	        } else {
	            BEEP_OFF();
	        }
	    }
	}

	bool isActive() {
		return active;
	}
};

extern Buzzer buzzer;
