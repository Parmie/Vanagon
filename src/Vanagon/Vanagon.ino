const double inputVoltage = 10.53;
const double refVoltage = 4.096;

const int in_battery = A0;
const int in_oxygen = A1;
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

void setup()
{
  //analogReference(EXTERNAL);
  Serial.begin(9600);
  initDisplay();
}

void loop()
{
  double batteryLevel = readBatteryLevel();
  double fuelLevel = readFuelSender();
  double oilPressure = readOilPressure();
  double oxygenLevel = readOxygen(in_oxygen);
  Serial.print("Battery: " + String(batteryLevel) + " V     ");
  Serial.print("Fuel: " + String(fuelLevel) + " L     ");
  Serial.print("Oil: " + String(oilPressure) + " bar     ");
  Serial.println("Ox: " + String(oxygenLevel) + " V");
  drawDisplay(batteryLevel, fuelLevel, oilPressure, oxygenLevel);
}