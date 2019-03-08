#ifndef Pin_cpp
#define Pin_cpp

#include <Arduino.h>

class Pin
{
  protected:
    int _pin;

    Input(int pin)
    {
      _pin = pin;
    };
    
    virtual void read();

  public:
    int getPin()
    {
      return _pin;
    };
};

class AnalogPin : Pin
{
  private:
    AnalogPin(int pin) : Pin(pin)
    {
    };
};

#endif