/*
 * ADCfilteredReader.cpp
 *
 *  Created on: Feb 2, 2023
 *      Author: antoine
 */

#include <scd41Reader.h>

#define I2C_ADDRESS_BMX 0x76



SCD41Reader::SCD41Reader(TwoWire *wire)
{
    _wire = wire;
}

SCD41Reader::~SCD41Reader() {
    // TODO Auto-generated destructor stub
}

void SCD41Reader::printUint16Hex(uint16_t value) {
    Serial.print(value < 4096 ? "0" : "");
    Serial.print(value < 256 ? "0" : "");
    Serial.print(value < 16 ? "0" : "");
    Serial.print(value, HEX);
}

void SCD41Reader::begin(){
    uint16_t error;
    char errorMessage[256];
    uint16_t serial0;
    uint16_t serial1;
    uint16_t serial2;
    scd4x.begin(*_wire);
    error = scd4x.getSerialNumber(serial0, serial1, serial2);
    if (error) {
        Serial.print("Error trying to execute getSerialNumber(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } else {
        Serial.print("Serial: 0x");
        printUint16Hex(serial0);
        printUint16Hex(serial1);
        printUint16Hex(serial2);
        Serial.println();
    }

    // Start Measurement
    error = scd4x.startPeriodicMeasurement();
    if (error) {
        Serial.print("Error trying to execute startPeriodicMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    }
}

void SCD41Reader::measure(){
    char errorMessage[256];
    uint16_t co2;
    float temperature;
    float humidity;
    uint16_t error = scd4x.readMeasurement(co2, temperature, humidity);
    if (error) {
        if (error!=526) { // wait until data comes
            registers[SCD41_TEMPERATURE]=0x7FFF;
            registers[SCD41_HUMIDITY]=0x7FFF;
            registers[SCD41_CO2]=0x7FFF;

            errorToString(error, errorMessage, 256);
            Serial.println(errorMessage);
        }
    }
    else{

        if (temperature==NAN){
            registers[SCD41_TEMPERATURE]=0x7FFF;
        }
        else{
            registers[SCD41_TEMPERATURE]=(uint16_t)(temperature*100);
        }
        if (humidity==NAN){
            registers[SCD41_HUMIDITY]=0x7FFF;
        }
        else{
            registers[SCD41_HUMIDITY]=(uint16_t)(humidity*100);
        }
        if (co2 == 0) {
            registers[SCD41_CO2]=0x7FFF;
        } else {
            registers[SCD41_CO2]=co2;
        }
        
    }
}

