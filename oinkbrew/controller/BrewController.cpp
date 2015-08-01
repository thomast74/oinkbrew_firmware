/**
 ******************************************************************************
 * @file    BrewController.cpp
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

#include "BrewController.h"
#include "../Helper.h"

bool BrewController::doProcess()
{
	heatActuator->setPwm(output);

	if (!this->temperatureReached  && this->currentTemperature >= this->targetTemperature) {

		Helper::serialDebug("Temperature reached");

		this->temperatureReached = true;
		this->startTime =  millis();
	}

	if (this->temperatureReached) {
		if (this->duration < (millis() - startTime))
			return calculateTargetTemperature();
	}

	return false;
}

void BrewController::update()
{
	heatActuator->updatePwm();
}

void BrewController::dispose()
{
	heatActuator->setPwm(0);
	heatActuator->updatePwm();
}

bool BrewController::calculateTargetTemperature()
{
	for(int i=0; i < MAX_PHASES; i++) {

		if (this->config.temperaturePhases[i].done)
			continue;

		this->config.temperaturePhases[i].done = true;
		this->temperatureReached = false;

		if ((i + 1) < MAX_PHASES) {

			String debug("New Target Temperature ");
			debug.concat(i);
			debug.concat(": ");
			debug.concat(this->config.temperaturePhases[i+1].duration);
			debug.concat(" -> ");
			debug.concat(this->config.temperaturePhases[i+1].targetTemperature);
			Helper::serialDebug(debug.c_str());

			this->duration = this->config.temperaturePhases[i+1].duration;
			setTargetTemperature(this->config.temperaturePhases[i+1].targetTemperature);

			return true;
		}
		else {
			String debug("New Target Temperatur off: 10000000 -> 0");
			Helper::serialDebug(debug.c_str());

			heatActuator->setPwm(0);
			heatActuator->updatePwm();

			this->finished = true;
			this->duration = 0;
			setTargetTemperature(0);
		}
		break;
	}

	return false;
}

unsigned long BrewController::timeToGo() {

	if (this->temperatureReached) {
		return this->duration - (millis() - startTime);
	}
	else
		return 0;
}

bool BrewController::isHeatActuatorActive()
{
	return this->heatActuator->isActive();
}

bool BrewController::isTemperatureReached()
{
	return this->temperatureReached;
}
