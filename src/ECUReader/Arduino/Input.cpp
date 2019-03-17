#ifndef Input_cpp
#define Input_cpp

#include <Arduino.h>

class Input
{
  protected:
    byte _pin;

  public:
    Input(byte pin)
    {
      _pin = pin;
    };
    
    virtual void read();
};

#endif