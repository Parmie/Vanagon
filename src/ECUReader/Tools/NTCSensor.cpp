#ifndef NTCSensor_cpp
#define NTCSensor_cpp

#include <Arduino.h>
#include "..\Arduino\AnalogInput.cpp"
#include "OhmMeter.cpp"

class NTCSensor
{
private:
  unsigned short _r25;
  unsigned short _beta;

public:
  OhmMeter ohmMeter;

  float getTemperature()
  {
    float resistance = ohmMeter.getResistance();
    //float tempK = (_beta / log(resistance / _r25));
    float temp = 1 / ((log(resistance / _r25) / _beta) + (1 / (273.15 + 25))) - 273.15;
    return temp;
  };

  NTCSensor(byte pin, float dividerResistance, unsigned int r25, unsigned short beta) : ohmMeter(pin, dividerResistance)
  {
    _r25 = r25;
    _beta = beta;
  };

  void read()
  {
    ohmMeter.read();
  };
};

#endif