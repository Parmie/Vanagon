#ifndef FuelTank_cpp
#define FuelTank_cpp

#include <Arduino.h>
#include "AnalogInput.cpp"
#include "VoltageMeter.cpp"

class FuelTank
{
  private:
    static const int _senderDividerResistance = 330;
    VoltageMeter _senderVoltage;
    float _capacity;
    float _content;

  public:
    float getCapacity()
    {
        return _capacity;
    };

    void setCapacity(float value)
    {
        _capacity = value;
    };

    float getContent()
    {
        return _content;
    };

    FuelTank(AnalogInput *senderInput) : _senderVoltage(senderInput)
    {
    };

    void update()
    {
        _senderVoltage.update();
        float resistance = (_senderVoltage.getVoltage() * FuelTank::_senderDividerResistance) / (_senderVoltage.getReference() - _senderVoltage.getVoltage());
        float content = (4.794908061 * pow(10, -4) * pow(resistance, 2)) - (4.726976404 * pow(10, -1) * resistance) + 99.48112787;
    };
};

#endif