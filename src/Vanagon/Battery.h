#ifndef Battery_h
#define Battery_h

#include <Arduino.h>
#include "AnalogInput.h"

class Battery {
  private:
    AnalogInput *_input;
    float _voltage;
  public:
    float getVoltage();
    Battery(AnalogInput *input);
    void update();
};

#endif