/*
 * ValueFilter.h
 *
 *  Created on: Feb 2, 2023
 *      Author: antoine
 */

#ifndef ValueFilter_H_
#define ValueFilter_H_

#include "Arduino.h"

class ValueFilter {
public:
    ValueFilter(float factor=1,int32_t filterFactor=16);
    virtual ~ValueFilter();
    void begin();
    int16_t filter(int16_t newVal);
    uint16_t value;
    uint16_t rawValue;
protected:
    float factor_;
    bool prevValue=false;
    int32_t valueFilter=0;
    int32_t filterFactor_;
};

class ValueFilter32 {
public:
    ValueFilter32(float factor=1,int32_t filterFactor=16);
    virtual ~ValueFilter32();
    void begin();
    int32_t filter(int32_t newVal);
    uint16_t highReg();
    uint16_t lowReg();

protected:
    float factor_;
    bool prevValue=false;
    int64_t valueFilter=0;
    int32_t value=0x7FFFFFFF;
    int32_t filterFactor_;
};

#endif /* ValueFilter_H_ */
