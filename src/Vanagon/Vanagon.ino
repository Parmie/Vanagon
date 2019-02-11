#include "AnalogInput.cpp"
#include "DigitalInput.cpp"
#include "Button.cpp"
#include "Battery.cpp"
#include "FuelTank.cpp"
#include "Exhaust.cpp"
#include "Display.cpp"
#include "DefaultView.cpp"

const double inputVoltage = 10.53;
const double refVoltage = 4.096;

const int in_airFlow = A2;
const int in_airTemperature = A3;
const int in_coolantTemperature = A4;
const int in_fuelLevel = A5;
const int in_oilPressure = A6;
const int in_starter = 2;
const int in_hallSender = 3;
const int in_diagnostics = 4;
const int in_throttleSwitch = 5;
const int in_injectors = 6;
const int in_ignition = 7;

AnalogInput batteryInput(A0);
Battery battery(&batteryInput);

AnalogInput fuelSenderInput(A5);
FuelTank fuelTank(&fuelSenderInput);

AnalogInput oxygenSensorInput(A1);
Exhaust exhaust(&oxygenSensorInput);

extern void buttonClick();
DigitalInput buttonInput(13);
Button button(&buttonInput, buttonClick);

DefaultView defaultView(&battery, &fuelTank, &exhaust);
Display display(&defaultView);

void setup()
{
  analogReference(EXTERNAL);
  Serial.begin(9600);

  batteryInput.setDivider(216.3, 98.8);
}

void loop()
{
  button.read();

  battery.update();
  Serial.print(String(battery.getVoltage()));

  Serial.print(" ");

  fuelTank.update();
  Serial.print(String(fuelTank.getContent()));

  Serial.print(" ");

  exhaust.update();
  Serial.print(String(exhaust.getOxygenVoltage()));

  Serial.println();
  
  display.update();
}

void buttonClick()
{
}