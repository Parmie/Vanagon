#ifndef DigitalInput_cpp
#define DigitalInput_cpp

#include <Arduino.h>
#include "Input.cpp"

class DigitalInput : Input
{
  private:
    bool _state = LOW;
    bool _previousState = LOW;
    bool _rising = false;
    bool _falling = false;
    unsigned long _debounceTimer = 0;
    unsigned long _debouncePeriod = 0;

  public:
    bool getState()
    {
      return _state;
    };

    bool getRising()
    {
      return _rising;
    };

    bool getFalling()
    {
      return _falling;
    };

    long setDebouncePeriod(unsigned long period)
    {
      _debouncePeriod = period;
    };

    DigitalInput(int pin, long debouncePeriod = 25) : Input(pin)
    {
      _debouncePeriod = debouncePeriod;
      pinMode(pin, INPUT);
    };

    void read()
    {
      _rising = false;
      _falling = false;

      bool reading = digitalRead(_pin);

      if (reading == _state) // Pin is the same state
      {
        // Reset everything
        _debounceTimer = millis();
      }
      else if ((millis() - _debounceTimer) > _debouncePeriod) // Pin is another state for period
      {
        // Change state
        _state = reading;

        if (reading)
        {
          // Set rising edge
          _rising = true;
        }
        else
        {
          // Set falling edge
          _falling = true;
        }
      }
    };
};

#endif