#ifndef Injection_cpp
#define Injection_cpp

#include <Arduino.h>
#include "Tools\PulseInput.cpp"

class Injection
{
  private:
    PulseInput *_hallSensorInput;

  public:
    Injection(PulseInput *hallSensorInput) : _hallSensorInput(hallSensorInput)
    {
    };

    unsigned int getRevolutions()
    {
      return _hallSensorInput->getPulsesPerMinute() / 2;
    }
};

#endif