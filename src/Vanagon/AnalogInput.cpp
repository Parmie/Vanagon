#include <Arduino.h>
#include "AnalogInput.h"

float AnalogInput::getVoltage()
{
    return this->_voltage;
}

AnalogInput::AnalogInput(int pin)
{
    this->_pin = pin;
}

void AnalogInput::read()
{
    int reading = analogRead(this->_pin);
    this->_voltage = reading * (REF_VOLTAGE / 1024.0) * this->_dividerRate;
}

void AnalogInput::setDivider(float resistance1, float resistance2)
{
    this->_dividerRate = (resistance1+resistance2)/resistance2;
}