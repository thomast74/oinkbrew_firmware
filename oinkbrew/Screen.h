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

extern "C" {
#include "d4d.h"
}


struct Screen {
    /**
     * Initialise the UI components.
     */
    static void init();

    /**
     * Display the startup page and retrieve how long the startup page should be displayed 
     * for in milliseconds before moving on to the main page.
     */
    static void showStartupPage();
    static void printStatusMessage(const char* messsage);
    
    /**
     * Display the home page and allow the user to see the current status of devices
     * and the configuration stored on the device
     */
    static void showHomePage();

    /**
     * Called as often as possible by the application. Allows the UI to peform
     * quick background tasks, such as reading the touch screen.
     */
    static void ticks();

    /**
     * Called from the main loop to update the current page and perform event
     * processing.
     */
    static void update();

    /**
     * Show touch screen calibration screen store settings afterwards
     */
    static void calibrateTouchScreen();

};

extern Screen screen;


#endif