/*
 * ValueFilter.cpp
 *
 *  Created on: Feb 2, 2023
 *      Author: antoine
 */

#include <ValueFilter.h>

ValueFilter::ValueFilter(float factor,int32_t filterFactor) :
    factor_(factor),filterFactor_(filterFactor)
{

}

ValueFilter::~ValueFilter() {
    // TODO Auto-generated destructor stub
}

void ValueFilter::begin(){
}

int16_t ValueFilter::filter(int16_t newVal){
    rawValue=newVal;
    if(newVal==0x7FFF){
        prevValue=false;
        return 0x7FFF;
    }
    if(prevValue==false){
        prevValue=true;
        valueFilter=newVal*filterFactor_;
    }
    else{
        valueFilter=((valueFilter*(filterFactor_-1))/filterFactor_)+newVal;
    }
    value=(int16_t)((valueFilter*factor_)/filterFactor_);
    return value;
}

ValueFilter32::ValueFilter32(float factor,int32_t filterFactor) :
    factor_(factor),filterFactor_(filterFactor)
{

}

ValueFilter32::~ValueFilter32() {
    // TODO Auto-generated destructor stub
}

void ValueFilter32::begin(){
}

uint16_t ValueFilter32::highReg(){
    return value >> 16;
}
uint16_t ValueFilter32::lowReg(){
    return value &0xFFFF;
}

int32_t ValueFilter32::filter(int32_t newVal){

    if(newVal>25000){
        volatile int k=0;
    }

    if(newVal==0x7FFFFFFF){
        prevValue=false;
        return 0x7FFFFFFF;
    }
    if(prevValue==false){
        prevValue=true;
        valueFilter=newVal*filterFactor_;
    }
    else{
        valueFilter=((valueFilter*(filterFactor_-1))/filterFactor_)+newVal;
    }
    value=(int32_t)((valueFilter*factor_)/filterFactor_);
    return value;
}

