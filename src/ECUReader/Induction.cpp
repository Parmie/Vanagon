#ifndef Induction_cpp
#define Induction_cpp

#include <Arduino.h>
#include "Tools\OhmMeter.cpp"
#include "Arduino\DigitalInput.cpp"

class Induction
{
private:
public:
  OhmMeter ohmMeter;
  DigitalInput throttleSwitch;

  float getFlow()
  {
    return ohmMeter.getResistance();
  };

  bool getEnrichment()
  {
    return throttleSwitch.getState();
  };

  Induction(byte airFlowPin, byte enrichmentPin) : ohmMeter(airFlowPin, 330),
                                                   throttleSwitch(enrichmentPin, 0){};

  void read()
  {
    ohmMeter.read();
    throttleSwitch.read();
  };
};

#endif