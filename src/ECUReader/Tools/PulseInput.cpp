#ifndef PulseInput_cpp
#define PulseInput_cpp

#include <Arduino.h>
#include <YetAnotherPcInt.h>
#include "..\Arduino\Input.cpp"

class PulseInput {
  private:
    byte _pin;
    int Cycle = 0;
    unsigned long _pulseStartTime;
    unsigned long _pulseEndTime;
    unsigned long _pulseLength = 0;
    unsigned long _pulsesPerMinute = 0;
    byte _pulseWidth = 0;
    unsigned long _pulseCounter = 0;

    static void pinChanged(PulseInput *input, bool pinState)
    {
      if (pinState)
      {
        unsigned long start = micros();
        if (input->_pulseStartTime < input->_pulseEndTime)
        {
          unsigned long upTime = input->_pulseEndTime - input->_pulseStartTime;
          input->_pulseLength = start - input->_pulseStartTime;
          input->_pulseWidth = upTime * 255 / input->_pulseLength;
          input->_pulsesPerMinute = 60000000 / input->_pulseLength;
        }
        input->_pulseStartTime = start;
        input->_pulseCounter++;
      }
      else
      {
        input->_pulseEndTime = micros();
      }
    };

  public:
    unsigned long getStart()
    {
      return _pulseStartTime;
    };

    unsigned long getStop()
    {
      return _pulseEndTime;
    };

    unsigned long getPulseLength()
    {
      return _pulseLength;
    };

    unsigned long getPulseCount()
    {
      return _pulseCounter;
    };

    byte getPulseWidth()
    {
      return _pulseWidth;
    };

    unsigned int getPulsesPerMinute()
    {
      return _pulsesPerMinute;
    };

    PulseInput(byte pin)
    {
      _pin = pin;
      PcInt::attachInterrupt(_pin, pinChanged, this, CHANGE, true);
    };

    ~PulseInput()
    {
      PcInt::detachInterrupt(_pin);
    };
};

#endif