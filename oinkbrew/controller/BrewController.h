/**
 ******************************************************************************
 * @file    BrewController.h
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

#ifndef OINKBREW_CONTROLLER_BREWCONTROLLER_H_
#define OINKBREW_CONTROLLER_BREWCONTROLLER_H_

#define BEER_OVERSHOOT_HEAT 0.5
#define BEER_OVERSHOOT_KEEP 0.5


#include "Controller.h"


class BrewController : public Controller
{
public:
	BrewController(ControllerConfiguration& config);

	void update();
	void dispose();
	bool isHeatActuatorActive();

protected:
	void doProcess();
};



#endif /* OINKBREW_CONTROLLER_BREWCONTROLLER_H_ */
