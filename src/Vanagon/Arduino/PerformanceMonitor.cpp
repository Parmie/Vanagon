#ifndef PerformanceMonitor_cpp
#define PerformanceMonitor_cpp

#include <Arduino.h>

class PerformanceMonitor
{
  private:
    unsigned long _lastMillis = 0;
    int _cycleTime = 0;

  public:
    int getCycleTime()
    {
      return _cycleTime;
    };

    void update()
    {
        unsigned long currentMillis = millis();
        if (_lastMillis != 0)
        {
            _cycleTime = currentMillis - _lastMillis;
        }
        _lastMillis = currentMillis;
    };
};

#endif