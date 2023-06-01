/*
 * ADCfilteredReader.cpp
 *
 *  Created on: Feb 2, 2023
 *      Author: antoine
 */

#include <ADCfilteredReader.h>

ADCfilteredReader::ADCfilteredReader(uint32_t pin,float factor,int32_t filterFactor) :
    pin_(pin),factor_(factor),filterFactor_(filterFactor)
{

}

ADCfilteredReader::~ADCfilteredReader() {
    // TODO Auto-generated destructor stub
}

void ADCfilteredReader::begin(){
    analogReadResolution(12);
}
uint16_t ADCfilteredReader::getLastRawValue(){
    return newVal;
}


uint16_t ADCfilteredReader::measure(){
    newVal=analogRead(pin_);
    if(valueFilter==0xFFFFFFFF){
        valueFilter=newVal*filterFactor_;
    }
    else{
        valueFilter=((valueFilter*(filterFactor_-1))/filterFactor_)+newVal;
    }
    return (uint16_t)((valueFilter*factor_)/filterFactor_);
}

