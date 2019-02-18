#include "Arduino\PerformanceMonitor.cpp"
#include "Arduino\AnalogInput.cpp"
#include "Arduino\DigitalInput.cpp"
#include "Tools\Button.cpp"
#include "Battery.cpp"
#include "FuelTank.cpp"
#include "OilPressure.cpp"
#include "Exhaust.cpp"
#include "Tools\Display.cpp"
#include "ListView.cpp"
#include "GraphView.cpp"

const int in_airFlow = A2;
const int in_airTemperature = A3;
const int in_coolantTemperature = A4;
const int in_fuelLevel = A5;
const int in_starter = 2;
const int in_hallSender = 3;
const int in_diagnostics = 4;
const int in_throttleSwitch = 5;
const int in_injectors = 6;
const int in_ignition = 7;

PerformanceMonitor performanceMonitor;

AnalogInput sensorVoltageInput(A7);
VoltageMeter sensorVoltage(&sensorVoltageInput, {148.6, 148.3});

AnalogInput batteryInput(A0);
Battery battery(&batteryInput);

AnalogInput fuelSenderInput(A5);
FuelTank fuelTank(&fuelSenderInput);

AnalogInput oilPressureInput(A6);
OilPressure oilPressure(&oilPressureInput);

AnalogInput oxygenSensorInput(A1);
Exhaust exhaust(&oxygenSensorInput);

extern void buttonClick();
DigitalInput buttonInput(13, 0);
Button button(&buttonInput, buttonClick);

ListView *listView1;
GraphView *batteryGraphView;
GraphView *fuelGraphView;
GraphView *oilPressureGraphView;
GraphView *oxygenGraphView;

byte viewIndex = 0;
View *view;
Display display;

void setup()
{
  analogReference(EXTERNAL);
  Serial.begin(9600);
  buttonInput.attachInterrupt();
}

void loop()
{
  performanceMonitor.update();

  button.read();

  sensorVoltage.update();

  battery.update();

  fuelTank.setBaseVoltage(sensorVoltage.getVoltage());
  fuelTank.update();

  oilPressure.setBaseVoltage(sensorVoltage.getVoltage());
  oilPressure.update();

  exhaust.update();

  Serial.print(String(battery.getVoltage()));
  Serial.print(" ");
  Serial.print(String(fuelTank.getContent()));
  Serial.print(" ");
  Serial.print(String(oilPressure.getPressure()));
  Serial.print(" ");
  Serial.print(String(exhaust.getOxygenVoltage()));
  Serial.print(" ");
  Serial.print(String(viewIndex));
  Serial.println();

  if (listView1 != NULL)
  {
    listView1->setValue(0, battery.getVoltage());
    listView1->setValue(1, fuelTank.getContent());
    listView1->setValue(2, oilPressure.getPressure());
    listView1->setValue(3, exhaust.getOxygenVoltage());
    listView1->setValue(4, INTERRUPTS);
  }

  if (batteryGraphView != NULL)
  {
    batteryGraphView->addPoint(battery.getVoltage());
  }

  if (fuelGraphView != NULL)
  {
    fuelGraphView->addPoint(fuelTank.getContent());
  }

  if (oilPressureGraphView != NULL)
  {
    oilPressureGraphView->addPoint(oilPressure.getPressure());
  }

  if (oxygenGraphView != NULL)
  {
    oxygenGraphView->addPoint(exhaust.getOxygenVoltage());
  }

  if (view != NULL)
  {
    display.update(view);
  }
}

void buttonClick()
{
  switch (viewIndex)
  {
    case 0:
    {
      delete listView1;
      listView1 = NULL;

      view = batteryGraphView = new GraphView("Battery", "V", 0, 15, 1, 12);
      viewIndex = 1;
      break;
    }
    case 1:
    {
      delete batteryGraphView;
      batteryGraphView = NULL;
      
      view = fuelGraphView = new GraphView("Fuel", "L", 0, 70, 10, 0);
      viewIndex = 2;
      break;
    }
    case 2:
    {
      delete fuelGraphView;
      fuelGraphView = NULL;
      
      view = oilPressureGraphView = new GraphView("Oil", "bar", 0, 5, 1, 0);
      viewIndex = 3;
      break;
    }
    case 3:
    {
      delete oilPressureGraphView;
      oilPressureGraphView = NULL;
      
      view = oxygenGraphView = new GraphView("Oxygen", "V", 0, 1, 0.1, 0.5);
      viewIndex = 4;
      break;
    }
    case 4:
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