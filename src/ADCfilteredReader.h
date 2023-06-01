/*
 * ADCfilteredReader.h
 *
 *  Created on: Feb 2, 2023
 *      Author: antoine
 */

#ifndef ADCFILTEREDREADER_H_
#define ADCFILTEREDREADER_H_

#include "Arduino.h"

class ADCfilteredReader {
public:
    ADCfilteredReader(uint32_t pin,float factor=1,int32_t filterFactor=16);
    virtual ~ADCfilteredReader();
    void begin();
    uint16_t measure();
    uint16_t getLastRawValue();
protected:
    uint32_t pin_;
    uint16_t newVal;
    float factor_;
    uint32_t valueFilter=0xFFFFFFFF;
    int32_t filterFactor_;
};

#endif /* ADCFILTEREDREADER_H_ */
