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
  AnalogInput batteryInput;
  AnalogInput fuelSenderInput;
  AnalogInput oilPressureInput;
  AnalogInput oxygenSensorInput;
  PulseInput hallSensorInput;
  AnalogInput airTemperatureInput;
  AnalogInput airFlowInput;

public:
  Battery *battery;
  FuelTank *fuelTank;
  OilPressure *oilPressure;
  Exhaust *exhaust;
  Induction *induction;
  Injection *injection;

  Vanagon() : batteryInput(A0),
              fuelSenderInput(A5),
              oilPressureInput(A6),
              oxygenSensorInput(A1),
              hallSensorInput(6),
              airTemperatureInput(A3),
              airFlowInput(A2)
  {
    battery = new Battery(&batteryInput);
    fuelTank = new FuelTank(&fuelSenderInput);
    oilPressure = new OilPressure(&oilPressureInput);
    exhaust = new Exhaust(&oxygenSensorInput);
    injection = new Injection(&hallSensorInput);
    induction = new Induction(&airTemperatureInput, &airFlowInput);
  };

  void setSensorVoltage(float voltage)
  {
    fuelTank->setBaseVoltage(voltage);
    oilPressure->setBaseVoltage(voltage);
  };

  void update()
  {
    battery->update();
    fuelTank->update();
    oilPressure->update();
    exhaust->update();
    induction->update();
    //_injection->update();
  };
};

#endif