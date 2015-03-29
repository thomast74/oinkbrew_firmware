/**
 ******************************************************************************
 * @file    TcpListener.cpp
 * @authors Thomas Trageser
 * @version V0.1
 * @date    2015-03-28
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

#include "TcpListener.h"
#include "Configuration.h"
#include "DeviceInfo.h"
#include "Helper.h"
#include "Settings.h"
#include "spark_wiring_tcpclient.h"
#include "spark_wiring_tcpserver.h"


TCPServer server = TCPServer(LOCAL_LISTENER_PORT);
TCPClient client;

void TcpListener::init() {
    server.begin();
}

bool TcpListener::connected() {

    bool needsScreenUpdate = false;
    
    if (client.connected()) {
        if (client.available()) {
            needsScreenUpdate = processRequest(client.read());
            client.flush();
            client.stop();
        }
    } else {
        client = server.available();
    }
    
    return needsScreenUpdate;
}

bool TcpListener::processRequest(char action) {
    switch (action) {
            // do nothing wrong request
        case ' ':
        case '\n':
        case '\r':
            break;
            // status message receiving
        case 'd':
            parseJson(&TcpListener::processDeviceInfo, NULL);
            conf.storeDeviceInfo();
            return true;
    }
    
    return false;
}

void TcpListener::processDeviceInfo(const char * key, const char * val, void* pv) {
    if (strcmp(key, "name") == 0)
        memcpy(&deviceInfo.name, val, strlen(val) + 1);
    else if (strcmp(key, "mode") == 0)
        memcpy(&deviceInfo.mode, val, strlen(val) + 1);
    else if (strcmp(key, "config") == 0)
        memcpy(&deviceInfo.config, val, strlen(val) + 1);
    else if (strcmp(key, "tempType") == 0)
        memcpy(&deviceInfo.tempType, val, strlen(val) + 1);
    else if (strcmp(key, "oinkweb") == 0)
        memcpy(&deviceInfo.oinkWeb, val, strlen(val) + 1);
}

void TcpListener::parseJson(ParseJsonCallback fn, void* data) {
    char key[30];
    char val[30];
    *key = 0;
    *val = 0;
    bool next = true;
    // read first open brace	
    int c = readNext();
    if (c != '{') {
        return;
    }
    do {
        next = parseJsonToken(key) && parseJsonToken(val);
        if (val[0] && key[0]) {
            fn(key, val, data);
        }
    } while (next);
}

bool TcpListener::parseJsonToken(char* val) {
    uint8_t index = 0;
    val[0] = 0;
    bool result = true;
    for (;;) // get value
    {
        int character = readNext();
        if (index == 29 || character == '}' || character == -1) {
            result = false;
            break;
        }
        if (character == ',' || character == ':') // end of value
            break;
        if (character == '"') {
            ; // skip spaces and apostrophes
        } else
            val[index++] = character;
    }
    val[index] = 0; // null terminate string
    return result;
}

int TcpListener::readNext() {
    uint8_t retries = 0;
    while (client.available() == 0) {
        delay(100);
        retries++;
        if (retries >= 10) {
            return -1;
        }
    }
    return client.read();
}

