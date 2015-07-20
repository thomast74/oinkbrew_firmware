/**
 ******************************************************************************
 * @file    Screen.h
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


#ifndef SCREEN_H
#define	SCREEN_H

#include <stdint.h>

enum ScreenType : uint8_t
{
	SCREEN_INFO = 0,
	SCREEN_BREW = 1,
	SCREEN_FERM = 2,
	SCREEN_CONTROLLERS = 3
};

struct Screen {
    /**
     * Initialise the UI components.
     */
    static void init();

    /**
     * Display the startup page and retrieve how long the startup page should be displayed 
     * for in milliseconds before moving on to the main page.
     */
    static void showStartupScreen();
    static void printStatusMessage(const char* messsage);
    static void startupFinished();
    
    /**
     * Display the information page and allow the user to see the current status
     * and the configuration stored on the device
     */
    static void showInformationScreen();

    /**
     * Display the brew page and allow the user to see the current brew sensor information
     */
    static void showBrewScreen();

    /**
     * Display the Ferm 1  page and allow the user to see the current 
     * fermentation chamber 1 sensor data
     */
    static void showFermScreen();

    /**
     * Display the Ferm 2  page and allow the user to see the current 
     * fermentation chamber 1 sensor data
     */
    static void showFerm2Screen();

    /**
     * Called as often as possible by the application. Allows the UI to peform
     * quick background tasks, such as reading the touch screen.
     */
    static void ticks();

    /**
     * Called from the main loop to update the current page and perform event
     * processing.
     */
    static void update(ScreenType screenType);

    /**
     * Show touch screen calibration screen store settings afterwards
     */
    static void calibrateTouchScreen();

};

extern Screen screen;


#endif
