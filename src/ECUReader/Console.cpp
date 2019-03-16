#ifndef Console_cpp
#define Console_cpp

#include <Arduino.h>
#include "Vanagon.cpp"
#include "Arduino\PerformanceMonitor.cpp"

class Console
{
  private:
  public:
    Console(unsigned long baudRate = 9600)
    {
        Serial.begin(baudRate);
    };

    void sendText(Vanagon *vanagon, PerformanceMonitor *performanceMonitor)
    {
        print(performanceMonitor->getCycleTime());
        print(vanagon->battery->getVoltage());
        print(vanagon->fuelTank->getResistance());
        print(vanagon->oilPressure->getResistance());
        print(vanagon->exhaust->getOxygenVoltage());
        print(vanagon->injection->getRevolutions());
        Serial.println();
        
    };

    void print(float value)
    {
        Serial.print(String(value));
        Serial.print(char(32));
    };

    void print(int value)
    {
        Serial.print(String(value));
        Serial.print(char(32));
    };

    void print(unsigned int value)
    {
        Serial.print(String(value));
        Serial.print(char(32));
    };
};

#endif