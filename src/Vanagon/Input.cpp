#ifndef Input_cpp
#define Input_cpp

#include <Arduino.h>

class Input
{
  protected:
    int _pin;

  public:
    Input(int pin)
    {
      _pin = pin;
    };
    
    void read();
};

#endif