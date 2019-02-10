#ifndef Battery_cpp
#define Battery_cpp

#include <Arduino.h>
#include "AnalogInput.cpp"

class Battery {
  private:
    AnalogInput *_input;
    float _voltage;

  public:
    float getVoltage()
    {
      return this->_voltage;
    };

    Battery(AnalogInput *input)
    {
      this->_input = input;
    };

    void update()
    {
      this->_input->read();
      float inputVoltage = this->_input->getVoltage();
      this->_voltage = inputVoltage;
    };
};

#endif