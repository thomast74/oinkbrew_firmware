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
#include "Helper.h"
#include "SparkInfo.h"
#include "devices/DeviceManager.h"
#include "controller/ControllerManager.h"

extern "C" {
#include "d4d.h"
}

#define EEPROM_SPARK_INFO_START_BLOCK 0
#define EEPROM_SPARK_INFO_END_BLOCK 4

#define EEPROM_DEVICE_SETTINGS_START_BLOCK 4
#define EEPROM_DEVICE_SETTINGS_END_BLOCK 18

#define EEPROM_CTRL_SETTINGS_START_BLOCK 18
#define EEPROM_CTRL_SETTINGS_END_BLOCK 32

#define EEPROM_EGUI_SETTINGS_START_BLOCK 32
#define EEPROM_EGUI_SETTINGS_END_BLOCK 36


#define pointerOffset(x) offsetof(EepromFormat, x)


static Flashee::FlashDevice* sparkInfoFlash;
static Flashee::FlashDevice* deviceSettingsFlash;
static Flashee::FlashDevice* controllerSettingsFlash;
static Flashee::FlashDevice* eguiFlash;


/*******************************************************************************
 * Function Name  : init
 * Description    : Creates flash devices for different configuration regions
 * Input          : 
 * Output         : 
 * Return         : 
 ******************************************************************************/
void Configuration::init()
{
	sparkInfoFlash = Flashee::Devices::createAddressErase(4096 * EEPROM_SPARK_INFO_START_BLOCK, 4096 * EEPROM_SPARK_INFO_END_BLOCK);
	deviceSettingsFlash = Flashee::Devices::createAddressErase(4096 * EEPROM_DEVICE_SETTINGS_START_BLOCK, 4096 * EEPROM_DEVICE_SETTINGS_END_BLOCK);
	controllerSettingsFlash = Flashee::Devices::createAddressErase(4096 * EEPROM_CTRL_SETTINGS_START_BLOCK, 4096 * EEPROM_CTRL_SETTINGS_END_BLOCK);
	eguiFlash = Flashee::Devices::createAddressErase(4096 * EEPROM_EGUI_SETTINGS_START_BLOCK, 4096 * EEPROM_EGUI_SETTINGS_END_BLOCK);
}

/*******************************************************************************
 * Function Name  : loadDeviceInfo
 * Description    : loads device information from flash memory
 * Input          : 
 * Output         : returns true if successfully able to ready data otherwise false
 * Return         : 
 ******************************************************************************/
bool Configuration::loadDeviceInfo()
{
	SparkInfo si;

	if (sparkInfoFlash->read(&si, 0, sizeof(SparkInfo))) {
		if (si.check != 'C') {
			storeSparkInfo();
		} else {
			memcpy(&sparkInfo, &si, sizeof(SparkInfo));
		}
		return true;
	}
	else {
		return false;
	}
}

/*******************************************************************************
 * Function Name  : storeSparkInfo
 * Description    : stores spark information in flash memory
 * Input          : 
 * Output         : 
 * Return         : 
 ******************************************************************************/
void Configuration::storeSparkInfo()
{
    sparkInfoFlash->write(&sparkInfo, 0, sizeof (SparkInfo));
}

/*******************************************************************************
 * Function Name  : fetchNumberDevices
 * Description    : get the number of devices stored in EEPROM
 * Input          :
 * Output         :
 * Return         : number of devices stored in EEPROM
 ******************************************************************************/
short Configuration::fetchNumberDevices()
{
	char no_devices_char;
	int no_devices;

	deviceSettingsFlash->read(&no_devices_char, 0, sizeof(char));

	no_devices = atoi(&no_devices_char);

	if (no_devices < 0 || no_devices > MAX_DEVICES)
		no_devices = 0;

	return no_devices;
}

/*******************************************************************************
 * Function Name  : storeNumberDevices
 * Description    : saves number of devices in EEPROM
 * Input          :
 * Output         : no of devices
 * Return         :
 ******************************************************************************/
void Configuration::storeNumberDevices(short no_devices) {

	char no_devices_char;
	itoa(no_devices, &no_devices_char, 10);

	String msg = "New no devices: ";
	msg.concat(no_devices_char);
	Helper::serialDebug(msg.c_str());

	deviceSettingsFlash->write(&no_devices_char, 0, sizeof(char));
}

/*******************************************************************************
 * Function Name  : fetchDevice
 * Description    : search if there is an existing device in EEPROM
 * Input          : pin_nr and hw_adress to look for
 * Output         : device if found
 * Return         : slot in EEPROM or -1 if not found
 ******************************************************************************/
short Configuration::fetchDevice(uint8_t& pin_nr, DeviceAddress& hw_address, Device& device)
{
	uint32_t offset = sizeof(char);
	uint32_t size_device = sizeof(Device);
	short no_devices = fetchNumberDevices();

	Device device_search;
	conf.clear((uint8_t*) &device_search, sizeof(device_search));

	for(short slot = 0; slot < no_devices; slot++) {
		deviceSettingsFlash->read(&device_search, (size_device*slot) + offset, size_device);
		if (device_search.hardware.pin_nr == pin_nr && Helper::matchAddress(hw_address, device_search.hardware.hw_address, 8)) {
			memcpy(&device, &device_search, size_device);
			return slot;
		}
	}

	return -1;
}

/*******************************************************************************
 * Function Name  : fetchDevices
 * Description    : load all devices from EEPROM
 * Input          :
 * Output         : Devices array with all stored devices
 * Return         :
 ******************************************************************************/
void Configuration::fetchDevices(Device devices[])
{
	uint32_t offset = sizeof(char);
	uint32_t size_device = sizeof(Device);
	short no_devices = fetchNumberDevices();

	for(short slot = 0; slot < no_devices; slot++) {
		deviceSettingsFlash->read(&devices[slot], (size_device*slot) + offset, size_device);
	}
}

/*******************************************************************************
 * Function Name  : storeDevice
 * Description    : save device to EEPROM, if exists overwrite, if new add to the end
 * Input          : Device to store in EEPROM
 * Output         :
 * Return         :
 ******************************************************************************/
void Configuration::storeDevice(Device& device)
{
	uint32_t offset = sizeof(char);
	uint32_t size_device = sizeof(Device);

	Device device_search;
	conf.clear((uint8_t*) &device_search, sizeof(device_search));

	short slot = fetchDevice(device.hardware.pin_nr, device.hardware.hw_address, device_search);

	if (slot != -1) {
		deviceSettingsFlash->write(&device, (size_device*slot) + offset, size_device);
	}
	else {
		short current_no_devices = fetchNumberDevices();

		deviceSettingsFlash->write(&device, (size_device*current_no_devices) + offset, size_device);

		current_no_devices++;
		storeNumberDevices(current_no_devices);
	}
}

/*******************************************************************************
 * Function Name  : storeDevices
 * Description    : save devices in array to EEPROM for restart
 * Input          : devices in array and no of devices
 * Output         :
 * Return         :
 ******************************************************************************/
void Configuration::storeDevices(Device devices[], short no_devices)
{
	uint32_t offset = sizeof(char);
	uint32_t size_device = sizeof(Device);

	storeNumberDevices(no_devices);

	for(short slot = 0; slot < no_devices; slot++) {
		deviceSettingsFlash->write(&devices[slot], (size_device*slot) + offset, size_device);
	}
}

/*******************************************************************************
 * Function Name  : removeDevice
 * Description    : remove a specific device from EEPROM
 * Input          : pin nr and hardware address of the device to delete
 * Output         :
 * Return         :
 ******************************************************************************/
void Configuration::removeDevice(uint8_t& pin_nr, DeviceAddress& hw_address)
{
	short no_devices = fetchNumberDevices();
	short new_no_devices = 0;

	Device devices[MAX_DEVICES];
	Device new_devices[MAX_DEVICES];
	fetchDevices(devices);

	for(short slot = 0; slot < no_devices; slot++) {

		if (!(devices[slot].hardware.pin_nr == pin_nr && Helper::matchAddress(hw_address, devices[slot].hardware.hw_address, 8))) {
			new_devices[new_no_devices] =  devices[slot];
			new_no_devices++;
		}
	}

	storeDevices(new_devices, new_no_devices);
}

/*******************************************************************************
 * Function Name  : removeDevices
 * Description    : remove all devices from EEPROM
 * Input          :
 * Output         :
 * Return         :
 ******************************************************************************/
void Configuration::removeDevices()
{
	uint32_t offset = sizeof(char);
	uint32_t size_device = sizeof(Device);

	Device device;
	conf.clear((uint8_t*) &device, sizeof(device));

	storeNumberDevices(0);

	for(short slot = 0; slot < MAX_DEVICES; slot++) {
		deviceSettingsFlash->write(&device, (size_device*slot) + offset, size_device);
	}
}



/*******************************************************************************
 * Function Name  : fetchNumberControllers
 * Description    : get the number of controllers stored in EEPROM
 * Input          :
 * Output         :
 * Return         : number of controllers stored in EEPROM
 ******************************************************************************/
short Configuration::fetchNumberControllers()
{
	char no_controllers_char;
	int no_controllers;

	controllerSettingsFlash->read(&no_controllers_char, 0, sizeof(char));

	no_controllers = atoi(&no_controllers_char);

	if (no_controllers < 0 || no_controllers > MAX_CONTROLLERS)
		no_controllers = 0;

	return no_controllers;
}

/*******************************************************************************
 * Function Name  : storeNumberControllers
 * Description    : saves number of controllers in EEPROM
 * Input          : no of device in EEPROM
 * Output         :
 * Return         :
 ******************************************************************************/
void Configuration::storeNumberControllers(short no_controllers)
{
	char no_controllers_char;
	itoa(no_controllers, &no_controllers_char, 10);

	String msg = "New no controllers: ";
	msg.concat(no_controllers_char);
	Helper::serialDebug(msg.c_str());

	controllerSettingsFlash->write(&no_controllers_char, 0, sizeof(char));
}


/*******************************************************************************
 * Function Name  : fetchController
 * Description    : search if there is an existing controller in device
 * Input          : id of controller to get
 * Output         : controller from EEPROM
 * Return         : slot number in EEPROM or -1 if not found
 ******************************************************************************/
short Configuration::fetchController(int id, ControllerConfiguration& config)
{
	uint32_t offset = sizeof(char);
	uint32_t size_controller = sizeof(ControllerConfiguration);
	short no_controllers = fetchNumberControllers();

	ControllerConfiguration controller_search;
	conf.clear((uint8_t*) &controller_search, sizeof(controller_search));

	for(short slot = 0; slot < no_controllers; slot++) {
		controllerSettingsFlash->read(&controller_search, (size_controller*slot) + offset, size_controller);
		if (controller_search.id == id) {
			memcpy(&config, &controller_search, sizeof(controller_search));

			return slot;
		}
	}

	return -1;
}

/*******************************************************************************
 * Function Name  : fetchControllers
 * Description    : load all controllers from EEPROM
 * Input          :
 * Output         : Controllers array with all stored devices
 * Return         :
 ******************************************************************************/
void Configuration::fetchControllers(ControllerConfiguration configs[])
{
	uint32_t offset = sizeof(char);
	uint32_t size_controller = sizeof(ControllerConfiguration);
	short no_controllers = fetchNumberControllers();


	for(short slot = 0; slot < no_controllers; slot++) {
		controllerSettingsFlash->read(&configs[slot], (size_controller*slot) + offset, size_controller);
	}
}

/*******************************************************************************
 * Function Name  : storeController
 * Description    : save controller in array to EEPROM for restart
 * Input          : controller to store in EEPROM, if exists overwrite, if new add to the end
 * Output         :
 * Return         :
 ******************************************************************************/
void Configuration::storeController(ControllerConfiguration& config)
{
	uint32_t offset = sizeof(char);
	uint32_t size_controller = sizeof(ControllerConfiguration);

	ControllerConfiguration controller_search;
	conf.clear((uint8_t*) &controller_search, sizeof(controller_search));

	short slot = fetchController(config.id, controller_search);

	if (slot != -1) {
		controllerSettingsFlash->write(&config, (size_controller*slot) + offset, size_controller);
	}
	else {
		short current_no_controllers = fetchNumberControllers();

		controllerSettingsFlash->write(&config, (size_controller*current_no_controllers) + offset, size_controller);

		current_no_controllers++;
		storeNumberControllers(current_no_controllers);
	}
}

/*******************************************************************************
 * Function Name  : storeControllers
 * Description    : save controllers in array to EEPROM for restart
 * Input          : controllers in an array and no of controllers
 * Output         :
 * Return         :
 ******************************************************************************/
void Configuration::storeControllers(ControllerConfiguration controllers[], short no_controllers)
{
	uint32_t offset = sizeof(char);
	uint32_t size_controllers = sizeof(ControllerConfiguration);

	storeNumberControllers(no_controllers);

	for(short slot = 0; slot < no_controllers; slot++) {
		controllerSettingsFlash->write(&controllers[slot], (size_controllers*slot) + offset, size_controllers);
	}
}

/*******************************************************************************
 * Function Name  : removeController
 * Description    : remove a specific controller from EEPROM
 * Input          : controller to remove
 * Output         :
 * Return         :
 ******************************************************************************/
void Configuration::removeController(ControllerConfiguration& config)
{
	Helper::serialDebug("conf.removeController");
	short no_controllers = fetchNumberControllers();
	short new_no_controllers = 0;

	ControllerConfiguration controllers[MAX_DEVICES];
	ControllerConfiguration new_controllers[MAX_DEVICES];
	fetchControllers(controllers);

	for(short slot = 0; slot < no_controllers; slot++) {

		if (controllers[slot].id != config.id) {
			new_controllers[new_no_controllers] =  controllers[slot];
			new_no_controllers++;
		}
	}

	storeControllers(new_controllers, new_no_controllers);
}

/*******************************************************************************
 * Function Name  : removeControllers
 * Description    : remove all controllers from EEPROM
 * Input          :
 * Output         :
 * Return         :
 ******************************************************************************/
void Configuration::removeControllers()
{
	uint32_t offset = sizeof(char);
	uint32_t size_controller = sizeof(ControllerConfiguration);

	ControllerConfiguration controller;
	conf.clear((uint8_t*) &controller, sizeof(controller));

	storeNumberControllers(0);

	for(short slot = 0; slot < MAX_CONTROLLERS; slot++) {
		controllerSettingsFlash->write(&controller, (size_controller*slot) + offset, size_controller);
	}
}

/*******************************************************************************
 * Function Name  : loadEguiSettings
 * Description    : Checks whether valid touch screen calibration data is stored in flash memory
 *                  and loads it in eGUI
 * Input          : 
 * Output         : 
 * Return         : true if valid data was found, false if not and calibration is needed
 ******************************************************************************/
bool Configuration::loadEguiSettings()
{
    D4D_TOUCHSCREEN_CALIB calib;
    eguiFlash->read(&calib, 0, sizeof (D4D_TOUCHSCREEN_CALIB));
    if (calib.ScreenCalibrated != 1) {
        return false;
    }
    D4D_TCH_SetCalibration(calib);
    return true;
}

/*******************************************************************************
 * Function Name  : storeEguiSettings
 * Description    : Stores current touch screen calibration data from eGUI to flash memory
 * Input          : 
 * Output         : 
 * Return         : 
 ******************************************************************************/
void Configuration::storeEguiSettings()
{
    D4D_TOUCHSCREEN_CALIB calib = D4D_TCH_GetCalibration();
    eguiFlash->write(&calib, 0, sizeof (D4D_TOUCHSCREEN_CALIB));
}

/*******************************************************************************
 * Function Name  : clear
 * Description    : clear variable of values
 * Input          :
 * Output         :
 * Return         :
 ******************************************************************************/
void Configuration::clear(uint8_t* p, uint8_t size)
{
	memset(p, 0, size);
}
