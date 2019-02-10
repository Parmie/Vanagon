#ifndef Exhaust_h
#define Exhaust_h

#include <Arduino.h>
#include "AnalogInput.h"

class Exhaust {
  private:
    AnalogInput *_oxygenInput;
    float _oxygenVoltage;
  public:
    float getOxygenVoltage();
    int getMixtureStatus();
    Exhaust(AnalogInput *oxygenInput);
    void update();
};

#endif