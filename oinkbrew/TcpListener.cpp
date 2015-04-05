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
#include "devices/DeviceManager.h"
#include "Helper.h"
#include "Settings.h"
#include "SparkInfo.h"
#include "spark_wiring_tcpclient.h"
#include "spark_wiring_tcpserver.h"
#include "rgbled.h"
#include <stdint.h>

extern "C" {
#include "ota_flash_hal.h"
}

#define MAX_DATA_BYTES 4096


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
		// request the device list
		case 'd':
			deviceManager.printDeviceList(client);
			break;
		// receive new firmware
        case 'f':
            updateFirmware();
            break;
        // receive and set device mode
        case 'm':
            parseJson(&TcpListener::processSparkInfo, NULL);
            return true;
        // reset settings
        case 'r':
            resetSettings();
            return true;
		// receive and process spark info
		case 's':
			parseJson(&TcpListener::processSparkInfo, NULL);
			conf.storeSparkInfo();
			return true;
    }

    return false;
}

void TcpListener::processSparkInfo(const char * key, const char * val, void* pv) {
    if (strcmp(key, "name") == 0)
        memcpy(&sparkInfo.name, val, strlen(val) + 1);
    else if (strcmp(key, "mode") == 0)
        memcpy(&sparkInfo.mode, val, strlen(val) + 1);
    else if (strcmp(key, "config") == 0)
        memcpy(&sparkInfo.config, val, strlen(val) + 1);
    else if (strcmp(key, "tempType") == 0)
        memcpy(&sparkInfo.tempType, val, strlen(val) + 1);
    else if (strcmp(key, "oinkweb") == 0)
        memcpy(&sparkInfo.oinkWeb, val, strlen(val) + 1);
}

void TcpListener::setDeviceMode(const char * key, const char * val, void* pv) {
    if (strcmp(key, "mode") == 0 && (strcmp(val, "MANUAL") == 0 || strcmp(val, "LOGGING") == 0 || strcmp(val, "AUTOMATIC") == 0)) {
        memcpy(&sparkInfo.mode, val, strlen(val) + 1);
        conf.storeSparkInfo();
    }
}

void TcpListener::resetSettings() {
    memcpy(&sparkInfo.name, "", 1);
    memcpy(&sparkInfo.mode, "MANUAL", 7);
    memcpy(&sparkInfo.config, "", 1);
    memcpy(&sparkInfo.tempType, "C", 2);
    memcpy(&sparkInfo.oinkWeb, "", 1);
    conf.storeSparkInfo();
}

void TcpListener::updateFirmware() {


    begin_flash_file(1, HAL_OTA_FlashAddress(), 120000);

    byte buffer[MAX_DATA_BYTES + 1];
    int available = client.available();

    while (available > 0) {
        int bytesRead = 0;

        for (int i = 0; i < available && i < MAX_DATA_BYTES - bytesRead; i++) {
            buffer[bytesRead++] = client.read();
        }
        buffer[bytesRead + 1] = '\0';

        if (bytesRead >= 0) {
            save_flash_file_chunk(buffer, bytesRead);
            client.write("!");

            available = client.available();

            uint32_t startTime = millis();
            while (available == 0 && (millis() - startTime) < 5000);

            available = client.available();
        } else {
            available = 0;
        }

        if (available == 0) {
            client.write("-");
        }
    }

    finish_flash_file();
}

void TcpListener::begin_flash_file(int flashType, uint32_t sFlashAddress, uint32_t fileSize) {
    RGB.control(true);
    RGB.color(RGB_COLOR_MAGENTA);

    TimingFlashUpdateTimeout = 0;
    HAL_FLASH_Begin(sFlashAddress, fileSize);

    client.write("!");

    uint32_t startTime = millis();
    while ((millis() - startTime) < 100);
}

uint16_t TcpListener::save_flash_file_chunk(unsigned char *buf, uint32_t buflen) {
    uint16_t chunkUpdatedIndex;

    TimingFlashUpdateTimeout = 0;
    chunkUpdatedIndex = HAL_FLASH_Update(buf, buflen);

    return chunkUpdatedIndex;
}

void TcpListener::finish_flash_file() {
    RGB.color(RGB_COLOR_CYAN);

    HAL_FLASH_End();

    RGB.control(false);
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
        delay(50);
        retries++;
        if (retries >= 20) {
            return -1;
        }
    }
    return client.read();
}
