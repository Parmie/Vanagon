#include <Arduino.h>
#include "Battery.h"
#include "AnalogInput.h"

float Battery::getVoltage()
{
  return this->_voltage;
}

Battery::Battery(AnalogInput *input)// : _input(input)
{
  this->_input = input;
}

void Battery::update()
{
  this->_input->read();
  float inputVoltage = this->_input->getVoltage();
  this->_voltage = inputVoltage;
}