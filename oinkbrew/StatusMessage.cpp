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
#include "spark_wiring_udp.h"
#include "spark_wiring_wifi.h"

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

    Helper::serialDebug("Create Json Status Message");
    String jsonMessage = "{\"device_id\":\"";
    jsonMessage.concat(Spark.deviceID().c_str());
    jsonMessage.concat("\",\"device_mode\":\"");
    jsonMessage.concat("MANUAL");
    jsonMessage.concat("\",\"device_config\":\"");
    jsonMessage.concat("0.0");
    jsonMessage.concat("\", \"firmware_version\":\"");
    jsonMessage.concat(OINK_BREW_VERSION);
    jsonMessage.concat("\",\"board_revision\":\"");
    jsonMessage.concat(BREWPI_SPARK_REVISION);
    jsonMessage.concat("\",\"ip_address\":\"");
    jsonMessage.concat(StatusMessage::getLocalIPStr());
    jsonMessage.concat("\"}");

    Helper::serialDebug("Send status message");
    UDP udp;
    udp.begin(LISTENER_PORT);
    udp.beginPacket(StatusMessage::getBroadcastAddress(), LISTENER_PORT);

    udp.write(jsonMessage.c_str());

    udp.endPacket();
    Helper::serialDebug("Status message sent");
}


/*******************************************************************************
 * Function Name  : getLocalIPStr
 * Description    : convert WiFi.localIP into a string
 * Input          : 
 * Output         : broadcast address as IPAddress
 * Return         : 
 ******************************************************************************/
String StatusMessage::getLocalIPStr()
{
    uint8_t* address = spark::WiFi.localIP().raw_address();
    
    String ipAddressStr = "";
    ipAddressStr.concat(address[0]);
    ipAddressStr.concat(".");
    ipAddressStr.concat(address[1]);
    ipAddressStr.concat(".");
    ipAddressStr.concat(address[2]);
    ipAddressStr.concat(".");
    ipAddressStr.concat(address[3]);
    
    return ipAddressStr;
}

/*******************************************************************************
 * Function Name  : getBroadcastAddress
 * Description    : calculate the broadcast address from localIP and subnetmask
 * Input          : 
 * Output         : broadcast address as IPAddress
 * Return         : 
 ******************************************************************************/
IPAddress StatusMessage::getBroadcastAddress()
{
    IPAddress local_ip = spark::WiFi.localIP();
    IPAddress network_mask = spark::WiFi.subnetMask();
    IPAddress broadcast_addr;
    
    int i;
    for( i=0; i<=3; i++) {
        broadcast_addr[i] = local_ip[i] | (~ network_mask[i]);
    }
    
    return broadcast_addr;    
}