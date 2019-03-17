#ifndef Battery_cpp
#define Battery_cpp

#include <Arduino.h>
#include "Tools\VoltageDivider.cpp"

class Battery {
  private:

  public:
    VoltageDivider voltageDivider;

    float getVoltage()
    {
      return voltageDivider.getVoltage();
    };

    Battery(byte pin) : voltageDivider(pin, 216.3, 98.8)
    {
    };

    void read()
    {
      voltageDivider.read();
    }
};

#endif