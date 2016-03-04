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
#include "Screen.h"
#include "SparkInfo.h"
#include "TcpListener.h"
#include "TcpLogger.h"
#include "controller/ControllerManager.h"

/* Declarations --------------------------------------------------------------*/  
void initialise();
void processing();
void wifiInit();

static bool initialised = false;
static unsigned long lastRun = -1000;
static unsigned long lastLog = 0;


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

    screen.init();
    screen.showStartupScreen();
    
    wifiInit();
    
    screen.printStatusMessage("Start TCP Server");
    listener.init();
    logger.init();

    screen.printStatusMessage("Initialise actuators and sensors");
    deviceManager.init();
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

/*******************************************************************************
 * Function Name  : loop
 * Description    : main application routine
 * Input          : 
 * Output         : 
 * Return         : 
 ******************************************************************************/
void loop()
{
	if (!initialised) {
		initialise();
	}
	else {
		processing();
	}
}

/*******************************************************************************
 * Function Name  : initialise
 * Description    : initialise everything for the device to run
 * Input          :
 * Output         :
 * Return         :
 ******************************************************************************/
void initialise()
{
	if (!sparkInfo.requested && !sparkInfo.received) {
		StatusMessage::send();
		sparkInfo.requested = true;
	}
	else if (sparkInfo.received) {
		deviceManager.findNewDevices();
		logger.requestConfigurations();
		initialised = true;
	}
}

/*******************************************************************************
 * Function Name  : processing
 * Description    : main loop for the controller
 * Input          :
 * Output         :
 * Return         :
 ******************************************************************************/
void processing()
{
	unsigned long time = millis();

    if((time - lastRun) >= DURATION_RUN)
    {
        lastRun = time;
        deviceManager.readValues();
        controllerManager.process();
    }

	controllerManager.update();

    if((time - lastLog) >= DURATION_LOG)
    {
    	lastLog = time;
    	deviceManager.findNewDevices();
    	logger.logDeviceValues();
    }

    // check for client connectivity
	if (listener.connected())
	{
		screen.update();
	}
}
