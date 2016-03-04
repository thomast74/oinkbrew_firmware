/**
 ******************************************************************************
 * @file    DigitalActuator.h
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

#include "spark_wiring.h"

class DigitalActuator {
private:
	bool invert;
	uint8_t pin;
	DeviceAddress hw_address;
	bool active;
public:
	DigitalActuator(uint8_t pin, DeviceAddress& hw_address, bool invert) {
		this->pin = pin;
		memcpy(&this->hw_address, &hw_address, 8);
		this->invert = invert;

		pinMode(pin, OUTPUT);

		this->active =
				digitalRead(pin) == HIGH ?
						true ^ this->invert : false ^ this->invert;
	}

	void setActive(bool active) {
		this->active = active;

		digitalWrite(pin, active ^ invert ? HIGH : LOW);
	}

	bool toggle() {
		setActive(!this->active);

		return this->active;
	}

	bool isActive() {
		return active;
	}
	uint8_t& getPin() {
		return pin;
	}
	DeviceAddress& getHwAddress() {
		return hw_address;
	}
};
