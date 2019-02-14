#ifndef OilPressure_cpp
#define OilPressure_cpp

#include <Arduino.h>
#include "Arduino\AnalogInput.cpp"
#include "Tools\ResistanceMeter.cpp"

class OilPressure
{
  private:
    ResistanceMeter _resistanceMeter;

  public:

    float getResistance()
    {
      return _resistanceMeter.getResistance();
    };

    float getPressure()
    {
      return -(sqrt(5)*sqrt(6726892997-7364000*_resistanceMeter.getResistance())-182325)/3682;
    };

    OilPressure(AnalogInput *resistanceInput) : _resistanceMeter(resistanceInput, 150)
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