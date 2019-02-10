#ifndef Exhaust_cpp
#define Exhaust_cpp

#include <Arduino.h>
#include "AnalogInput.cpp"

class Exhaust {
  private:
    AnalogInput *_oxygenInput;
    float _oxygenVoltage;

  public:
    float getOxygenVoltage()
    {
      return this->_oxygenVoltage;
    };

    int getMixtureStatus()
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
    };

    Exhaust(AnalogInput *oxygenInput)
    {
      this->_oxygenInput = oxygenInput;
    };

    void update()
    {
      this->_oxygenInput->read();
      float inputVoltage = this->_oxygenInput->getVoltage();
      this->_oxygenVoltage = inputVoltage;
    };
};

#endif