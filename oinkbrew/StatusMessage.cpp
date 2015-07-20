/**
 ******************************************************************************
 * @file    StatusMessage.cpp
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
#include "StatusMessage.h"
#include "Helper.h"
#include "Settings.h"
#include "spark_wiring_time.h"
#include "spark_wiring_udp.h"
#include "spark_wiring_wifi.h"
#include "SparkInfo.h"
#include <stdio.h>

/*******************************************************************************
 * Function Name  : send
 * Description    : send a broadcast message via UDP
 * Input          : 
 * Output         : 
 * Return         : 
 ******************************************************************************/
void StatusMessage::send() {
    
    if (!spark::WiFi.ready())
        return;
    
    String jsonMessage = "{\"device_id\":\"";
    jsonMessage.concat(Spark.deviceID().c_str());
    jsonMessage.concat("\",\"datetime\":");
    jsonMessage.concat(Time.now());
    jsonMessage.concat(",\"device_mode\":\"");
    jsonMessage.concat(sparkInfo.mode);
    jsonMessage.concat("\", \"firmware_version\":\"");
    jsonMessage.concat(OINK_BREW_VERSION);
    jsonMessage.concat("\",\"ip_address\":\"");
    jsonMessage.concat(Helper::getLocalIpStr().c_str());
    jsonMessage.concat("\",\"web_address\":\"");

    char buf[16];
    sprintf(buf, "%i.%i.%i.%i", sparkInfo.oinkWeb[0], sparkInfo.oinkWeb[1], sparkInfo.oinkWeb[2], sparkInfo.oinkWeb[3]);
    jsonMessage.concat(buf);

    jsonMessage.concat("\",\"web_port\":\"");
    jsonMessage.concat(sparkInfo.oinkWebPort);
    jsonMessage.concat("\"}");

    UDP udp;
    udp.begin(REMOTE_LISTENER_PORT-1);
    udp.beginPacket(Helper::getBroadcastAddress(), REMOTE_LISTENER_PORT);

    udp.write(jsonMessage.c_str());

    udp.endPacket();

    delay(100);

    unsigned long startTime = millis();
    while (udp.available() == 0 && (millis() - startTime) < 1000) { }

    startTime = millis();
    while (udp.available() != 0 && (millis() - startTime) < 1000) {
    	udp.read();
        delay(20);
    }

    udp.stop();
    delay(20);
}
