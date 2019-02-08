#ifndef FuelTank_h
#define FuelTank_h

#include <Arduino.h>
#include "AnalogInput.h"

class FuelTank {
  private:
    static const int _senderDividerResistance = 330;
    AnalogInput *_senderInput;
    float _capacity;
    float _content;
  public:
    float getCapacity();
    void setCapacity(float value);
    float getContent();
    FuelTank(AnalogInput *senderInput);
    void update();
};

#endif