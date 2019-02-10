#ifndef AnalogInput_cpp
#define AnalogInput_cpp

#include <Arduino.h>
#include "Input.cpp"

const float REF_VOLTAGE = 4.096;

class AnalogInput : Input
{
  private:
    float _voltage;
    float _dividerRate = 1.0;
    
  public:
    float getVoltage()
    {
      return _voltage;
    };

    AnalogInput(int pin) : Input(pin)
    {
    };

    void read()
    {
      int reading = analogRead(_pin);
      _voltage = reading * (REF_VOLTAGE / 1024.0) * _dividerRate;
    };

    void setDivider(float resistance1, float resistance2)
    {
      _dividerRate = (resistance1+resistance2)/resistance2;
    };
};

#endif