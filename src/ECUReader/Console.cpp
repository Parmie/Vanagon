#ifndef Console_cpp
#define Console_cpp

#include <Arduino.h>
#include "Vanagon.cpp"
#include "Arduino\PerformanceMonitor.cpp"
#include "Arduino\DigitalInput.cpp"
#include "Tools\Button.cpp"

class Console
{
  private:
    DigitalInput buttonInput;
    Vanagon *vanagon;
    PerformanceMonitor *performanceMonitor;

  public:
    byte viewIndex;
    Button *button;

    static void buttonClicked(Console *console)
    {
        console->buttonClick();
    }

    Console(Vanagon *vanagon, PerformanceMonitor *performanceMonitor, unsigned long baudRate = 9600) : buttonInput(13, 0)
    {
        this->vanagon = vanagon;
        this->performanceMonitor = performanceMonitor;
        Serial.begin(baudRate);
        buttonInput.attachInterrupt();
        button = new Button(&buttonInput, Console::buttonClicked, this);
        viewIndex = 2;
    };

    void buttonClick()
    {
        viewIndex++;
    }

    void update()
    {
        button->read();

        print(viewIndex);

        switch (viewIndex)
        {
        case 0:
        {
            print(performanceMonitor->getCycleTime());
            print(vanagon->battery.getVoltage());
            print(vanagon->fuelTank.getContent());
            print(vanagon->oilPressure.getPressure());
            print(vanagon->exhaust.getOxygenVoltage());
            print(vanagon->injection.getRevolutions());

            break;
        }
        case 1:
        {
            print(vanagon->battery.voltageDivider.voltMeter.input.getValue());
            print(vanagon->battery.voltageDivider.voltMeter.getVoltage());
            print(vanagon->battery.voltageDivider.getVoltage());
            print(vanagon->battery.getVoltage());
            break;
        }
        case 2:
        {
            print(vanagon->fuelTank.ohmMeter.voltMeter.input.getValue());
            print(vanagon->fuelTank.ohmMeter.voltMeter.getVoltage());
            print(vanagon->fuelTank.ohmMeter.getResistance());
            print(vanagon->fuelTank.getContent());
            break;
        }
        case 3:
        {
            print(vanagon->oilPressure.ohmMeter.voltMeter.input.getValue());
            print(vanagon->oilPressure.ohmMeter.voltMeter.getVoltage());
            print(vanagon->oilPressure.ohmMeter.getResistance());
            print(vanagon->oilPressure.getPressure());
            break;
        }
        default:
        {
            viewIndex = 0;
            break;
        }
        }

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