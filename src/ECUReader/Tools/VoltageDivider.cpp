#ifndef VoltageDivider_cpp
#define VoltageDivider_cpp

#include <Arduino.h>
#include "VoltageMeter.cpp"

class VoltageDivider
{
  private:
    float _scale = 1.0;

  public:
    VoltageMeter voltMeter;

    float getScale()
    {
      return _scale;
    };

    float getVoltage()
    {
      return voltMeter.getVoltage() * _scale;
    };

    VoltageDivider(byte pin, float resistor1, float resistor2) : voltMeter(pin)
    {
      if (resistor2 > 0)
      {
        _scale = (resistor1 + resistor2) / resistor2;
      }
    };

    void read()
    {
      voltMeter.read();
    };
};

#endif