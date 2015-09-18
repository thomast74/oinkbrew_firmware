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
#include "../devices/DeviceManager.h"
#include "../Helper.h"

BrewController::BrewController(ControllerConfiguration& config)
	: Controller()
{
	this->pid->SetOutputLimits(0, 100);
	setConfig(config);
}

void BrewController::doProcess()
{
	heatActuator->setPwm(output);
	deviceManager.setDeviceValue(this->heatActuator->getPin(), this->heatActuator->getHwAddress(), output);
}

void BrewController::update()
{
	heatActuator->updatePwm();
}

void BrewController::dispose()
{
	getHeatActuator()->setPwm(0);
	heatActuator->updatePwm();
	deviceManager.setDeviceValue(this->heatActuator->getPin(), this->heatActuator->getHwAddress(), 0);

	delete heatActuator;
}

bool BrewController::isHeatActuatorActive()
{
	return this->heatActuator->isActive();
}
