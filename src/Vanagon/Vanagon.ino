#include "Arduino\PerformanceMonitor.cpp"
#include "Arduino\AnalogInput.cpp"
#include "Arduino\DigitalInput.cpp"
#include "Tools\Button.cpp"
#include "Battery.cpp"
#include "FuelTank.cpp"
#include "OilPressure.cpp"
#include "Exhaust.cpp"
#include "Tools\Display.cpp"
#include "DefaultView.cpp"
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

GraphView batteryGraphView("Battery", "V", 0, 15, 1, 12);
GraphView fuelGraphView("Fuel", "L", 0, 70, 10, 0);
GraphView oilPressureGraphView("Oil", "bar", 0, 5, 1, 0);
GraphView oxygenGraphView("Oxygen", "V", 0, 1, 0.1, 0.5);

ListView listView1;
ListView listView2;

View *views[] = {
  &listView1,
  &batteryGraphView,
  &fuelGraphView,
  &oilPressureGraphView,
  &oxygenGraphView
};

byte viewIndex = 0;
Display display(views[0]);

void setup()
{
  analogReference(EXTERNAL);
  Serial.begin(9600);
  buttonInput.attachInterrupt();

  listView1.configure(0, "Batt", "V");
  listView1.configure(1, "Fuel", "L");
  listView1.configure(2, "Oil", "bar");
  listView1.configure(3, "Oxygen", "V");
  listView1.configure(4, "Button", "");
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

  fuelTank.setBaseVoltage(sensorVoltage.getVoltage());
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

  listView1.setValue(0, battery.getVoltage());
  listView1.setValue(1, fuelTank.getContent());
  listView1.setValue(2, oilPressure.getPressure());
  listView1.setValue(3, exhaust.getOxygenVoltage());
  listView1.setValue(4, INTERRUPTS);

  display.update();
}

void buttonClick()
{
  if (viewIndex++ >= sizeof(views))
  {
    viewIndex = 0;
  }

  display.setView(views[viewIndex]);

}