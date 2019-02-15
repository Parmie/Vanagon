#ifndef DigitalInput_cpp
#define DigitalInput_cpp

#include <Arduino.h>
#include <YetAnotherPcInt.h>
#include "Input.cpp"

byte INTERRUPTS = 0;

class DigitalInput : Input
{
  private:
    bool _usingInterrupts = false;
    bool _state = LOW;
    bool _newState = LOW;
    bool _rising = false;
    bool _falling = false;
    unsigned long _debounceTimer = 0;
    unsigned long _debouncePeriod = 0;

    static void pinChanged(DigitalInput *input, bool pinState)
    {
      input->_newState = pinState;
    }

    void changeState(bool state)
    {
      INTERRUPTS = state;
      
      _rising = false;
      _falling = false;

      if (state == _state) // Pin is the same state
      {
        // Reset everything
        _debounceTimer = millis();
      }
      else if ((millis() - _debounceTimer) > _debouncePeriod) // Pin is another state for period
      {
        // Change state
        _state = state;

        if (state)
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
    }

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

    void attachInterrupt()
    {
      if (!_usingInterrupts)
      {
        PcInt::attachInterrupt(_pin, pinChanged, this, CHANGE, true);
        _usingInterrupts = true;
      }
    };

    void detachInterrupt()
    {
      if (_usingInterrupts)
      {
        PcInt::detachInterrupt(_pin);
        _usingInterrupts = false;
      }
    };

    void read()
    {
      if (!_usingInterrupts)
      {
        _newState = digitalRead(_pin);
      }
      changeState(_newState);
    };
};

#endif