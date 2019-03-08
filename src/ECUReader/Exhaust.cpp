#ifndef Exhaust_cpp
#define Exhaust_cpp

#include <Arduino.h>
#include "Arduino\AnalogInput.cpp"
#include "Tools\VoltageMeter.cpp"

class Exhaust {
  private:
    VoltageMeter _oxygenVoltage;

  public:
    float getOxygenVoltage()
    {
      return _oxygenVoltage.getVoltage();
    };

    int getMixtureStatus()
    {
      if (_oxygenVoltage.getVoltage() > 0.720)
      {
          return +1;
      }
      else if (_oxygenVoltage.getVoltage() < 0.120)
      {
          return -1;
      }
      else
      {
          return 0;
      }
    };

    Exhaust(AnalogInput *oxygenInput) : _oxygenVoltage(oxygenInput)
    {
    };

    void update()
    {
      _oxygenVoltage.update();
    };
};

#endif