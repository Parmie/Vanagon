#ifndef DefaultView_cpp
#define DefaultView_cpp

#include <Arduino.h>
#include "Display.cpp"
#include "Battery.cpp"
#include "FuelTank.cpp"
#include "OilPressure.cpp"
#include "Exhaust.cpp"

class DefaultView : public View {
  private:
    Battery *_battery;
    FuelTank *_fuelTank;
    OilPressure *_oilPressure;
    Exhaust *_exhaust;

  public:
    DefaultView(Battery *battery, FuelTank *fuelTank, OilPressure *oilPressure, Exhaust *exhaust)
    {
      _battery = battery;
      _fuelTank = fuelTank;
      _oilPressure = oilPressure;
      _exhaust = exhaust;
    };

    void draw(Display *display) override
    {
      String batteryVoltage = String(_battery->getVoltage());
      display->writeString(0, 0, "Batt");
      display->writeString(0, 5+6-batteryVoltage.length(), batteryVoltage);
      display->writeString(0, 11, "V");

      String fuelLevel = String(_fuelTank->getContent());
      display->writeString(1, 0, "Fuel");
      display->writeString(1, 5+6-fuelLevel.length(), fuelLevel);
      display->writeString(1, 11, "L");

      String oilPressure = String(_oilPressure->getPressure());
      display->writeString(2, 0, "Oil");
      display->writeString(2, 5+6-oilPressure.length(), oilPressure);
      display->writeString(2, 11, "bar");

      String oxygenVoltage = String(_exhaust->getOxygenVoltage());
      display->writeString(3, 0, "Ox");
      display->writeString(3, 5+6-oxygenVoltage.length(), oxygenVoltage);
      display->writeString(3, 11, "V");
    };
};

#endif