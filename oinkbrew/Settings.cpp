/**
 ******************************************************************************
 * @file    Settings.cpp
 * @authors Thomas Trageser
 * @version V0.1
 * @date    2015-03-25
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

#include "Settings.h"
#include "Platform.h"
#include "spark_wiring_ipaddress.h"

const char OINK_BREW_VERSION[] = "0.3";
const char OINK_BREW_VERSION_STRING[] = "Version: 0.3";

#if SPARK_V1
const char BREWPI_SPARK_REVISION[] = "V1";
#else
const char BREWPI_SPARK_REVISION[] = "V2";
#endif

const short REMOTE_LISTENER_PORT = 7872;
const short LOCAL_LISTENER_PORT = 7873;


const unsigned long DURATION_RUN = 1000;
const unsigned long DURATION_LOG = 5000;
const unsigned long DURATION_DETECT = 60000;
