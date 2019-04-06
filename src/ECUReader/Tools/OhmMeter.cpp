#ifndef OhmMeter_cpp
#define OhmMeter_cpp

#include <Arduino.h>
#include "..\Arduino\AnalogInput.cpp"
#include "VoltageMeter.cpp"

class OhmMeter
{
  private:
    float _dividerResistance;
    float _baseVoltage;

  public:
    VoltageMeter voltMeter;

    float getResistance()
    {
      return (voltMeter.getVoltage() * _dividerResistance) / (_baseVoltage - voltMeter.getVoltage());
    };

    OhmMeter(byte pin, float dividerResistance) : voltMeter(pin)
    {
      _dividerResistance = dividerResistance;
      _baseVoltage = 5;
    };

    void read()
    {
      voltMeter.read();
    };

    void setBaseVoltage(float voltage)
    {
      _baseVoltage = voltage;
    };
};

#endif