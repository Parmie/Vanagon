#ifndef Battery_cpp
#define Battery_cpp

#include <Arduino.h>
#include "Arduino\AnalogInput.cpp"
#include "Tools\VoltageMeter.cpp"

class Battery {
  private:
    VoltageMeter _meter;

  public:
    float getVoltage()
    {
      return _meter.getVoltage();
    };

    Battery(AnalogInput *input) : _meter(input, {216.3, 98.8})
    {
    };

    void update()
    {
      _meter.update();
    };
};

#endif