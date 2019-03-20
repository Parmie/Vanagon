#ifndef Induction_cpp
#define Induction_cpp

#include <Arduino.h>
#include "Tools\ResistanceMeter.cpp"

class Induction
{
  private:

  public:
    ResistanceMeter temperatureOhmMeter;
    ResistanceMeter flowOhmMeter;

    float getFlowResistance()
    {
      return flowOhmMeter.getResistance();
    };
/*
    float getTemperature()
    {
        
    };
*/
    Induction(byte temperaturePin, byte airFlowPin) : temperatureOhmMeter(temperaturePin, 326), flowOhmMeter(airFlowPin, 330)
    {
    };

    void read()
    {
      temperatureOhmMeter.read();
      flowOhmMeter.read();
    };
};

#endif