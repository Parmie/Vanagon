#ifndef FuelTank_cpp
#define FuelTank_cpp

#include <Arduino.h>
#include "Arduino\AnalogInput.cpp"
#include "Tools\ResistanceMeter.cpp"

class FuelTank
{
  private:
    float _capacity;

  public:
    ResistanceMeter ohmMeter;

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

    FuelTank(byte pin) : ohmMeter(pin, 326)
    {
    };

    void read()
    {
      ohmMeter.read();
    };
};

#endif