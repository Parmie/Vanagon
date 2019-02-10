#include <Arduino.h>
#include "Exhaust.h"
#include "AnalogInput.h"

float Exhaust::getOxygenVoltage()
{
  return this->_oxygenVoltage;
}

int Exhaust::getMixtureStatus()
{
  if (this->_oxygenVoltage > 0.720)
  {
      return +1;
  }
  else if (this->_oxygenVoltage < 0.120)
  {
      return -1;
  }
  else
  {
      return 0;
  }
}

Exhaust::Exhaust(AnalogInput *oxygenInput)
{
  this->_oxygenInput = oxygenInput;
}

void Exhaust::update()
{
  this->_oxygenInput->read();
  float inputVoltage = this->_oxygenInput->getVoltage();
  this->_oxygenVoltage = inputVoltage;
}