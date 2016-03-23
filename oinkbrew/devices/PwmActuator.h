/**
 ******************************************************************************
 * @file    PwmActuator.h
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

#ifndef OINKBREW_DEVICES_PWMACTUATOR_H_
#define OINKBREW_DEVICES_PWMACTUATOR_H_

#include "../devices/Device.h"

class PwmActuator
{
private:
	uint8_t pin;
	DeviceAddress hw_address;
    float pwm;
    float minVal;
    float maxVal;
    unsigned long period;
    bool active;
    bool simulate;

    unsigned long periodLate;
    unsigned long dutyLate;
    unsigned long dutyTime;

    unsigned long periodStartTime;

    void recalculate();

public:
	PwmActuator(uint8_t pin, DeviceAddress& hw_address, float pwm, unsigned long period, bool simulate);

	void setPwm(float pwm);
	float getPwm();
	void setMinMax(float minVal, float maxVal);
	void updatePwm();

	unsigned long getPeriod(){
		return period;
	}
	bool isActive() {
		return pwm > 0.0;
	}
	uint8_t& getPin() {
		return pin;
	}
	DeviceAddress& getHwAddress() {
		return hw_address;
	}
};

#endif // OINKBREW_DEVICES_PWMACTUATOR_H_
