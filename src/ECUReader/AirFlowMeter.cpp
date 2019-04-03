#ifndef AirFlowMeter_cpp
#define AirFlowMeter_cpp

#include <Arduino.h>
#include "Tools\OhmMeter.cpp"

class AirFlowMeter
{
  private:

  public:
    OhmMeter ohmMeter;

    float getFlow()
    {
      return ohmMeter.getResistance();
    };
    
    AirFlowMeter(byte pin) : ohmMeter(pin, 330)
    {
    };

    void read()
    {
      ohmMeter.read();
    };
};

#endif