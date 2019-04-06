#ifndef Vanagon_cpp
#define Vanagon_cpp

#include <Arduino.h>
#include "Battery.cpp"
#include "FuelLevel.cpp"
#include "OilPressure.cpp"
#include "LambdaSensor.cpp"
#include "AirFlowMeter.cpp"
#include "Tools\NTCSensor.cpp"

class Vanagon
{
private:
public:
  Battery battery;
  LambdaSensor lambdaSensor;
  AirFlowMeter airFlowMeter;
  NTCSensor intakeTemperature;
  NTCSensor coolantTemperature;
  OilPressure oilPressure;
  FuelLevel fuelLevel;

  Vanagon() : battery(A0),
              lambdaSensor(A1),
              airFlowMeter(A2),
              intakeTemperature(A3, 8250, 2041, 3545),
              coolantTemperature(A4, 8250, 2041, 3545),
              oilPressure(A5, 9, 10),
              fuelLevel(A6)
  {
  };

  void update()
  {
    battery.read();
    lambdaSensor.read();
    airFlowMeter.read();
    intakeTemperature.read();
    coolantTemperature.read();
    oilPressure.read();
    fuelLevel.read();
  };
};

#endif