#ifndef VoltMeter_cpp
#define VoltMeter_cpp

#include <Arduino.h>
#include "..\Arduino\AnalogInput.cpp"

class VoltMeter
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

    VoltMeter(byte pin, float reference = 5) : input(pin)
    {
      _reference = reference;
    };

    void read()
    {
      input.read();
    };
};

#endif