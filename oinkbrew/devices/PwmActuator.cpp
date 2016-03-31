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
#include "../Helper.h"
#include "spark_wiring.h"

PwmActuator::PwmActuator(uint8_t pin, DeviceAddress& hw_address, float pwm,
		unsigned long period, bool simulate)
{

	this->pin = pin;
	memcpy(&this->hw_address, &hw_address, sizeof(DeviceAddress));
	this->periodStartTime = 0;
	this->simulate = simulate;
	this->periodLate = 0;
	this->dutyTime = 0;
	this->dutyLate = 0;
	this->pwm = 0;
	this->minVal = 0;
	this->maxVal = 100;
	this->period = period;
	this->minimumOnTime = 0;
	this->minimumOffTime = 0;
	this->active = false;

	pinMode(this->pin, OUTPUT);
	this->setPwm(pwm);
}

void PwmActuator::recalculate()
{
	unsigned long newPeriod = this->pwm * this->period / 100;
	unsigned long correctionFactor = (this->period + periodLate) / this->period;

	this->dutyTime = newPeriod * correctionFactor;

	if (this->minimumOnTime > 0 && this->dutyTime < this->minimumOnTime) {
		this->dutyTime = this->minimumOnTime;
	}
}

void PwmActuator::setMinMax(float minVal, float maxVal)
{
	this->minVal = minVal;
	this->maxVal = maxVal;
}

void PwmActuator::setMinimumOnTime(unsigned long minOnTime)
{
	this->minimumOnTime = minOnTime;
	if (this->minimumOnTime > this->period)
		this->minimumOnTime = this->period;
}

float PwmActuator::getPwm()
{
	return this->pwm;
}

void PwmActuator::setPwm(float val)
{
	if (this->simulate) {
		if (val <= this->minVal) {
			val = this->minVal;
		}
		if (val >= this->maxVal) {
			val = this->maxVal;
		}
		if (this->pwm != val) {
			float delta = (val > this->pwm) ? val - this->pwm : this->pwm - val;
			this->pwm = val;
			if (delta > 1.0) {
				dutyLate = 0;
			}
		}
		recalculate();
	} else {
		this->pwm = val;

		float value = 0.0;
		if (this->pin == 16) {
			value = (4095.0000 / 100.0000) * this->pwm;
		} else {
			value = (255.0000 / 100.0000) * this->pwm;
		}

		analogWrite(this->pin, value);
		this->active = this->pwm > 0.0;
	}
}

void PwmActuator::updatePwm()
{
	if (!this->simulate)
		return;

	unsigned long adjDutyTime = this->dutyTime - this->dutyLate;
	unsigned long currentTime = millis();
	unsigned long elapsedTime = currentTime - periodStartTime;

	if (this->pwm <= minVal) {
		digitalWrite(this->pin, LOW);
		this->active = false;
		return;
	}

	if (this->pwm >= maxVal) {
		digitalWrite(this->pin, HIGH);
		this->active = true;
		return;
	}

	if (this->active) {
		if (elapsedTime >= adjDutyTime) {
			// end of duty cycle
			digitalWrite(this->pin, LOW);
			this->active = false;
			this->dutyLate += elapsedTime - this->dutyTime;
		}
	}
	if (!this->active) { // <- do not replace with else if
		if (elapsedTime >= this->period || periodStartTime == 0) {
			// end of PWM cycle
			if (adjDutyTime < 0) {
				// skip going high for 1 period when previous periods built up
				// more than one entire duty cycle (duty is ahead)
				// subtract duty cycle form duty late accumulator
				this->dutyLate = this->dutyLate - this->dutyTime;
			} else {
				digitalWrite(this->pin, HIGH);
				this->active = true;
			}
			this->periodLate = elapsedTime - this->period;
			// limit to half of the period
			this->periodLate = (this->periodLate < this->period / 2)
					? this->periodLate
				    : this->period / 2;
			// adjust next duty time to account for longer period due to infrequent updates
			// low period was longer, increase high period (duty cycle) with same ratio
			recalculate();
			this->periodStartTime = currentTime;
		}
	}
}
