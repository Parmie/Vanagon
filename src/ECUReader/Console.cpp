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

    Console(Vanagon *vanagon, PerformanceMonitor *performanceMonitor) : buttonInput(13, 0)
    {
        this->vanagon = vanagon;
        this->performanceMonitor = performanceMonitor;
        viewIndex = 0;
    };

    void init(unsigned long baudRate = 9600)
    {
        Serial.begin(baudRate);
        buttonInput.attachInterrupt();
        button = new Button(&buttonInput, Console::buttonClicked, this);
    }

    void buttonClick()
    {
        viewIndex++;
    };

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
            print(vanagon->lambdaSensor.getVoltage());
            print(vanagon->intakeTemperature.getTemperature());
            print(vanagon->coolantTemperature.getTemperature());
            print(vanagon->oilPressure.getPressure());
            print(vanagon->fuelLevel.getContent());

            break;
        }
        case 1:
        {
            // Battery - A0
            print(vanagon->battery.voltageDivider.voltMeter.input.getValue());
            print(vanagon->battery.voltageDivider.voltMeter.getVoltage());
            print(vanagon->battery.voltageDivider.getVoltage());
            print(vanagon->battery.getVoltage());
            break;
        }
        case 2:
        {
            // Lambda sensor - A1
            print(vanagon->lambdaSensor.voltageMeter.input.getValue());
            print(vanagon->lambdaSensor.voltageMeter.getVoltage());
            print(vanagon->lambdaSensor.getVoltage());
            break;
        }
        case 3:
        {
            // Air flow - A2
            print(vanagon->airFlowMeter.ohmMeter.voltMeter.input.getValue());
            print(vanagon->airFlowMeter.ohmMeter.voltMeter.getVoltage());
            print(vanagon->airFlowMeter.ohmMeter.getResistance());
            print(vanagon->airFlowMeter.getFlow());
            break;
        }
        case 4:
        {
            // Air temperature - A3
            print(vanagon->intakeTemperature.ohmMeter.voltMeter.input.getValue());
            print(vanagon->intakeTemperature.ohmMeter.voltMeter.getVoltage());
            print(vanagon->intakeTemperature.ohmMeter.getResistance());
            print(vanagon->intakeTemperature.getTemperature());
            break;
        }
        case 5:
        {
            // Coolant temperature - A4
            print(vanagon->coolantTemperature.ohmMeter.voltMeter.input.getValue());
            print(vanagon->coolantTemperature.ohmMeter.voltMeter.getVoltage());
            print(vanagon->coolantTemperature.ohmMeter.getResistance());
            print(vanagon->coolantTemperature.getTemperature());
            break;
        }
        case 6:
        {
            // Oil pressure - A5
            print(vanagon->oilPressure.ohmMeter.voltMeter.input.getValue());
            print(vanagon->oilPressure.ohmMeter.voltMeter.getVoltage());
            print(vanagon->oilPressure.ohmMeter.getResistance());
            print(vanagon->oilPressure.getPressure());
            break;
        }
        case 7:
        {
            // Fuel level - A6
            print(vanagon->fuelLevel.ohmMeter.voltMeter.input.getValue());
            print(vanagon->fuelLevel.ohmMeter.voltMeter.getVoltage());
            print(vanagon->fuelLevel.ohmMeter.getResistance());
            print(vanagon->fuelLevel.getContent());
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