#ifndef ResistanceMeter_cpp
#define ResistanceMeter_cpp

#include <Arduino.h>
#include "..\Arduino\AnalogInput.cpp"
#include "VoltageMeter.cpp"

class ResistanceMeter
{
  private:
    VoltageMeter _voltageMeter;
    float _dividerResistance;
    float _baseVoltage;

  public:
    float getVoltage()
    {
      return _voltageMeter.getVoltage();
    };

    float getResistance()
    {
      return (_voltageMeter.getVoltage() * _dividerResistance) / (_baseVoltage - _voltageMeter.getVoltage());
    };

    ResistanceMeter(AnalogInput *input, float dividerResistance) : _voltageMeter(input)
    {
      _dividerResistance = dividerResistance;
    };

    void update()
    {
      _voltageMeter.update();
    };

    void setBaseVoltage(float voltage)
    {
      _baseVoltage = voltage;
    };
};

#endif