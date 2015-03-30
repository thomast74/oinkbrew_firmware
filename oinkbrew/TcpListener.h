/**
 ******************************************************************************
 * @file    TcpListener.h
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


#ifndef TCPLISTENER_H
#define	TCPLISTENER_H


class TcpListener {
public:
    void init();
    bool connected();
private:
    void resetSettings();
    bool processRequest(char action);

    
    typedef void (*ParseJsonCallback)(const char* key, const char* val, void* data);

    
    void parseJson(ParseJsonCallback fn, void* data);
    bool parseJsonToken(char* val);
    int readNext();

    
    static void processDeviceInfo(const char * key, const char * val, void* pv);
    static void setDeviceMode(const char * key, const char * val, void* pv);
    
};

extern TcpListener listener;

#endif	/* TCPLISTENER_H */

