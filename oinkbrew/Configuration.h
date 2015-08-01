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


#ifndef CONFIGURATION_H
#define	CONFIGURATION_H

#include "flashee-eeprom.h"
#include "devices/Device.h"
#include "controller/ControllerConfiguration.h"
#include <stddef.h>


class Configuration {
public:
    static void init();

    static bool loadDeviceInfo();
    static void storeSparkInfo();

    static short fetchNumberDevices();
    static void storeNumberDevices(short no_devices);

    static short fetchDevice(uint8_t& pin_nr, DeviceAddress& hw_address, Device& device);
    static void fetchDevices(Device devices[]);

    static void storeDevice(Device& device);
    static void storeDevices(Device devices[], short no_devices);

    static void removeDevice(uint8_t& pin_nr, DeviceAddress& hw_address);
    static void removeDevices();

    static short fetchNumberControllers();
    static void storeNumberControllers(short no_configs);

    static short fetchController(int id, ControllerConfiguration& config);
    static void fetchControllers(ControllerConfiguration configs[]);

    static void storeController(ControllerConfiguration& config);
    static void storeControllers(ControllerConfiguration configs[], short no_controllers);

    static void removeController(ControllerConfiguration& config);
    static void removeControllers();

    static bool loadEguiSettings();
    static void storeEguiSettings();

    static void clear(uint8_t* p, uint16_t size);
};

extern Configuration conf;

#endif	/* CONFIGURATION_H */

