/*
 * Copyright 2012-2013 BrewPi/Elco Jacobs.
 * Copyright 2013 Matthew McGowan.
 *
 * This file is part of BrewPi.
 * 
 * BrewPi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * BrewPi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with BrewPi.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "OneWireTempSensor.h"
#include "DallasTemperature.h"
#include "OneWire.h"

OneWireTempSensor::~OneWireTempSensor() {
	delete sensor;
};

/**
 * Initializes the temperature sensor.
 * This method is called when the sensor is first created and also any time the sensor reports it's disconnected.
 * If the result is TEMP_SENSOR_DISCONNECTED then subsequent calls to read() will also return TEMP_SENSOR_DISCONNECTED.
 * Clients should attempt to re-initialize the sensor by calling init() again. 
 */
bool OneWireTempSensor::init() {

	// save address and pinNr for log messages
	char addressString[17];
	printBytes(sensorAddress, 8, addressString);

	bool success = false;

	if (sensor == NULL) {
		sensor = new DallasTemperature(oneWire);
	}

	// This quickly tests if the sensor is connected and initializes the reset detection.
	// During the main TempControl loop, we don't want to spend many seconds
	// scanning each sensor since this brings things to a halt.
	if (sensor && sensor->initConnection(sensorAddress)) {
		requestConversion();
		temperature temp = readAndConstrainTemp();
		success = temp != DEVICE_DISCONNECTED;
		requestConversion(); // piggyback request for a new conversion
	}
	setConnected(success);
	return success;
}

void OneWireTempSensor::requestConversion() {
	sensor->requestTemperaturesByAddress(sensorAddress);
}

void OneWireTempSensor::setConnected(bool connected) {
	if (this->connected == connected)
		return; // state is stays the same

	char addressString[17];
	printBytes(sensorAddress, 8, addressString);
	this->connected = connected;
}

temperature OneWireTempSensor::read() {

	if (!connected)
		return TEMP_SENSOR_DISCONNECTED;

	temperature temp = readAndConstrainTemp();
	requestConversion();
	return temp;
}

temperature OneWireTempSensor::readAndConstrainTemp() {
	temperature temp = sensor->getTempRaw(sensorAddress);
	if (temp == DEVICE_DISCONNECTED) {
		setConnected(false);
		return TEMP_SENSOR_DISCONNECTED;
	}

	const uint8_t shift = TEMP_FIXED_POINT_BITS - ONEWIRE_TEMP_SENSOR_PRECISION;
	temp = constrainTemp(temp + calibrationOffset + (C_OFFSET >> shift), ((int) MIN_TEMP) >> shift, ((int) MAX_TEMP) >> shift) << shift;
	return temp;
}

bool OneWireTempSensor::isParasitePowerMode() {
	return sensor->isParasitePowered(sensorAddress);
}
