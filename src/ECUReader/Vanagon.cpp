#ifndef Vanagon_cpp
#define Vanagon_cpp

#include <Arduino.h>
#include "Battery.cpp"
#include "FuelTank.cpp"
#include "OilPressure.cpp"
#include "Exhaust.cpp"
#include "Induction.cpp"
#include "Injection.cpp"

class Vanagon
{
private:
public:
  VoltageDivider sensorReference;
  Battery battery;
  FuelTank fuelTank;
  OilPressure oilPressure;
  Exhaust exhaust;
  Induction induction;
  Injection injection;

  Vanagon() : sensorReference(A7, 148.6, 148.3),
              battery(A0),
              fuelTank(A5),
              oilPressure(A6),
              exhaust(A1),
              induction(A3, A2),
              injection(6){

              };

  void update()
  {
    sensorReference.read();

    battery.read();

    fuelTank.ohmMeter.setBaseVoltage(sensorReference.getVoltage());
    oilPressure.ohmMeter.setBaseVoltage(sensorReference.getVoltage());
    fuelTank.read();
    oilPressure.read();
    exhaust.read();
    induction.read();
    //_injection.read();
  };
};

#endif