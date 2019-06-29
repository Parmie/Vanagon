#ifndef Camshaft_cpp
#define Camshaft_cpp

#include <Arduino.h>
#include "Tools\PulseInput.cpp"

class Camshaft
{
  private:

  public:
    PulseInput hallSensorInput;
    
    Camshaft(byte hallSensorPin) : hallSensorInput(hallSensorPin)
    {
    };

    unsigned int getRevolutions()
    {
      return hallSensorInput.getPulsesPerMinute() / 2;
    }
};

#endif