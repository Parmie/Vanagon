#include <Arduino.h>
#include "FuelTank.h"

float FuelTank::getCapacity()
{
    return this->_capacity;
}

void FuelTank::setCapacity(float value)
{
    this->_capacity = value;
}

float FuelTank::getContent()
{
    return this->_content;
}

FuelTank::FuelTank(AnalogInput *senderInput)
{
    this->_senderInput = senderInput;
}

void FuelTank::update()
{
    this->_senderInput->read();
    float voltage = this->_senderInput->getVoltage();
    float resistance = (voltage*FuelTank::_senderDividerResistance)/(REF_VOLTAGE-voltage);
    float content = (4.794908061*pow(10,-4)*pow(resistance, 2))-(4.726976404*pow(10,-1)*resistance)+99.48112787;
}