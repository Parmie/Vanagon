#ifndef FuelLevel_cpp
#define FuelLevel_cpp

#include <Arduino.h>
#include "Arduino\AnalogInput.cpp"
#include "Tools\OhmMeter.cpp"

class FuelLevel
{
  private:
    float _capacity;

  public:
    OhmMeter ohmMeter;

    float getContent()
    {
      return (4.794908061 * pow(10, -4) * pow(ohmMeter.getResistance(), 2)) - (4.726976404 * pow(10, -1) * ohmMeter.getResistance()) + 99.48112787;
    };

    float getCapacity()
    {
      return _capacity;
    };

    void setCapacity(float value)
    {
      _capacity = value;
    };

    FuelLevel(byte pin) : ohmMeter(pin, 56)
    {
    };

    void read()
    {
      ohmMeter.read();
    };
};

#endif
