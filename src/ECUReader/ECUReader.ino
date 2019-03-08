//#include "Arduino\PerformanceMonitor.cpp"
#include "Arduino\AnalogInput.cpp"
#include "Arduino\DigitalInput.cpp"
//#include "Tools\Button.cpp"
//#include "Tools\PulseInput.cpp"
#include "Vanagon.cpp"
#include "Battery.cpp"
#include "FuelTank.cpp"
#include "OilPressure.cpp"
#include "Exhaust.cpp"
#include "Induction.cpp"
#include "Injection.cpp"
#include "Visualization.cpp"

const int in_airFlow = A2;
const int in_airTemperature = A3;
const int in_coolantTemperature = A4;
const int in_fuelLevel = A5;
const int in_starter = 2;
const int in_hallSender = 3;
const int in_diagnostics = 4;
const int in_throttleSwitch = 5;
const int in_ignition = 7;

//PerformanceMonitor performanceMonitor;

AnalogInput sensorVoltageInput(A7);
VoltageMeter sensorVoltage(&sensorVoltageInput, {148.6, 148.3});

Vanagon *vanagon;

Visualization *visualization;

void setup()
{
  analogReference(EXTERNAL);
  Serial.begin(9600);

  vanagon = new Vanagon();

  visualization = new Visualization(vanagon);
}

void loop()
{
  // Reading all inputs
  //performanceMonitor.update();
  sensorVoltage.update();

  vanagon->setSensorVoltage(sensorVoltage.getVoltage());
  vanagon->update();

  visualization->update();

  Serial.print(String(vanagon->battery->getVoltage()));
  Serial.print(" ");
  Serial.print(String(vanagon->fuelTank->getResistance()));
  Serial.print(" ");
  Serial.print(String(vanagon->oilPressure->getResistance()));
  Serial.print(" ");
  Serial.print(String(vanagon->exhaust->getOxygenVoltage()));
  Serial.print(" ");
  Serial.print(String(vanagon->injection->getRevolutions()));
  Serial.print(" ");
  Serial.print(String(visualization->viewIndex));
  /*
  Serial.print(" ");
  Serial.print(String(pulseInput.getStart()));
  Serial.print(" ");
  Serial.print(String(pulseInput.getStop()));
  Serial.print(" ");
  Serial.print(String(pulseInput.getPulseLength()));
  Serial.print(" ");
  Serial.print(String(pulseInput.getPulseWidth()));
  Serial.print(" ");
  Serial.print(String(pulseInput.getPulsesPerMinute()));
  Serial.print(" ");
  Serial.print(String(pulseInput.getPulseCount()));*/
  Serial.println();
  /*
  unsigned long pulse = pulseIn(6, HIGH);
  Serial.print(String(pulse));
  Serial.println();
*/
}
