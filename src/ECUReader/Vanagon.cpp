#ifndef Vanagon_cpp
#define Vanagon_cpp

#include <Arduino.h>
#include "Battery.cpp"
#include "FuelLevel.cpp"
#include "OilPressure.cpp"
#include "LambdaSensor.cpp"
#include "AirFlowMeter.cpp"
#include "Injection.cpp"
#include "Tools\NTCSensor.cpp"

class Vanagon
{
private:
public:
  VoltageDivider sensorReference;
  Battery battery;
  FuelLevel fuelLevel;
  OilPressure oilPressure;
  LambdaSensor lambdaSensor;
  AirFlowMeter airFlowMeter;
  Injection injection;
  NTCSensor intakeTemperature;
  NTCSensor coolantTemperature;

  Vanagon() : sensorReference(A7, 148.6, 148.3),
              battery(A0),
              fuelLevel(A5),
              oilPressure(A6),
              lambdaSensor(A1),
              airFlowMeter(A2),
              injection(6),
              intakeTemperature(A3, 8250, 2041, 3545),
              coolantTemperature(A4, 8250, 2041, 3545)
  {
    intakeTemperature.ohmMeter.setBaseVoltage(5);
    coolantTemperature.ohmMeter.setBaseVoltage(5);
  };

  void update()
  {
    sensorReference.read();

    battery.read();

    fuelLevel.ohmMeter.setBaseVoltage(sensorReference.getVoltage());
    oilPressure.ohmMeter.setBaseVoltage(sensorReference.getVoltage());
    fuelLevel.read();
    oilPressure.read();
    lambdaSensor.read();
    airFlowMeter.read();
    //_injection.read();
    intakeTemperature.read();
    coolantTemperature.read();
  };
};

#endif