#ifndef Vanagon_cpp
#define Vanagon_cpp

#include <Arduino.h>
#include "Battery.cpp"
#include "FuelLevel.cpp"
#include "OilPressure.cpp"
#include "LambdaSensor.cpp"
#include "Induction.cpp"
#include "Camshaft.cpp"
#include "Tools\NTCSensor.cpp"

class Vanagon
{
  private:
  public:
    float reference;
    Battery battery;
    LambdaSensor lambdaSensor;
    Induction induction;
    NTCSensor intakeTemperature;
    NTCSensor coolantTemperature;
    OilPressure oilPressure;
    FuelLevel fuelLevel;
    Camshaft camshaft;

    Vanagon() : battery(A0),
      lambdaSensor(A1),
      induction(A2, 4),
      intakeTemperature(A3, 8250, 2041, 3545),
      coolantTemperature(A4, 8250, 2041, 3545),
      oilPressure(A5, 9, 10),
      fuelLevel(A6),
      camshaft(6)
    {
    };

    void update()
    {
      battery.voltageDivider.voltMeter.setReference(reference);
      battery.read();
      lambdaSensor.voltMeter.setReference(reference);
      lambdaSensor.read();
      induction.voltMeter.setReference(reference);
      induction.read();
      intakeTemperature.ohmMeter.voltMeter.setReference(reference);
      intakeTemperature.read();
      coolantTemperature.ohmMeter.voltMeter.setReference(reference);
      coolantTemperature.read();
      oilPressure.ohmMeter.voltMeter.setReference(reference);
      oilPressure.read();
      fuelLevel.ohmMeter.voltMeter.setReference(reference);
      fuelLevel.read();
    };
};

#endif
