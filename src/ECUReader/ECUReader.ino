#include "Arduino\PerformanceMonitor.cpp"
#include "Arduino\AnalogInput.cpp"
#include "Arduino\DigitalInput.cpp"
#include "Vanagon.cpp"
#include "Battery.cpp"
#include "FuelTank.cpp"
#include "OilPressure.cpp"
#include "Exhaust.cpp"
#include "Induction.cpp"
#include "Injection.cpp"
#include "Console.cpp"

const int in_airFlow = A2;
const int in_airTemperature = A3;
const int in_coolantTemperature = A4;
const int in_fuelLevel = A5;
const int in_starter = 2;
const int in_hallSender = 3;
const int in_diagnostics = 4;
const int in_throttleSwitch = 5;
const int in_ignition = 7;

PerformanceMonitor performanceMonitor;

AnalogInput sensorVoltageInput(A7);
VoltageMeter sensorVoltage(&sensorVoltageInput, {148.6, 148.3});

Vanagon *vanagon;
Console *console;

void setup()
{
  analogReference(EXTERNAL);

  vanagon = new Vanagon();
  console = new Console(115200);
}

void loop()
{
  // Reading all inputs
  performanceMonitor.update();
  sensorVoltage.update();

  vanagon->setSensorVoltage(sensorVoltage.getVoltage());
  vanagon->update();

  console->sendText(vanagon, &performanceMonitor);
}