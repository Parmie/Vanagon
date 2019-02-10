#ifndef FuelTank_cpp
#define FuelTank_cpp

#include <Arduino.h>
#include "AnalogInput.cpp"

class FuelTank
{
  private:
    static const int _senderDividerResistance = 330;
    AnalogInput *_senderInput;
    float _capacity;
    float _content;

  public:
    float getCapacity()
    {
        return this->_capacity;
    };

    void setCapacity(float value)
    {
        this->_capacity = value;
    };

    float getContent()
    {
        return this->_content;
    };

    FuelTank(AnalogInput *senderInput)
    {
        this->_senderInput = senderInput;
    };

    void update()
    {
        this->_senderInput->read();
        float voltage = this->_senderInput->getVoltage();
        float resistance = (voltage * FuelTank::_senderDividerResistance) / (REF_VOLTAGE - voltage);
        float content = (4.794908061 * pow(10, -4) * pow(resistance, 2)) - (4.726976404 * pow(10, -1) * resistance) + 99.48112787;
    };
};

#endif