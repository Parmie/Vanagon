#ifndef Injection_cpp
#define Injection_cpp

#include <Arduino.h>
#include "Tools\PulseInput.cpp"

class Injection
{
  private:
    PulseInput hallSensorInput;

  public:
    Injection(byte hallSensorPin) : hallSensorInput(hallSensorPin)
    {
    };

    unsigned int getRevolutions()
    {
      return hallSensorInput.getPulsesPerMinute() / 2;
    }
};

#endif