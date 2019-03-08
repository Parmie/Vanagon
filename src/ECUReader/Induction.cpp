#ifndef Induction_cpp
#define Induction_cpp

#include <Arduino.h>
#include "Arduino\AnalogInput.cpp"
#include "Tools\ResistanceMeter.cpp"

class Induction
{
  private:
    ResistanceMeter _temperatureResistanceMeter;
    ResistanceMeter _flowResistanceMeter;

  public:
    float getTemperatureResistance()
    {
      return _temperatureResistanceMeter.getResistance();
    };

    float getFlowResistance()
    {
      return _flowResistanceMeter.getResistance();
    };
/*
    float getTemperature()
    {
        
    };
*/
    Induction(AnalogInput *temperatureInput, AnalogInput *airFlowInput) : _temperatureResistanceMeter(temperatureInput, 326), _flowResistanceMeter(airFlowInput, 330)
    {
    };

    void update()
    {
      _temperatureResistanceMeter.update();
      _flowResistanceMeter.update();
    };

    void setBaseVoltage(float voltage)
    {
      _temperatureResistanceMeter.setBaseVoltage(voltage);
      _flowResistanceMeter.setBaseVoltage(voltage);
    };
};

#endif