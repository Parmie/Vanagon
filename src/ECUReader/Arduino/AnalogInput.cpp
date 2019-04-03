#ifndef AnalogInput_cpp
#define AnalogInput_cpp

#include <Arduino.h>
#include "Input.cpp"

class AnalogInput : Input
{
  private:
    unsigned short _value = 0;
    
  public:
    unsigned short getValue()
    {
      return _value;
    };

    AnalogInput(byte pin) : Input(pin)
    {
    };

    void read()
    {
      _value = analogRead(_pin);
    };
};

#endif