#ifndef LambdaSensor_cpp
#define LambdaSensor_cpp

#include <Arduino.h>
#include "Arduino\AnalogInput.cpp"
#include "Tools\VoltageMeter.cpp"

class LambdaSensor {
  public:
    VoltageMeter voltageMeter;

    float getVoltage()
    {
      return voltageMeter.getVoltage();
    };

    byte getMixtureStatus()
    {
      if (voltageMeter.getVoltage() > 0.720)
      {
          return +1;
      }
      else if (voltageMeter.getVoltage() < 0.120)
      {
          return -1;
      }
      else
      {
          return 0;
      }
    };

    LambdaSensor(byte pin) : voltageMeter(pin)
    {
    };

    void read()
    {
      voltageMeter.read();
    };
};

#endif