/**
 ******************************************************************************
 * @file    Helper.cpp
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
#include "Helper.h"
#include "spark_wiring_usbserial.h"


/*******************************************************************************
 * Function Name  : isDebug
 * Description    : returns if this build is a debug compile
 * Input          : 
 * Output         : True for debug build, False for release build
 * Return         : 
 ******************************************************************************/
bool Helper::isDebug() {
#ifdef DEBUG_BUILD    
    return true;
#else
    return false;
#endif
}

/*******************************************************************************
 * Function Name  : serialDebug
 * Description    : log to serial interface if debug build
 * Input          : message to log and if lineFeed should be added to the end
 * Output         : Serial print via USB
 * Return         : 
 ******************************************************************************/
void Helper::serialDebug(const char* message, bool lineFeed) {
    if (Helper::isDebug()) {
        if (lineFeed)
            Serial.println(message);
        else
            Serial.print(message);
    }
}