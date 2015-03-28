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
#include "Buzzer.h"
#include "Configuration.h"
#include "DeviceInfo.h"
#include "Helper.h"
#include "Settings.h"

extern "C" {
#include "d4d.h"
#include "startup_screen.h"
#include "info_screen.h"
#include "brew_screen.h"
#include "common_screen.h"
}

void updateInformationScreen();


void Screen::init() {        
    
    if (!D4D_Init(NULL))
        return;
    
    D4D_SetOrientation(D4D_ORIENT_LANDSCAPE);
    
    buzzer.init();
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

    updateLabel((D4D_OBJECT*)&scrBrew_curHltOut, (D4D_CHAR*)"74.0 C");
    updateLabel((D4D_OBJECT*)&scrBrew_curMashOut, (D4D_CHAR*)"72.0 C");
    updateLabel((D4D_OBJECT*)&scrBrew_tarMashOut, (D4D_CHAR*)"72.0 C");
}

void Screen::showFerm1Screen()
{
    D4D_ActivateScreen(&screen_info, D4D_TRUE);
}

void Screen::showFerm2Screen()
{
    D4D_ActivateScreen(&screen_info, D4D_TRUE);    
}

void Screen::ticks()
{
    D4D_TimeTickPut();
    D4D_CheckTouchScreen();
    D4D_Poll();
}    

void Screen::update() 
{    
    if (D4D_GetActiveScreen() == &screen_info) {
        updateInformationScreen();
    }
}

void updateInformationScreen() {
    updateLabel((D4D_OBJECT*)&scrInfo_valName, (D4D_CHAR*)deviceInfo.name);
    updateLabel((D4D_OBJECT*)&scrInfo_valMode, (D4D_CHAR*)deviceInfo.mode);
    updateLabel((D4D_OBJECT*)&scrInfo_valId, (D4D_CHAR*)Spark.deviceID().c_str());
    updateLabel((D4D_OBJECT*)&scrInfo_valConfig, (D4D_CHAR*)deviceInfo.config);
    updateLabel((D4D_OBJECT*)&scrInfo_valTemp, (D4D_CHAR*)deviceInfo.tempType);
    updateLabel((D4D_OBJECT*)&scrInfo_valFirmware, (D4D_CHAR*)OINK_BREW_VERSION);
    updateLabel((D4D_OBJECT*)&scrInfo_valIp, (D4D_CHAR*)Helper::getLocalIPStr().c_str());
    updateLabel((D4D_OBJECT*)&scrInfo_valWeb, (D4D_CHAR*)deviceInfo.oinkWeb);    
}

void Screen::calibrateTouchScreen() {
    D4D_CalibrateTouchScreen();
    conf.storeEguiSettings();
}

extern "C" void menuButtonClicked(D4D_OBJECT* pThis)
{
    if (pThis==&scr_btnInfo)
        Screen::showInformationScreen();        
    else if (pThis==&scr_btnBrew)
        Screen::showBrewScreen();
    else if (pThis==&scr_btnFerm1)
        Screen::showFerm1Screen();
    else if (pThis==&scr_btnFerm2)
        Screen::showFerm2Screen();
}
