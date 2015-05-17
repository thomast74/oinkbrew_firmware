/**
 ******************************************************************************
 * @file    ControllerManager.cpp
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


#include "ControllerManager.h"
#include "ControllerConfiguration.h"
#include "BrewController.h"
#include "FridgeController.h"
#include "../Configuration.h"


Controller* ControllerManager::active_controllers[MAX_CONTROLLERS] = {};
short ControllerManager::registered_controllers = 0;


void ControllerManager::process()
{
	for(short i=0; i < registered_controllers; i++)
	{
		active_controllers[i]->process();
	}
}

void ControllerManager::loadControllersFromEEPROM()
{
	registered_controllers = conf.fetchNumberDevices();
	ControllerConfiguration configs[registered_controllers];

	conf.fetchControllers(configs);

	// add controllers for each configuration
	for(int i=0; i < registered_controllers; i++) {

		if (configs[i].type == TYPE_BREW) {
			active_controllers[i] = new BrewController(configs[i]);
		}
		else if (configs[i].type == TYPE_FRIDGE) {
			active_controllers[i] = new FridgeController(configs[i]);
		}
	}
}

void ControllerManager::addController()
{
	// check that controller does not exists already
	// if exists do update instead

	// if not create controller based on type
	// add to active_controllers
	// save configuration in EEPROM
}

void ControllerManager::updateController()
{
	// get controller
	// if found update configuration
	// save configuration in EEPROM
}

bool ControllerManager::removeController(int id)
{
	Controller* new_active_controllers[MAX_CONTROLLERS] = {};
	bool removed = false;
	short new_registered_controllers = 0;

	for(int i=0; i < registered_controllers; i++) {
		if (active_controllers[i]->getId() == id) {
			conf.removeController(active_controllers[i]->getConfig());
			removed = true;
		}
		else {
			new_active_controllers[new_registered_controllers] = active_controllers[i];
			new_registered_controllers++;
		}
	}

	if (removed) {
		memcpy(active_controllers, new_active_controllers, sizeof(new_active_controllers));
		registered_controllers = new_registered_controllers;
	}

	return removed;
}
