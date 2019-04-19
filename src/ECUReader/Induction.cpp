#ifndef Induction_cpp
#define Induction_cpp

#include <Arduino.h>
#include "Tools\VoltMeter.cpp"
#include "Arduino\DigitalInput.cpp"

class Induction
{
  private:
  public:
    VoltMeter voltMeter;
    DigitalInput throttleSwitch;

    float getFlow()
    {
      return map(voltMeter.getVoltage() * 100, 18, 440, 0, 100) / 100.0;
      //return map(voltMeter.getVoltage(), 4.69, 0.41, 0.0, 1.0);
      //return voltMeter.getVoltage();
    };

    bool getEnrichment()
    {
      return !throttleSwitch.getState();
    };

    Induction(byte airFlowPin, byte enrichmentPin) : voltMeter(airFlowPin),
      throttleSwitch(enrichmentPin, 0) {};

    void read()
    {
      voltMeter.read();
      throttleSwitch.read();
    };
};

#endif
