/**
 ******************************************************************************
 * @file    Controller.cpp
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


#include "PwmActuator.h"

PwmActuator::PwmActuator(uint8_t pin, uint8_t pwm) : PwmActuator(pin, pwm, true)
{
}

PwmActuator::PwmActuator(uint8_t pin, uint8_t pwm, bool simulate)
{
	this->pin = pin;
	this->periodStartTime = 0;
	this->simulate = simulate;

	this->setPwm(pwm);

	pinMode(this->pin, OUTPUT);
}

uint8_t PwmActuator::getPwm()
{
	return this->pwm;
}

void PwmActuator::setPwm(uint8_t val)
{
	this->pwm = val;

	if (this->simulate) {
		this->dutyLate = 0;
		this->dutyTime = ((this->pwm * period) / 255);
	}
	else {
		analogWrite(this->pin, val);
		this->active = val > 0;
	}
}

void PwmActuator::updatePwm()
{
	if (!this->simulate)
		return;

	int32_t adjDutyTime = dutyTime - this->dutyLate;
	int32_t currentTime = millis();
	int32_t elapsedTime = currentTime - this->periodStartTime;

	if (this->isActive()) {
		if (elapsedTime >= adjDutyTime) {
			// end of duty cycle
			digitalWrite(this->pin, LOW);
			this->active = false;
			this->dutyLate += elapsedTime - dutyTime;
		}
	}
	if (!this->isActive()) {
		if (elapsedTime >= period) {
			// end of PWM cycle
			if (adjDutyTime < 0) {
				// skip going high for 1 period when previous periods built up
				// more than one entire duty cycle (duty is ahead)
				// subtract duty cycle form duty late accumulator
				this->dutyLate = this->dutyLate - dutyTime;
			} else {
				digitalWrite(this->pin, HIGH);
				this->active = true;
			}
			int32_t periodLate = elapsedTime - period;

			// limit to half of the period
			periodLate = (periodLate < period / 2) ? periodLate : period / 2;

			// adjust next duty time to account for longer period due to infrequent updates
			// low period was longer, increase high period (duty cycle) with same ratio
			this->dutyTime = ((this->pwm * period) / 255) * (period + periodLate) / period;
			this->periodStartTime = currentTime;
		}
	}
}
