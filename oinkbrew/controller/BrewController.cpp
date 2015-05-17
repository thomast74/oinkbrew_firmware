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


void BrewController::doProcess()
{
	if (output > 5) {
		heatActuator->setPwm(output);
	}
	else {
		if (heatActuator->isActive()) {
			heatActuator->setPwm(0);
		}
	}

	heatActuator->updatePwm();

	if (!this->temperatureReached  && currentTemperature >= (targetTemperature - 0.5) && currentTemperature <= (targetTemperature + 0.5)) {
		this->temperatureReached = true;
	}
}

void BrewController::calculateTargetTemperatur()
{
	if (!this->temperatureReached)
		return;

	unsigned long duration = millis() - startTime;

	for(int i=0; i < MAX_PHASES; i++) {

		if (this->config.temperaturePhases[i].done)
			continue;

		if (this->config.temperaturePhases[i].duration <= duration) {
			this->config.temperaturePhases[i].done = true;
			if ((i + 1) < MAX_PHASES) {
				setTargetTemperatur(this->config.temperaturePhases[i].targetTemperature);
			}
			else {
				setTargetTemperatur(0);
			}
			this->temperatureReached = false;
		}
	}
}
