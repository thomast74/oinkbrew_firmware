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
#include "inet_hal.h"
#include "spark_wiring_ipaddress.h"
#include "spark_wiring_string.h"
#include "spark_wiring_usbserial.h"
#include "spark_wiring_wifi.h"
#include "Settings.h"


static IPAddress NO_IP = IPAddress(0, 0, 0, 0);
static IPAddress LOCAL_ADDR = IPAddress(0, 0, 0, 0);
static IPAddress BROADCAST_ADDR = IPAddress(0, 0, 0, 0);


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
        Serial.flush();
    }
}

void Helper::serialDebug(int8_t message, bool lineFeed) {
    if (Helper::isDebug()) {
        if (lineFeed)
            Serial.println(message);
        else
            Serial.print(message);
        Serial.flush();
    }
}

/*******************************************************************************
 * Function Name  : getLocalIPStr
 * Description    : convert WiFi.localIP into a string
 * Input          : 
 * Output         : broadcast address as IPAddress
 * Return         : 
 ******************************************************************************/
IPAddress Helper::getLocalIp()
{
    if (LOCAL_ADDR == NO_IP) 
    {
        LOCAL_ADDR = spark::WiFi.localIP();
    }
    
    return LOCAL_ADDR;
}


/*******************************************************************************
 * Function Name  : getLocalIPStr
 * Description    : convert WiFi.localIP into a string
 * Input          : 
 * Output         : broadcast address as IPAddress
 * Return         : 
 ******************************************************************************/
String Helper::getLocalIpStr()
{
	IPAddress address = getLocalIp();
    
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
 * Function Name  : getIpStr
 * Description    : convert IPAddress into a String object
 * Input          : String representation of the IPAddress
 * Output         :
 * Return         :
 ******************************************************************************/
String Helper::getIpStr(IPAddress ip)
{
    String ipAddressStr = "";
    ipAddressStr.concat(ip[0]);
    ipAddressStr.concat(".");
    ipAddressStr.concat(ip[1]);
    ipAddressStr.concat(".");
    ipAddressStr.concat(ip[2]);
    ipAddressStr.concat(".");
    ipAddressStr.concat(ip[3]);

    return ipAddressStr;
}

/*******************************************************************************
 * Function Name  : getIp
 * Description    : Convert a char* into a IPAddress object
 * Input          : IPAddress
 * Output         :
 * Return         :
 ******************************************************************************/
void Helper::getRawIp(const char * ipString, uint8_t* address) {

	String strIpAddress = ipString;

	int startIndex = 0;
	int endIndex = strIpAddress.indexOf('.');
	if (endIndex > 0) {
		address[0] = strIpAddress.substring(startIndex, endIndex).toInt();
		startIndex = endIndex + 1;
	}

	endIndex = strIpAddress.indexOf('.', startIndex);
	if (endIndex > 0) {
		address[1] = strIpAddress.substring(startIndex, endIndex).toInt();
		startIndex = endIndex + 1;
	}

	endIndex = strIpAddress.indexOf('.', startIndex);
	if (endIndex > 0) {
		address[2] = strIpAddress.substring(startIndex, endIndex).toInt();
		startIndex = endIndex + 1;
	}
	address[3] = strIpAddress.substring(startIndex).toInt();

}

/*******************************************************************************
 * Function Name  : getBroadcastAddress
 * Description    : calculate the broadcast address from localIP and subnetmask
 * Input          : 
 * Output         : broadcast address as IPAddress
 * Return         : 
 ******************************************************************************/
IPAddress Helper::getBroadcastAddress()
{
    if (BROADCAST_ADDR == NO_IP) {
        IPAddress network_mask = spark::WiFi.subnetMask();

        int i;
        for( i=0; i<=3; i++) {
            BROADCAST_ADDR[i] = getLocalIp()[i] | (~ network_mask[i]);
        }
    }
    
    return BROADCAST_ADDR;
}

/*******************************************************************************
 * Function Name  : getBytes
 * Description    : convert uint8_t into char*
 * Input          :
 * Output         : broadcast address as IPAddress
 * Return         :
 ******************************************************************************/
void Helper::getBytes(const uint8_t* data, uint8_t len, char* buf) {
	for (int i = 0; i < len; i++) {
		uint8_t b = (data[i] >> 4) & 0x0f;
		*buf++ = (b > 9 ? b - 10 + 'A' : b + '0');
		b = data[i] & 0x0f;
		*buf++ = (b > 9 ? b - 10 + 'A' : b + '0');
	}
	*buf = 0;
}

/*******************************************************************************
 * Function Name  : setBytes
 * Description    : convert const char* into uint8_t
 * Input          :
 * Output         : broadcast address as IPAddress
 * Return         :
 ******************************************************************************/
void Helper::setBytes(uint8_t* data, const char* s, uint8_t len) {
	char c;
	while ((c = *s++)) {
		uint8_t d = (c >= 'A' ? c - 'A' + 10 : c - '0') << 4;
		c = *s++;
		d |= (c >= 'A' ? c - 'A' + 10 : c - '0');
		*data++ = d;
	}
}

/*******************************************************************************
 * Function Name  : matchAddress
 * Description    : tests if two DeviceAddress are the same
 * Input          : hw_adress to check and the number of bytes
 * Output         : true if a match, false if not matching
 * Return         :
 ******************************************************************************/
bool Helper::matchAddress(uint8_t* detected, uint8_t* configured, uint8_t count) {

	if (!configured[0])
		return true;

	while (count-- > 0) {
		if (detected[count] != configured[count])
			return false;
	}

	return true;
}
