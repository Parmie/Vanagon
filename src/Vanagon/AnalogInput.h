#ifndef AnalogInput_h
#define AnalogInput_h

#include <Arduino.h>

const float REF_VOLTAGE = 4.096;

class AnalogInput
{
  private:
    int _pin;
    float _voltage;
  public:
    float getVoltage();
    AnalogInput(int pin);
    void read();
};

#endif