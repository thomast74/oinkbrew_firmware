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
#include "Configuration.h"
#include "Helper.h"
#include "Settings.h"
#include "StatusMessage.h"
#include "Screen.h"
#include "SparkInfo.h"
#include "TcpListener.h"
#include "TcpLogger.h"
#include "controller/ControllerManager.h"

/* Declarations --------------------------------------------------------------*/  
void applicationInit();
void wifiInit();


static unsigned long lastRun = -1000;
static unsigned long lastLog = 0;
static unsigned long lastMsg = -121000;


SYSTEM_MODE(MANUAL);


SparkInfo sparkInfo;
TcpListener listener;
TcpLogger logger;


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
    
    conf.init();

    screen.init();
    screen.showStartupScreen();
    
    // turn on and configure WiFi
    wifiInit();
    
    // initialise application
    applicationInit();
        
    screen.startupFinished();
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
	unsigned long time = millis();

    // update screen and check for touch input
    //screen.ticks();


    // every second read actuator and sensor values
    if((time - lastRun) >= DURATION_RUN)
    {
        lastRun = time;
        deviceManager.readValues();

        // process controllers and control temperature
        controllerManager.process();
    }

    // every 15 seconds log actuator and sensor values
    if((time - lastLog) >= DURATION_LOG)
    {
    	lastLog = time;
    	deviceManager.findNewDevices();
    	logger.logDeviceValues();
    }

    // every 2 minutes send a status message
    if((time - lastMsg) >= DURATION_MSG)
    {
        lastMsg = time;
        StatusMessage::send();
    }    

    // check for client connectivity
	if (listener.connected())
	{
		//screen.update();
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
    screen.printStatusMessage("Load configuration data");
    conf.loadDeviceInfo();

    screen.printStatusMessage("Start TCP Server");
    listener.init();
    logger.init();

    screen.printStatusMessage("Initialise actuators and sensors");
    deviceManager.init();
    deviceManager.loadDevicesFromEEPROM();

    screen.printStatusMessage("Initialise controllers");
    controllerManager.loadControllersFromEEPROM();
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
    screen.printStatusMessage("Turn on WiFi");
    WiFi.on();

    if (!WiFi.hasCredentials())
    {
        screen.printStatusMessage("No credentials, change to Listen mode after connect");
    }
    
    screen.printStatusMessage("Connect to WiFi");
    WiFi.connect();
    
    // wait until WiFi is ready
    while (!WiFi.ready())
    {
        delay(500);
    }
    
    delay(1000);        
    screen.printStatusMessage("WiFi ready");
}
