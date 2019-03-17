#ifndef ResistanceMeter_cpp
#define ResistanceMeter_cpp

#include <Arduino.h>
#include "..\Arduino\AnalogInput.cpp"
#include "VoltageMeter.cpp"

class ResistanceMeter
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

    ResistanceMeter(byte pin, float dividerResistance) : voltMeter(pin)
    {
      _dividerResistance = dividerResistance;
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