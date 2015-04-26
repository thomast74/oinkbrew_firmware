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


#define	SPARK_MODE_MANUAL 		0
#define	SPARK_MODE_CALIBRATION 	1
#define	SPARK_MODE_LOGGING 		2
#define	SPARK_MODE_AUTOMATIC 	3


struct SparkInfo {
    unsigned char name[31] = "";
    int mode = SPARK_MODE_MANUAL;
    unsigned char tempType[2] = "C";
    uint8_t oinkWeb[4] = { 0, 0, 0, 0 };
    int oinkWebPort = 80;
	unsigned char check[2] = "C";
};

extern SparkInfo sparkInfo;

#endif	/* SPARKINFO_H */

