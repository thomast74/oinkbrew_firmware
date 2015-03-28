/**
 ******************************************************************************
 * @file    Configuration.cpp
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


#include "Configuration.h"
#include "DeviceInfo.h"

extern "C" {
#include "d4d.h"
}

#define EEPROM_DEVICE_INFO_START_BLOCK 0
#define EEPROM_DEVICE_INFO_END_BLOCK 4
#define EEPROM_EGUI_SETTINGS_START_BLOCK 32
#define EEPROM_EGUI_SETTINGS_END_BLOCK 36



/*******************************************************************************
 * Function Name  : Constructor
 * Description    : Creates flash devices for different configuration regions
 * Input          : 
 * Output         : 
 * Return         : 
 ******************************************************************************/
Configuration::Configuration() {
    deviceInfoFlash = Flashee::Devices::createAddressErase(4096 * EEPROM_DEVICE_INFO_START_BLOCK, 4096 * EEPROM_DEVICE_INFO_END_BLOCK);
    eguiFlash = Flashee::Devices::createAddressErase(4096 * EEPROM_EGUI_SETTINGS_START_BLOCK, 4096 * EEPROM_EGUI_SETTINGS_END_BLOCK);
};

/*******************************************************************************
 * Function Name  : loadDeviceInfo
 * Description    : loads device information from flash memory
 * Input          : 
 * Output         : returns true if successfully able to ready data otherwise false
 * Return         : 
 ******************************************************************************/
bool Configuration::loadDeviceInfo() {
   if (deviceInfoFlash->read(&deviceInfo, 0, sizeof(DeviceInfo)))
        return true;
   else
        return false;
};

/*******************************************************************************
 * Function Name  : storeDeviceInfo
 * Description    : stores device information in flash memory
 * Input          : 
 * Output         : 
 * Return         : 
 ******************************************************************************/
void Configuration::storeDeviceInfo() {
    deviceInfoFlash->write(&deviceInfo, 0, sizeof (DeviceInfo));
}

/*******************************************************************************
 * Function Name  : loadEguiSettings
 * Description    : Checks whether valid touch screen calibration data is stored in flash memory
 *                  and loads it in eGUI
 * Input          : 
 * Output         : 
 * Return         : true if valid data was found, false if not and calibration is needed
 ******************************************************************************/
bool Configuration::loadEguiSettings() {
    D4D_TOUCHSCREEN_CALIB calib;
    eguiFlash->read(&calib, 0, sizeof (D4D_TOUCHSCREEN_CALIB));
    if (calib.ScreenCalibrated != 1) {
        return false;
    }
    D4D_TCH_SetCalibration(calib);
    return true;
};

/*******************************************************************************
 * Function Name  : storeEguiSettings
 * Description    : Stores current touch screen calibration data from eGUI to flash memory
 * Input          : 
 * Output         : 
 * Return         : 
 ******************************************************************************/
void Configuration::storeEguiSettings() {
    D4D_TOUCHSCREEN_CALIB calib = D4D_TCH_GetCalibration();
    eguiFlash->write(&calib, 0, sizeof (D4D_TOUCHSCREEN_CALIB));
};
