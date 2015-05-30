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
#include "../Helper.h"
#include "../SparkInfo.h"

Controller* ControllerManager::active_controllers[MAX_CONTROLLERS] = {};
short ControllerManager::registered_controllers = 0;


void ControllerManager::process()
{
	if (sparkInfo.mode != SPARK_MODE_AUTOMATIC)
		return;

	for(short i=0; i < registered_controllers; i++)
	{
		if (active_controllers[i]->process()) {
			conf.storeController(active_controllers[i]->getConfig());
		}
	}
}

void ControllerManager::loadControllersFromEEPROM()
{
	short stored_controllers = conf.fetchNumberControllers();
	ControllerConfiguration configs[stored_controllers];

	conf.fetchControllers(configs);

	Helper::serialDebug("Reg Controllers: ", false);
	Helper::serialDebug(registered_controllers);

	// add controllers for each configuration
	for(int i=0; i < stored_controllers; i++) {
		if (configs[i].type == TYPE_BREW) {
			Helper::serialDebug("Create Brew Controller");
			active_controllers[registered_controllers] = new BrewController(configs[i]);
			registered_controllers++;
		}
		else if (configs[i].type == TYPE_FRIDGE) {
			Helper::serialDebug("Create Fridge Controller");
			active_controllers[registered_controllers] = new FridgeController(configs[i]);
			registered_controllers++;
		}
		else {
			Helper::serialDebug("Uknown controller: ", false);
			Helper::serialDebug(configs[i].type);
			conf.removeController(configs[i]);
		}
	}
}

bool ControllerManager::changeController(ControllerConfiguration request)
{
	String debug("Add or update controller: ");
	debug.concat(request.id);
	debug.concat(" -> ");
	debug.concat(request.type);
	Helper::serialDebug(debug.c_str());

	int index = findController(request.id);

	if (index >= 0) {
		Helper::serialDebug("Updating existing controller");
		active_controllers[index]->setConfig(request);
	}
	else {
		if (request.type == TYPE_BREW) {
			Helper::serialDebug("Create Brew Controller");
			active_controllers[registered_controllers] = new BrewController(request);
			registered_controllers++;
		}
		else if (request.type == TYPE_FRIDGE) {
			Helper::serialDebug("Create Fridge Controller");
			active_controllers[registered_controllers] = new FridgeController(request);
			registered_controllers++;
		}
		else {
			return false;
		}
	}

	conf.storeController(request);

	return true;
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

int ControllerManager::findController(int id)
{
	for(int i=0; i < registered_controllers; i++) {
		if (active_controllers[i]->getId() == id) {
			return i;
		}
	}

	return -1;
}
