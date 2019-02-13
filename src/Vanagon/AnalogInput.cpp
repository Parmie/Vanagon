#ifndef AnalogInput_cpp
#define AnalogInput_cpp

#include <Arduino.h>
#include "Input.cpp"

class AnalogInput : Input
{
  private:
    unsigned short _value = 0;
    
  public:
    float getValue()
    {
      return _value;
    };

    AnalogInput(int pin) : Input(pin)
    {
    };

    void read()
    {
      _value = analogRead(_pin);
    };
};

#endif