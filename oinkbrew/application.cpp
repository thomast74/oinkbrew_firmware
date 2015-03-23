/**
 ******************************************************************************
 * @file    application.cpp
 * @authors Thomas Trageser
 * @version V0.1
 * @date    2015-03-21
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

/* Includes ------------------------------------------------------------------*/  
#include "application.h"
#include "Helper.h"
#include "Settings.h"
#include "StatusMessage.h"


/* Declarations --------------------------------------------------------------*/  
void applicationInit();
void wifiInit();


SYSTEM_MODE(MANUAL);

/* Global Variables ----------------------------------------------------------*/
static unsigned long lastStatusMessage = -305000;

StatusMessage status;
Helper helper;


/*******************************************************************************
 * Function Name  : setup
 * Description    : configure device after startup
 * Input          : 
 * Output         : 
 * Return         : 
 ******************************************************************************/
void setup()
{
    if (Helper::isDebug())
    {        
        Serial.begin(9600);
        delay(2000);
    }
    
    // turn on and configure WiFi
    wifiInit();
    
    // initialise application
    applicationInit();
}

/*******************************************************************************
 * Function Name  : loop
 * Description    : main application routine
 * Input          : 
 * Output         : 
 * Return         : 
 ******************************************************************************/
void loop()
{
    
    if((millis() - lastStatusMessage) >= DURATION_MESSAGE)
    {
        Helper::serialDebug("Loop wants to send status message");
        lastStatusMessage = millis();
        StatusMessage::send();
    }
}

/*******************************************************************************
 * Function Name  : applicationInit
 * Description    : initialise everything for the application to run
 * Input          : 
 * Output         : 
 * Return         : 
 ******************************************************************************/
void applicationInit()
{
}

/*******************************************************************************
 * Function Name  : wifiInit
 * Description    : turn on WiFi and starts listening mode if not configured
 * Input          : 
 * Output         : 
 * Return         : 
 ******************************************************************************/
void wifiInit()
{
    Helper::serialDebug("Turn on WiFi");
    WiFi.on();

    if (!WiFi.hasCredentials())
    {
        Helper::serialDebug("No credentials, change to Listen mode after connect");
    }
    
    Helper::serialDebug("Connect to WiFi");
    WiFi.connect();
    
    // wait until WiFi is ready
    while (!WiFi.ready())
    {
        delay(500);
    }

    // connect to configured WiFi, but wait a bit to get IP Address
    delay(2000);
    
    Helper::serialDebug("WiFi ready");
}
