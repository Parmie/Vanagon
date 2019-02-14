#ifndef VoltageMeter_cpp
#define VoltageMeter_cpp

#include <Arduino.h>
#include "AnalogInput.cpp"

struct VoltageDivider
{
  float resistor1;
  float resistor2;
};

class VoltageMeter
{
  private:
    AnalogInput *_input;
    float _reference = 4.096;
    float _scale = 1.0;

  public:
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
      return _input->getValue() * (_reference / 1024.0) * _scale;
    };

    VoltageMeter(AnalogInput *input, VoltageDivider divider = { 0, 0 })
    {
      _input = input;
      if (divider.resistor2 > 0)
      {
        _scale = (divider.resistor1 + divider.resistor2) / divider.resistor2;
      }
    };

    void update()
    {
      _input->read();
    };
};

#endif