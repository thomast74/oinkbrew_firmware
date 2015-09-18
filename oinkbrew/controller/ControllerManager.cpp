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
#include "../Helper.h"
#include "../SparkInfo.h"
#include "../TcpLogger.h"

Controller* ControllerManager::active_controllers[MAX_CONTROLLERS] = {};
short ControllerManager::registered_controllers = 0;


void ControllerManager::process()
{
	for(short i=0; i < registered_controllers; i++)
	{
		active_controllers[i]->process();
	}
}

void ControllerManager::update()
{
	for(short i=0; i < registered_controllers; i++)
	{
		active_controllers[i]->update();
	}
}

bool ControllerManager::changeController(ControllerConfiguration request)
{
	int index = findController(request.id);

	if (index >= 0) {
		active_controllers[index]->dispose();
		active_controllers[index]->setConfig(request);
	}
	else {
		if (request.type == TYPE_BREW) {
			active_controllers[registered_controllers] = new BrewController(request);
			registered_controllers++;
		}
		else if (request.type == TYPE_FRIDGE) {
			active_controllers[registered_controllers] = new FridgeController(request);
			registered_controllers++;
		}
		else {
			return false;
		}
	}

	return true;
}

bool ControllerManager::removeController(int id)
{
	Controller* new_active_controllers[MAX_CONTROLLERS] = {};
	bool removed = false;
	short new_registered_controllers = 0;

	for(int i=0; i < registered_controllers; i++) {
		if (active_controllers[i]->getId() == id) {
			Helper::serialDebug("EEPROM remove");
			active_controllers[i]->dispose();
			delete active_controllers[i];

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
	for(short i=0; i < registered_controllers; i++) {
		if (active_controllers[i]->getId() == id) {
			return i;
		}
	}

	return -1;
}

const char* ControllerManager::getTargetTemperatureJson()
{
	bool notFirst = false;
	String targetsJson;

	for(short i=0; i < registered_controllers; i++) {

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
