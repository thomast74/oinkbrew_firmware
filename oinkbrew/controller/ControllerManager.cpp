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
#include "../TcpLogger.h"

Controller* ControllerManager::active_controllers[MAX_CONTROLLERS] = {};
short ControllerManager::registered_controllers = 0;


void ControllerManager::process()
{
	if (sparkInfo.mode != SPARK_MODE_AUTOMATIC)
		return;

	for(short i=0; i < registered_controllers; i++)
	{
		int tempPhaseId = active_controllers[i]->process();
		if (tempPhaseId > 0) {
			conf.storeController(active_controllers[i]->getConfig());
			logger.logTemperaturePhase(active_controllers[i]->getId(), active_controllers[i]->getConfig().temperaturePhases[tempPhaseId]);
		}
	}
}

void ControllerManager::update()
{
	if (sparkInfo.mode != SPARK_MODE_AUTOMATIC)
		return;

	for(short i=0; i < registered_controllers; i++)
	{
		active_controllers[i]->update();
	}
}

void ControllerManager::loadControllersFromEEPROM()
{
	short stored_controllers = conf.fetchNumberControllers();
	ControllerConfiguration configs[stored_controllers];

	conf.fetchControllers(configs);

	Helper::serialDebug("Reg Controllers: ", false);
	Helper::serialDebug(stored_controllers);

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

BrewController* ControllerManager::getBrewConfiguration(int noBrew)
{
	short brews = 0;

	for(int i=0; i < registered_controllers; i++) {
		if (active_controllers[i]->getConfig().type == TYPE_BREW) {

			if (brews == noBrew) {
				return (BrewController*)active_controllers[i];
			}

			brews++;
		}
	}

	return 0;
}

FridgeController* ControllerManager::getFridgeConfiguration(int noFridge)
{
	short fridges = 0;

	for(int i=0; i < registered_controllers; i++) {
		if (active_controllers[i]->getConfig().type == TYPE_FRIDGE) {

			if (fridges == noFridge) {
				return (FridgeController*)active_controllers[i];
			}

			fridges++;
		}
	}

	return 0;
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
	Helper::serialDebug("Remove controller: ", false);
	Helper::serialDebug(id);

	Controller* new_active_controllers[MAX_CONTROLLERS] = {};
	bool removed = false;
	short new_registered_controllers = 0;

	for(int i=0; i < registered_controllers; i++) {
		if (active_controllers[i]->getId() == id) {
			Helper::serialDebug("EEPROM remove");
			active_controllers[i]->dispose();
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

const char* ControllerManager::getTargetTemperatureJson()
{
	bool notFirst;
	String targetsJson;

	for(int i=0; i < registered_controllers; i++) {

		if (notFirst) {
			targetsJson.concat(',');
		} else {
			notFirst = true;
		}

		targetsJson.concat("{\"config_id\":");
		targetsJson.concat(active_controllers[i]->getId());
		targetsJson.concat(",\"temperature\":");
		targetsJson.concat(active_controllers[i]->getTargetTemperature());
		targetsJson.concat("}");
	}

	return targetsJson.c_str();
}
