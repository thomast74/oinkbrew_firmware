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


PwmActuator::PwmActuator(uint8_t pin, DeviceAddress& hw_address, uint8_t pwm, uint32_t period)
  : PwmActuator(pin, hw_address, pwm, period, true)
{
}


PwmActuator::PwmActuator(uint8_t pin, DeviceAddress& hw_address, uint8_t pwm, uint32_t period, bool simulate)
{
	this->pin = pin;
	memcpy(&this->hw_address, &hw_address, 8);
	this->periodStartTime = 0;
	this->simulate = simulate;
	this->periodLate = 0;
	this->dutyTime = 0;
	this->dutyLate = 0;
	this->pwm = 0;
	this->minVal = 0;
	this->maxVal = 100;
    this->period = period;

	this->active = false;

	this->setPwm(pwm);

	pinMode(this->pin, OUTPUT);
}

void PwmActuator::recalculate(){
	int32_t newPeriod = this->pwm * this->period / 100;
	int32_t correctionFactor = (this->period + periodLate) / this->period;
    this->dutyTime = int32_t(newPeriod * correctionFactor);
}

void PwmActuator::setMinMax(uint8_t minVal, uint8_t maxVal)
{
	this->minVal = minVal;
	this->maxVal = maxVal;
}

uint8_t PwmActuator::getPwm()
{
	return this->pwm;
}

void PwmActuator::setPwm(uint8_t val)
{
	if (this->simulate) {
	    if (val <= minVal){
	    	val = minVal;
	    }
	    if (val >= maxVal){
	    	val = maxVal;
	    }
	    if(this->pwm != val){
	    	uint8_t delta = (val > this->pwm) ? val - this->pwm : this->pwm - val;
	    	this->pwm = val;
	        if(delta > 1){
	            dutyLate = 0;
	        }
	    }
	    recalculate();	}
	else {
    	this->pwm = val;
		analogWrite(this->pin, this->pwm);
		this->active = this->pwm > 0;
	}
}

void PwmActuator::updatePwm()
{
	if (!this->simulate)
		return;

    uint32_t adjDutyTime = this->dutyTime - this->dutyLate;
    uint32_t currentTime = millis();
    uint32_t elapsedTime = currentTime - periodStartTime;

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
        if (elapsedTime >= this->period) {
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
            this->periodLate = (this->periodLate < this->period / 2) ? this->periodLate : this->period / 2;
            // adjust next duty time to account for longer period due to infrequent updates
            // low period was longer, increase high period (duty cycle) with same ratio
            recalculate();
            this->periodStartTime = currentTime;
        }
    }
}
