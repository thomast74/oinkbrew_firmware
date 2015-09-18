/**
 ******************************************************************************
 * @file    Screen.cpp
 * @authors Thomas Trageser
 * @version V0.1
 * @date    2015-03-24
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

#include "Screen.h"
#include "devices/Buzzer.h"
#include "controller/ControllerConfiguration.h"
#include "controller/ControllerManager.h"
#include "controller/BrewController.h"
#include "devices/DeviceManager.h"
#include "Helper.h"
#include "Settings.h"
#include "SparkInfo.h"

extern "C"
{
#include "d4d.h"
#include "startup_screen.h"
#include "info_screen.h"
#include "common_screen.h"
#include "widget_color_scheme.h"
}


void updateInformationScreen();


void Screen::init()
{
	if (!D4D_Init((D4D_SCREEN*) NULL))
		return;

	D4D_SetOrientation(D4D_ORIENT_LANDSCAPE);

	buzzer.beep(1, 100);
}

void Screen::showStartupScreen()
{
	D4D_ActivateScreen(&screen_startup, D4D_TRUE);
	D4D_Poll();

	Helper::serialDebug(OINK_BREW_VERSION_STRING);
	ScreenStartup_UpdateVersion(OINK_BREW_VERSION_STRING);
}

void Screen::printStatusMessage(const char* message)
{
	ScreenStartup_UpdateMessage(message);
	Helper::serialDebug(message);
}

void Screen::startupFinished()
{
	buzzer.beep(2, 250);
	printStatusMessage("Running");
	showInformationScreen();
}

void Screen::showInformationScreen()
{
	D4D_ActivateScreen(&screen_info, D4D_TRUE);
	updateInformationScreen();
}

void Screen::ticks()
{
	D4D_TimeTickPut();
	D4D_CheckTouchScreen();
	D4D_Poll();
}

void Screen::update()
{
	updateInformationScreen();
}

void updateInformationScreen()
{
	updateLabel((D4D_OBJECT*) &scrInfo_valName, (D4D_CHAR*) sparkInfo.name);
	updateLabel((D4D_OBJECT*) &scrInfo_valId, (D4D_CHAR*) Spark.deviceID().c_str());
	updateLabel((D4D_OBJECT*) &scrInfo_valFirmware, (D4D_CHAR*) OINK_BREW_VERSION);
	updateLabel((D4D_OBJECT*) &scrInfo_valIp, (D4D_CHAR*) Helper::getLocalIpStr().c_str());

	String oinkWeb = Helper::getIpStr(IPAddress(sparkInfo.oinkWeb));
	oinkWeb.concat(":");
	oinkWeb.concat(sparkInfo.oinkWebPort);
	updateLabel((D4D_OBJECT*) &scrInfo_valWeb, (D4D_CHAR*) oinkWeb.c_str());
}
