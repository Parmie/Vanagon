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
    Induction(byte temperaturePin, byte airFlowPin) : _temperatureResistanceMeter(temperaturePin, 326), _flowResistanceMeter(airFlowPin, 330)
    {
    };

    void read()
    {
      _temperatureResistanceMeter.read();
      _flowResistanceMeter.read();
    };

    void setBaseVoltage(float voltage)
    {
      _temperatureResistanceMeter.setBaseVoltage(voltage);
      _flowResistanceMeter.setBaseVoltage(voltage);
    };
};

#endif