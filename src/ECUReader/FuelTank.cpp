#ifndef FuelTank_cpp
#define FuelTank_cpp

#include <Arduino.h>
#include "Arduino\AnalogInput.cpp"
#include "Tools\ResistanceMeter.cpp"

class FuelTank
{
  private:
    ResistanceMeter _resistanceMeter;
    float _capacity;

  public:
    float getResistance()
    {
      return _resistanceMeter.getResistance();
    };

    float getContent()
    {
        return (4.794908061 * pow(10, -4) * pow(_resistanceMeter.getResistance(), 2)) - (4.726976404 * pow(10, -1) * _resistanceMeter.getResistance()) + 99.48112787;
    };

    float getCapacity()
    {
        return _capacity;
    };

    void setCapacity(float value)
    {
        _capacity = value;
    };

    FuelTank(AnalogInput *resistanceInput) : _resistanceMeter(resistanceInput, 326)
    {
    };

    void update()
    {
      _resistanceMeter.update();
    };

    void setBaseVoltage(float voltage)
    {
      _resistanceMeter.setBaseVoltage(voltage);
    };
};

#endif