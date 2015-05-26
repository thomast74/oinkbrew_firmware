/**
 ******************************************************************************
 * @file    ControllerManager.h
 * @authors Thomas Trageser
 * @version V0.3
 * @date    2015-05-05
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

#ifndef OINKBREW_CONTROLLER_CONTROLLERMANAGER_H_
#define OINKBREW_CONTROLLER_CONTROLLERMANAGER_H_

#include "Controller.h"
#include "ControllerConfiguration.h"



class ControllerManager
{
private:
	static Controller* active_controllers[MAX_CONTROLLERS];
	static short registered_controllers;
public:
	static void process();

	static void loadControllersFromEEPROM();

	static bool changeController(ControllerConfiguration request);
	static bool removeController(int id);
private:
	static int findController(int id);
};

extern ControllerManager controllerManager;

#endif /* OINKBREW_CONTROLLER_CONTROLLERMANAGER_H_ */
