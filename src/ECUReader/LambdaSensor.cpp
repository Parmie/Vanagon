#ifndef LambdaSensor_cpp
#define LambdaSensor_cpp

#include <Arduino.h>
#include "Arduino\AnalogInput.cpp"
#include "Tools\VoltMeter.cpp"

class LambdaSensor {
  public:
    VoltMeter voltMeter;

    float getVoltage()
    {
      return voltMeter.getVoltage();
    };

    byte getMixtureStatus()
    {
      if (voltMeter.getVoltage() > 0.720)
      {
        return +1;
      }
      else if (voltMeter.getVoltage() < 0.120)
      {
        return -1;
      }
      else
      {
        return 0;
      }
    };

    LambdaSensor(byte pin) : voltMeter(pin)
    {
    };

    void read()
    {
      voltMeter.read();
    };
};

#endif
