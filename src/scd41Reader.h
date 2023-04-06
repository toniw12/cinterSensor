/*
 * ADCfilteredReader.h
 *
 *  Created on: Feb 2, 2023
 *      Author: antoine
 */

#ifndef SCD41READER_H_
#define SCD41READER_H_

#include "Arduino.h"
#include <SensirionI2CScd4x.h>
#include <Wire.h>

enum {
    SCD41_TEMPERATURE,
    SCD41_HUMIDITY,
    SCD41_CO2,
};

class SCD41Reader {
public:
    SCD41Reader(TwoWire *wire);
    virtual ~SCD41Reader();
    void begin();
    void measure();

    uint16_t registers[3];
    float pressure,temperature,humidity;
private:
    void printUint16Hex(uint16_t value);
    TwoWire *_wire;
    SensirionI2CScd4x scd4x;
};

#endif /* SCD41READER_H_ */
