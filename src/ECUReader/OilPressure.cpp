#ifndef OilPressure_cpp
#define OilPressure_cpp

#include <Arduino.h>
#include "Arduino\AnalogInput.cpp"
#include "Tools\ResistanceMeter.cpp"

class OilPressure
{
  private:

  public:
  ResistanceMeter ohmMeter;

    float getPressure()
    {
      return -(sqrt(5)*sqrt(6726892997-7364000*ohmMeter.getResistance())-182325)/3682;
    };

    OilPressure(byte pin) : ohmMeter(pin, 150)
    {
    };

    void read()
    {
      ohmMeter.read();
    };
};

#endif