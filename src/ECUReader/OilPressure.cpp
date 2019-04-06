#ifndef OilPressure_cpp
#define OilPressure_cpp

#include <Arduino.h>
#include "Arduino\AnalogInput.cpp"
#include "Arduino\DigitalInput.cpp"
#include "Tools\OhmMeter.cpp"

class OilPressure
{
private:
public:
  OhmMeter ohmMeter;
  DigitalInput warningLowInput;
  DigitalInput warningHighInput;

  float getPressure()
  {
    return -(sqrt(5) * sqrt(6726892997 - 7364000 * ohmMeter.getResistance()) - 182325) / 3682;
  };

  bool getLowPressure()
  {
    return warningLowInput.getState();
  };

  bool getHighPressure()
  {
    return warningHighInput.getState();
  };

  OilPressure(byte senderPin, byte warningLowPin, byte warningHighPin) : ohmMeter(senderPin, 47),
                                                                         warningLowInput(warningLowPin, 0),
                                                                         warningHighInput(warningHighPin, 0){

                                                                         };

  void read()
  {
    ohmMeter.read();
    warningLowInput.read();
    warningHighInput.read();
  };
};

#endif