/**
 ******************************************************************************
 * @file    DeviceInfo.h
 * @authors Thomas Trageser
 * @version V0.1
 * @date    2015-03-27
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


#ifndef SPARKINFO_H
#define	SPARKINFO_H

struct SparkInfo {
    char name[31] = "";
    uint8_t oinkWeb[4] = { 0, 0, 0, 0 };
    int oinkWebPort = 80;
    bool requested = false;
    bool received = false;
};

extern SparkInfo sparkInfo;

#endif	/* SPARKINFO_H */

