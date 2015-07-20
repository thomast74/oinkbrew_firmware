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
#include "Configuration.h"
#include "Helper.h"
#include "Settings.h"
#include "SparkInfo.h"

extern "C"
{
#include "d4d.h"
#include "startup_screen.h"
#include "info_screen.h"
#include "brew_screen.h"
#include "ferm_screen.h"
#include "common_screen.h"
#include "widget_color_scheme.h"
}


bool hasBeerController = false;
bool setBackgroundColor(const D4D_OBJECT* pThis, D4D_COLOR bg);
void updateInformationScreen();
void updateBrewScreen();
void updateFermScreen();


void Screen::init()
{
	if (!D4D_Init((D4D_SCREEN*) NULL))
		return;

	D4D_SetOrientation(D4D_ORIENT_LANDSCAPE);

	buzzer.beep(1, 100);

	if (!conf.loadEguiSettings()) {
		calibrateTouchScreen();
	}
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

void Screen::showBrewScreen()
{
	D4D_ActivateScreen(&screen_brew, D4D_TRUE);
	updateBrewScreen();
}

void Screen::showFermScreen()
{
	D4D_ActivateScreen(&screen_ferm, D4D_TRUE);
}

void Screen::ticks()
{
	D4D_TimeTickPut();
	D4D_CheckTouchScreen();
	D4D_Poll();
}

void Screen::update(ScreenType screenType)
{
	D4D_SCREEN* activeScreen =  D4D_GetActiveScreen();

	if (screenType == SCREEN_INFO && activeScreen == &screen_info) {
		updateInformationScreen();
	}
	else if ((screenType == SCREEN_BREW || screenType == SCREEN_CONTROLLERS) && activeScreen == &screen_brew) {
		updateBrewScreen();
	}
	else if ((screenType == SCREEN_FERM || screenType == SCREEN_CONTROLLERS) && activeScreen == &screen_ferm) {
		updateFermScreen();
	}
}

bool setBackgroundColor(const D4D_OBJECT* pThis, D4D_COLOR bg)
{
    D4D_COLOR existing = pThis->clrScheme->bckg;
    pThis->clrScheme->bckg = bg;
    pThis->clrScheme->bckgDis = bg;
    pThis->clrScheme->bckgCapture = bg;
    pThis->clrScheme->bckgFocus = bg;
    if (existing!=bg)
        D4D_InvalidateObject(pThis, D4D_TRUE);
    return existing!=bg;
}

void updateInformationScreen()
{
	char mode[] = { sparkInfo.mode };
	char tempType[] = { sparkInfo.tempType };

	updateLabel((D4D_OBJECT*) &scrInfo_valName, (D4D_CHAR*) sparkInfo.name);
	updateLabel((D4D_OBJECT*) &scrInfo_valMode, (D4D_CHAR*) mode);
	updateLabel((D4D_OBJECT*) &scrInfo_valId, (D4D_CHAR*) Spark.deviceID().c_str());
	updateLabel((D4D_OBJECT*) &scrInfo_valTemp, (D4D_CHAR*) tempType);
	updateLabel((D4D_OBJECT*) &scrInfo_valFirmware, (D4D_CHAR*) OINK_BREW_VERSION);
	updateLabel((D4D_OBJECT*) &scrInfo_valIp, (D4D_CHAR*) Helper::getLocalIpStr().c_str());

	String oinkWeb = Helper::getIpStr(IPAddress(sparkInfo.oinkWeb));
	oinkWeb.concat(":");
	oinkWeb.concat(sparkInfo.oinkWebPort);
	updateLabel((D4D_OBJECT*) &scrInfo_valWeb, (D4D_CHAR*) oinkWeb.c_str());
}

void updateBrewScreen()
{
    BrewController* controller = controllerManager.getBrewConfiguration(0);

    if (controller != 0) {

    	ActiveDevice device;
    	deviceManager.getDevice(controller->getConfig().tempSensor.pin_nr, controller->getConfig().tempSensor.hw_address, device);

    	if (device.type == DEVICE_HARDWARE_ONEWIRE_TEMP) {

    		hasBeerController = true;

    		float minTarget = controller->getTargetTemperature() - 0.5;
    		float maxTarget = controller->getTargetTemperature() + 0.5;

    		D4D_COLOR bg = OINK_COLOR_DARKGREY;
    		if (minTarget <= device.value && device.value <= maxTarget) {
    			bg = D4D_COLOR_RGB(0xb3, 0x98, 0x00);
    		}
    		else if (minTarget > device.value) {
    			bg = D4D_COLOR_RGB(0x00, 0x4b, 0xb4);
    		}
    		else if (device.value > maxTarget) {
    			bg = D4D_COLOR_RGB(0xb4, 0x00, 0x00);
    		}

    		char cCurrentTemp[8], cTargetTemp[8], cDurationToGo[8];

    		float currentTemp = device.value;
    		float targetTemp = controller->getTargetTemperature();

    		if (sparkInfo.tempType == 'F') {
    			currentTemp = (currentTemp * 1.8) + 32.0;
    			targetTemp = (targetTemp * 1.8) + 32;
    		}

    		int seconds = (int) (controller->timeToGo() / 1000) % 60 ;
    		int minutes = (int) ((controller->timeToGo() / (1000*60)) % 60);

    		sprintf (cCurrentTemp,  "%5.1f ", currentTemp);
    		sprintf (cTargetTemp,   "%5.1f ", targetTemp);
    		sprintf (cDurationToGo, "%2i:%02i m", minutes, seconds);

    		cCurrentTemp[6] = sparkInfo.tempType;
    		cTargetTemp[6] = sparkInfo.tempType;

			updateLabel((D4D_OBJECT*)&scrBrew_Name, (D4D_CHAR*)controller->getConfig().name);

    		switch (controller->getConfig().tempSensor.function) {
    		case DEVICE_FUNCTION_HLT_IN_TEMP_SENSOR:
    		case DEVICE_FUNCTION_HLT_INSIDE_TEMP_SENSOR:
    		case DEVICE_FUNCTION_HLT_OUT_TEMP_SENSOR:
					updateLabel((D4D_OBJECT*)&scrBrew_curHlt, (D4D_CHAR*)cCurrentTemp);
					updateLabel((D4D_OBJECT*)&scrBrew_tarHlt, (D4D_CHAR*)cTargetTemp);
					updateLabel((D4D_OBJECT*)&scrBrew_togoHlt, (D4D_CHAR*)cDurationToGo);
					setBackgroundColor((D4D_OBJECT*)&scrBrew_curHlt, bg);
					break;
    		case DEVICE_FUNCTION_MASH_IN_TEMP_SENSOR:
    		case DEVICE_FUNCTION_MASH_INSIDE_TEMP_SENSOR:
    		case DEVICE_FUNCTION_MASH_OUT_TEMP_SENSOR:
					updateLabel((D4D_OBJECT*)&scrBrew_curMash, (D4D_CHAR*)cCurrentTemp);
					updateLabel((D4D_OBJECT*)&scrBrew_tarMash, (D4D_CHAR*)cTargetTemp);
					updateLabel((D4D_OBJECT*)&scrBrew_togoMash, (D4D_CHAR*)cDurationToGo);
					setBackgroundColor((D4D_OBJECT*)&scrBrew_curMash, bg);
					break;
    		case DEVICE_FUNCTION_BOIL_IN_TEMP_SENSOR:
    		case DEVICE_FUNCTION_BOIL_INSIDE_TEMP_SENSOR:
    		case DEVICE_FUNCTION_BOIL_OUT_TEMP_SENSOR:
					updateLabel((D4D_OBJECT*)&scrBrew_curBoil, (D4D_CHAR*)cCurrentTemp);
					updateLabel((D4D_OBJECT*)&scrBrew_tarBoil, (D4D_CHAR*)cTargetTemp);
					updateLabel((D4D_OBJECT*)&scrBrew_togoBoil, (D4D_CHAR*)cDurationToGo);
					setBackgroundColor((D4D_OBJECT*)&scrBrew_curBoil, bg);
					break;
    		}
    	}
    }
    else
    {
    	if (hasBeerController) {

			updateLabel((D4D_OBJECT*)&scrBrew_Name, (D4D_CHAR*)"");

			updateLabel((D4D_OBJECT*)&scrBrew_curHlt, (D4D_CHAR*)"-.-");
			updateLabel((D4D_OBJECT*)&scrBrew_tarHlt, (D4D_CHAR*)"-.-");
			updateLabel((D4D_OBJECT*)&scrBrew_togoHlt, (D4D_CHAR*)"");
			setBackgroundColor((D4D_OBJECT*)&scrBrew_curHlt, OINK_COLOR_DARKGREY);

			updateLabel((D4D_OBJECT*)&scrBrew_curMash, (D4D_CHAR*)"-.-");
			updateLabel((D4D_OBJECT*)&scrBrew_tarMash, (D4D_CHAR*)"-.-");
			updateLabel((D4D_OBJECT*)&scrBrew_togoMash, (D4D_CHAR*)"");
			setBackgroundColor((D4D_OBJECT*)&scrBrew_curMash, OINK_COLOR_DARKGREY);

			updateLabel((D4D_OBJECT*)&scrBrew_curBoil, (D4D_CHAR*)"-.-");
			updateLabel((D4D_OBJECT*)&scrBrew_tarBoil, (D4D_CHAR*)"-.-");
			updateLabel((D4D_OBJECT*)&scrBrew_togoBoil, (D4D_CHAR*)"");
			setBackgroundColor((D4D_OBJECT*)&scrBrew_curBoil, OINK_COLOR_DARKGREY);

    		hasBeerController = false;
    	}
    }
}

void updateFermScreen()
{

}

void Screen::calibrateTouchScreen()
{
	D4D_CalibrateTouchScreen();
	conf.storeEguiSettings();
}

extern "C" void menuButtonClicked(D4D_OBJECT* pThis)
{
	if (pThis == &scr_btnInfo)
		Screen::showInformationScreen();
	else if (pThis == &scr_btnBrew)
		Screen::showBrewScreen();
	else if (pThis == &scr_btnFerm)
		Screen::showFermScreen();
}
