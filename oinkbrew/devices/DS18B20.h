/*
 * DS18B20.h
 *
 *  Created on: 8 Apr 2015
 *      Author: thomast74
 */

#ifndef OINKBREW_DEVICES_DS18B20_H_
#define OINKBREW_DEVICES_DS18B20_H_


#include "OneWire.h"


#define DS18B20MODEL 0x28


class DS18B20{
private:
    OneWire* ds;
    uint8_t data[12];
    uint8_t addr[8];
    uint8_t type_s;

public:
    DS18B20(uint16_t pin, uint8_t hw_address[]);

    float getTemperature();
    float convertToFahrenheit(float celsius);
};


#endif /* OINKBREW_DEVICES_DS18B20_H_ */
