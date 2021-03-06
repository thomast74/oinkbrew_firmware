/**
 ******************************************************************************
 * @file    Helper.h
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

#ifndef HELPER_H
#define	HELPER_H


#include "spark_wiring_string.h"
#include "spark_wiring_ipaddress.h"


class Helper {
public:   
    static bool isDebug();
    static void serialDebug(const char* message, bool lineFeed = true);
    //static void serialDebug(int8_t message, bool lineFeed = true);
    static void serialDebug(float number, bool lineFeed = true);

    static String getIpStr(IPAddress ip);
    static void getRawIp(const char* ipString, uint8_t* address);
    static IPAddress getLocalIp();
    static IPAddress getBroadcastAddress();
    static String getLocalIpStr();

    static void getBytes(const uint8_t* data, uint8_t len, char* buf);
    static void setBytes(uint8_t* data, const char* s, uint8_t len);

    static bool matchAddress(uint8_t* detected, uint8_t* configured, uint8_t count);
};

extern Helper helper;


#endif
