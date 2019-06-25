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

    Battery(byte pin) : voltageDivider(pin, 57.396, 12) // Resistors are 56 and 12 ohm
    {
    };

    void read()
    {
      voltageDivider.read();
    }
};

#endif
