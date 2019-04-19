#include "Display.cpp"
#include "ListView.cpp"
#include "GraphView.cpp"

Display display;
ListView *placeHolder;
ListView *overview1;
ListView *overview2;
GraphView *batteryGraph;
GraphView *oxygenGraph;
GraphView *airFlowGraph;
GraphView *airTempGraph;
GraphView *coolantTempGraph;
GraphView *oilPressureGraph;
GraphView *fuelLevelGraph;
View *view;
short subPage = 0;

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), buttonPressed, RISING);
}

void buttonPressed()
{
  subPage++;
}

void loop()
{
  while (Serial.available() > 0)
  {
    if (Serial.read() == '\n')
    {
      digitalWrite(13, HIGH);
      int page = Serial.readStringUntil(' ').toInt();

      switch (page)
      {
        case 0:
          {
            int cycleTime = Serial.readStringUntil(' ').toInt();
            float batteryVoltage = Serial.readStringUntil(' ').toFloat();
            float oxygenVoltage = Serial.readStringUntil(' ').toFloat();
            float airFlow = Serial.readStringUntil(' ').toFloat();
            float airTemp = Serial.readStringUntil(' ').toFloat();
            float coolTemp = Serial.readStringUntil(' ').toFloat();
            float oilPressure = Serial.readStringUntil(' ').toFloat();
            bool oilLow = Serial.readStringUntil(' ') == "1";
            bool oilHigh = Serial.readStringUntil(' ') == "1";
            float fuelLevel = Serial.readStringUntil(' ').toFloat();

            switch (subPage)
            {
              case 0:
                {
                  if (overview1 == NULL)
                  {
                    clearViews();
                    view = overview1 = new ListView();
                    overview1->configure(0, "Batt", "V");
                    overview1->configure(1, "O2", "V");
                    overview1->configure(2, "AirF", "ohm");
                    overview1->configure(3, "AirT", "C");
                    overview1->configure(4, "CoolT", "C");
                  }

                  overview1->setValue(0, String(batteryVoltage));
                  //overview1->setValue(0, String(Serial.available()));
                  overview1->setValue(1, String(oxygenVoltage));
                  overview1->setValue(2, String(airFlow));
                  overview1->setValue(3, String(airTemp));
                  overview1->setValue(4, String(coolTemp));

                  break;
                }
              case 1:
                {
                  if (overview2 == NULL)
                  {
                    clearViews();
                    view = overview2 = new ListView();
                    overview2->configure(0, "OilP", "bar");
                    overview2->configure(1, "OilL", "");
                    overview2->configure(2, "OilH", "");
                    overview2->configure(3, "Fuel", "L");
                  }

                  overview2->setValue(0, String(oilPressure));
                  overview2->setValue(1, String(oilLow));
                  overview2->setValue(2, String(oilHigh));
                  overview2->setValue(3, String(fuelLevel));

                  break;
                }
              default:
                {
                  subPage = 0;

                  break;
                }
            }

            break;
          }
        case 1:
          {
            if (batteryGraph == NULL)
            {
              clearViews();
              view = batteryGraph = new GraphView("Battery", "V", 0, 15, 1, 12);
            }

            Serial.readStringUntil(' ');
            Serial.readStringUntil(' ');
            Serial.readStringUntil(' ');
            float batteryVoltage = Serial.readStringUntil(' ').toFloat();
            batteryGraph->addPoint(batteryVoltage);

            break;
          }
        case 2:
          {
            if (oxygenGraph == NULL)
            {
              clearViews();
              view = oxygenGraph = new GraphView("Oxygen", "V", 0, 1, 0.1, 0.5);
            }

            Serial.readStringUntil(' ');
            Serial.readStringUntil(' ');
            float lambdaVoltage = Serial.readStringUntil(' ').toFloat();
            oxygenGraph->addPoint(lambdaVoltage);

            break;
          }
        case 3:
          {
            if (airFlowGraph == NULL)
            {
              clearViews();
              view = airFlowGraph = new GraphView("AirF", "%", 0, 100, 10, 100);
            }

            Serial.readStringUntil(' ');
            Serial.readStringUntil(' ');
            float airFlow = Serial.readStringUntil(' ').toFloat();
            airFlowGraph->addPoint(airFlow * 100);

            break;
          }
        case 4:
          {
            if (airTempGraph == NULL)
            {
              clearViews();
              view = airTempGraph = new GraphView("AirT", "C", 0, 60, 20, 0);
            }

            Serial.readStringUntil(' ');
            Serial.readStringUntil(' ');
            Serial.readStringUntil(' ');
            float airTemperature = Serial.readStringUntil(' ').toFloat();
            airTempGraph->addPoint(airTemperature);

            break;
          }
        case 5:
          {
            if (coolantTempGraph == NULL)
            {
              clearViews();
              view = coolantTempGraph = new GraphView("CoolT", "C", 0, 120, 20, 90);
            }

            Serial.readStringUntil(' ');
            Serial.readStringUntil(' ');
            Serial.readStringUntil(' ');
            float coolantTemperature = Serial.readStringUntil(' ').toFloat();
            coolantTempGraph->addPoint(coolantTemperature);

            break;
          }
        case 6:
          {
            if (oilPressureGraph == NULL)
            {
              clearViews();
              view = oilPressureGraph = new GraphView("OilP", "bar", 0, 5, 1, 0);
            }

            Serial.readStringUntil(' ');
            Serial.readStringUntil(' ');
            Serial.readStringUntil(' ');
            float oilPressure = Serial.readStringUntil(' ').toFloat();
            oilPressureGraph->addPoint(oilPressure);

            break;
          }
        case 7:
          {
            if (fuelLevelGraph == NULL)
            {
              clearViews();
              view = fuelLevelGraph = new GraphView("Fuel", "L", 0, 120, 20, 90);
            }

            Serial.readStringUntil(' ');
            Serial.readStringUntil(' ');
            Serial.readStringUntil(' ');
            float fuelLevel = Serial.readStringUntil(' ').toFloat();
            fuelLevelGraph->addPoint(fuelLevel);

            break;
          }
        default:
          {
            if (placeHolder == NULL)
            {
              clearViews();
              view = placeHolder = new ListView();
              placeHolder->configure(0, "???", "");
            }

            placeHolder->setValue(0, String(page));

            break;
          }
      }
      digitalWrite(13, LOW);
      return;
    }
  }

  if (view != NULL)
  {
    display.update(view);
  }
}

void clearViews()
{
  if (placeHolder != NULL)
  {
    delete placeHolder;
    placeHolder = NULL;
  }

  if (overview1 != NULL)
  {
    delete overview1;
    overview1 = NULL;
  }

  if (overview2 != NULL)
  {
    delete overview2;
    overview2 = NULL;
  }

  if (batteryGraph != NULL)
  {
    delete batteryGraph;
    batteryGraph = NULL;
  }

  if (oxygenGraph != NULL)
  {
    delete oxygenGraph;
    oxygenGraph = NULL;
  }

  if (airFlowGraph != NULL)
  {
    delete airFlowGraph;
    airFlowGraph = NULL;
  }

  if (airTempGraph != NULL)
  {
    delete airTempGraph;
    airTempGraph = NULL;
  }

  if (coolantTempGraph != NULL)
  {
    delete coolantTempGraph;
    coolantTempGraph = NULL;
  }

  if (oilPressureGraph != NULL)
  {
    delete oilPressureGraph;
    oilPressureGraph = NULL;
  }

  if (fuelLevelGraph != NULL)
  {
    delete fuelLevelGraph;
    fuelLevelGraph = NULL;
  }

  view = NULL;
}
