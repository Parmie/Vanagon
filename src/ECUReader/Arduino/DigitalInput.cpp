#ifndef DigitalInput_cpp
#define DigitalInput_cpp

#include <Arduino.h>
#include <YetAnotherPcInt.h>
#include "Input.cpp"

class DigitalInput : Input
{
  private:
    bool _usingInterrupts = false;
    bool _state = LOW;
    byte _pulseCounter = 0;
    unsigned int _highTime = 0;
    unsigned int _lowTime = 0;
    unsigned int _lastMillis = 0;
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
          _pulseCounter++;
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

    byte getCounter()
    {
      byte result = _pulseCounter;
      _pulseCounter = 0;
      return result;
    }

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