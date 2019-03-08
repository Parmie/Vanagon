#ifndef Visualization_cpp
#define Visualization_cpp

#include <Arduino.h>
#include "Tools\Display.cpp"
#include "Tools\Button.cpp"
#include "Vanagon.cpp"
#include "ListView.cpp"
#include "GraphView.cpp"

class Visualization
{
  private:
    DigitalInput buttonInput;
    Vanagon *vanagon;
    ListView *listView1;
    ListView *listView2;
    GraphView *batteryGraphView;
    GraphView *fuelGraphView;
    GraphView *oilPressureGraphView;
    GraphView *oxygenGraphView;

    View *view;
    Display display;

  public:
    byte viewIndex;
    Button *button;

    static void buttonClicked(Visualization *visualization)
    {
        visualization->buttonClick();
    }

    Visualization(Vanagon *vanagon) : buttonInput(13, 0)
    {
        this->vanagon = vanagon;

        buttonInput.attachInterrupt();
        button = new Button(&buttonInput, Visualization::buttonClicked, this);

        viewIndex = 0;
        view = listView1 = new ListView();
        listView1->configure(0, "Batt", "V");
        listView1->configure(1, "Fuel", "L");
        listView1->configure(2, "Oil", "bar");
        listView1->configure(3, "Oxygen", "V");
        listView1->configure(4, "Button", "");
    };

    void update()
    {
        button->read();

        if (listView1 != NULL)
        {
            //if (vanagon->battery != NULL)
                listView1->setValue(0, vanagon->battery->getVoltage());
            //if (vanagon->fuelTank != NULL)
                listView1->setValue(1, vanagon->fuelTank->getContent());
            //if (vanagon->oilPressure != NULL)
                listView1->setValue(2, vanagon->oilPressure->getPressure());
            //if (vanagon->exhaust != NULL)
                listView1->setValue(3, vanagon->exhaust->getOxygenVoltage());
            //listView1->setValue(4, pulseInput->getPulseLength());
        }

        if (listView2 != NULL)
        {
            listView2->setValue(0, vanagon->induction->getTemperatureResistance());
            listView2->setValue(1, vanagon->induction->getFlowResistance());
        }

        if (batteryGraphView != NULL)
        {
            batteryGraphView->addPoint(vanagon->battery->getVoltage());
        }

        if (fuelGraphView != NULL)
        {
            fuelGraphView->addPoint(vanagon->fuelTank->getContent());
        }

        if (oilPressureGraphView != NULL)
        {
            oilPressureGraphView->addPoint(vanagon->oilPressure->getPressure());
        }

        if (oxygenGraphView != NULL)
        {
            oxygenGraphView->addPoint(vanagon->exhaust->getOxygenVoltage());
        }

        if (view != NULL)
        {
            display.update(view);
        }
    };

    void buttonClick()
    {
        switch (viewIndex)
        {
        case 0:
        {
            delete listView1;
            listView1 = NULL;

            view = listView2 = new ListView();
            listView2->configure(0, "Air T", "C");
            listView2->configure(1, "Air F", "");

            viewIndex = 1;
            break;
        }
        case 1:
        {
            delete listView2;
            listView2 = NULL;

            view = batteryGraphView = new GraphView("Battery", "V", 0, 15, 1, 12);
            viewIndex = 2;
            break;
        }
        case 2:
        {
            delete batteryGraphView;
            batteryGraphView = NULL;

            view = fuelGraphView = new GraphView("Fuel", "L", 0, 70, 10, 0);
            viewIndex = 3;
            break;
        }
        case 3:
        {
            delete fuelGraphView;
            fuelGraphView = NULL;

            view = oilPressureGraphView = new GraphView("Oil", "bar", 0, 5, 1, 0);
            viewIndex = 4;
            break;
        }
        case 4:
        {
            delete oilPressureGraphView;
            oilPressureGraphView = NULL;

            view = oxygenGraphView = new GraphView("Oxygen", "V", 0, 1, 0.1, 0.5);
            viewIndex = 5;
            break;
        }
        case 5:
        {
            delete oxygenGraphView;
            oxygenGraphView = NULL;

            view = listView1 = new ListView();
            listView1->configure(0, "Batt", "V");
            listView1->configure(1, "Fuel", "L");
            listView1->configure(2, "Oil", "bar");
            listView1->configure(3, "Oxygen", "V");
            listView1->configure(4, "Button", "");
            viewIndex = 0;
            break;
        }
        }
    }
};

#endif