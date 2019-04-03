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
            // Overview
            print(performanceMonitor->getCycleTime());
            print(vanagon->battery.getVoltage());
            print(vanagon->fuelLevel.getContent());
            print(vanagon->oilPressure.getPressure());
            print(vanagon->lambdaSensor.getVoltage());
            print(vanagon->injection.getRevolutions());

            break;
        }
        case 1:
        {
            // Battery
            print(vanagon->battery.voltageDivider.voltMeter.input.getValue());
            print(vanagon->battery.voltageDivider.voltMeter.getVoltage());
            print(vanagon->battery.voltageDivider.getVoltage());
            print(vanagon->battery.getVoltage());
            break;
        }
        case 2:
        {
            // Fuel level
            print(vanagon->fuelLevel.ohmMeter.voltMeter.input.getValue());
            print(vanagon->fuelLevel.ohmMeter.voltMeter.getVoltage());
            print(vanagon->fuelLevel.ohmMeter.getResistance());
            print(vanagon->fuelLevel.getContent());
            break;
        }
        case 3:
        {
            // Oil pressure
            print(vanagon->oilPressure.ohmMeter.voltMeter.input.getValue());
            print(vanagon->oilPressure.ohmMeter.voltMeter.getVoltage());
            print(vanagon->oilPressure.ohmMeter.getResistance());
            print(vanagon->oilPressure.getPressure());
            break;
        }
        case 4:
        {
            // Coolant temperature - A4
            print(vanagon->coolantTemperature.ohmMeter.voltMeter.input.getValue());
            print(vanagon->coolantTemperature.ohmMeter.voltMeter.getVoltage());
            print(vanagon->coolantTemperature.ohmMeter.getResistance());
            print(vanagon->coolantTemperature.getTemperature());
            break;
        }
        case 5:
        {
            // Air temperature - A3
            print(vanagon->intakeTemperature.ohmMeter.voltMeter.input.getValue());
            print(vanagon->intakeTemperature.ohmMeter.voltMeter.getVoltage());
            print(vanagon->intakeTemperature.ohmMeter.getResistance());
            print(vanagon->intakeTemperature.getTemperature());
            break;
        }
        case 6:
        {
            // Air flow
            print(vanagon->airFlowMeter.ohmMeter.voltMeter.input.getValue());
            print(vanagon->airFlowMeter.ohmMeter.voltMeter.getVoltage());
            print(vanagon->airFlowMeter.ohmMeter.getResistance());
            print(vanagon->airFlowMeter.getFlow());
            break;
        }
        case 7:
        {
            // Lambda sensor - A1
            print(vanagon->lambdaSensor.voltageMeter.input.getValue());
            print(vanagon->lambdaSensor.voltageMeter.getVoltage());
            print(vanagon->lambdaSensor.getVoltage());
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