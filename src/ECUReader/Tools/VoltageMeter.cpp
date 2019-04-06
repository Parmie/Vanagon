#ifndef VoltageMeter_cpp
#define VoltageMeter_cpp

#include <Arduino.h>
#include "..\Arduino\AnalogInput.cpp"

class VoltageMeter
{
  private:
    float _reference;

  public:
    AnalogInput input;

    float getReference()
    {
      return _reference;
    }

    void setReference(float value)
    {
      _reference = value;
    }

    float getVoltage()
    {
      return input.getValue() * (_reference / 1024.0);
    };

    VoltageMeter(byte pin, float reference = 5) : input(pin)
    {
      _reference = reference;
    };

    void read()
    {
      input.read();
    };
};

#endif