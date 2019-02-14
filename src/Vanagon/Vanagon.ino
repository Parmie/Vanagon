#include "PerformanceMonitor.cpp"
#include "AnalogInput.cpp"
#include "DigitalInput.cpp"
#include "Button.cpp"
#include "Battery.cpp"
#include "FuelTank.cpp"
#include "OilPressure.cpp"
#include "Exhaust.cpp"
#include "Display.cpp"
#include "DefaultView.cpp"
#include "GraphView.cpp"

const double inputVoltage = 10.53;
const double refVoltage = 4.096;

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
DigitalInput buttonInput(13);
Button button(&buttonInput, buttonClick);

DefaultView defaultView(&battery, &fuelTank, &oilPressure, &exhaust);
GraphView batteryGraphView("Battery", "V", 0, 15, 1, 12);
GraphView fuelGraphView("Fuel", "L", 0, 70, 10, 0);
GraphView oilPressureGraphView("Oil", "bar", 0, 5, 1, 0);
GraphView oxygenGraphView("Oxygen", "V", 0, 1, 0.1, 0.5);

byte viewIndex = 0;
Display display(&defaultView);

void setup()
{
  analogReference(EXTERNAL);
  Serial.begin(9600);
}

void loop()
{
  performanceMonitor.update();

  button.read();

  sensorVoltage.update();

  battery.update();
  batteryGraphView.addPoint(battery.getVoltage());
  Serial.print(String(battery.getVoltage()));

  Serial.print(" ");

  fuelTank.update();
  fuelGraphView.addPoint(fuelTank.getContent());
  Serial.print(String(fuelTank.getContent()));

  Serial.print(" ");

  oilPressure.setBaseVoltage(sensorVoltage.getVoltage());
  oilPressure.update();
  oilPressureGraphView.addPoint(oilPressure.getPressure());
  Serial.print(String(oilPressure.getPressure()));

  Serial.print(" ");

  exhaust.update();
  oxygenGraphView.addPoint(exhaust.getOxygenVoltage());
  Serial.print(String(exhaust.getOxygenVoltage()));

  Serial.println();

  display.update();
}

void buttonClick()
{
  if (viewIndex == 0)
  {
    display.setView(&batteryGraphView);
    viewIndex = 1;
  }
  else if (viewIndex == 1)
  {
    display.setView(&fuelGraphView);
    viewIndex = 2;
  }
  else if (viewIndex == 2)
  {
    display.setView(&oilPressureGraphView);
    viewIndex = 3;
  }
  else if (viewIndex == 3)
  {
    display.setView(&oxygenGraphView);
    viewIndex = 4;
  }
  else if (viewIndex == 4)
  {
    display.setView(&defaultView);
    viewIndex = 0;
  }
}