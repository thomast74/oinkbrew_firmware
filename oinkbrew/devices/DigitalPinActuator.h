/* 
 * File:   ArduinoActuator.h
 * Author: mat
 *
 * Created on 19 August 2013, 20:32
 */

#pragma once

#include "Actuator.h"

class DigitalPinActuator ACTUATOR_BASE_CLASS_DECL {
private:
	bool invert;
	uint8_t pin;
	bool active;
public:
	DigitalPinActuator(uint8_t pin, bool invert) {
		this->pin = pin;
		this->invert = invert;

		pinMode(pin, OUTPUT);

		this->active = digitalRead(pin) == HIGH ? true : false;
	}

	inline ACTUATOR_METHOD void setActive(bool active) {
		this->active = active;
		digitalWrite(pin, active ^ invert ? HIGH : LOW);
	}

	bool isActive() {
		return active;
	}
};
