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


/* Function prototypes -------------------------------------------------------*/
void wifiInit();
void serialDebug(String, bool = true);

SYSTEM_MODE(MANUAL);

#ifdef DEBUG_BUILD    
bool debug = true;
#else
bool debug = false;
#endif

/*******************************************************************************
 * Function Name  : setup
 * Description    : configure device after startup
 * Input          : 
 * Output         : 
 * Return         : 
 ******************************************************************************/
void setup()
{
    if (debug)
    {        
        Serial.begin(9600);
        delay(2000);
    }
    
    // turn on and configure WiFi
    wifiInit();
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
    serialDebug("Turn on WiFi");
    WiFi.on();

    if (!WiFi.hasCredentials())
    {
        serialDebug("No credentials, change to Listen mode after connect");
    }
    
    serialDebug("Connect to WiFi");
    WiFi.connect();
    
    // wait until WiFi is ready
    while (!WiFi.ready())
    {
        delay(500);
    }    // connect to configured WiFi

    
    serialDebug("WiFi ready");
}

/*******************************************************************************
 * Function Name  : serialDebug
 * Description    : log to serial interface if debug build
 * Input          : message to log and if lineFeed should be added to the end
 * Output         : Serial print via USB
 * Return         : 
 ******************************************************************************/
void serialDebug(String message, bool lineFeed)
{
    if (debug)
    {
        if (lineFeed)
            Serial.println(message);
        else
            Serial.print(message);        
    }
}