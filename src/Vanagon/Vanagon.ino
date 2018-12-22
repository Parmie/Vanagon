double inputVoltage = 10.53;

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
  Serial.print("Battery: " + String(batteryLevel) + " V     ");
  Serial.print("Fuel: " + String(fuelLevel) + " L       ");
  Serial.println("Oil: " + String(oilPressure) + " bar");
  drawDisplay(batteryLevel, fuelLevel, oilPressure);
}

// note: the _in array should have increasing values
int multiMap(int val, int* _in, int* _out, uint8_t size)
{
  // take care the value is within range
  // val = constrain(val, _in[0], _in[size-1]);
  if (val <= _in[0]) return _out[0];
  if (val >= _in[size-1]) return _out[size-1];

  // search right interval
  uint8_t pos = 1;  // _in[0] allready tested
  while(val > _in[pos]) pos++;

  // this will handle all exact "points" in the _in array
  if (val == _in[pos]) return _out[pos];

  // interpolate in the right segment for the rest
  return (val - _in[pos-1]) * (_out[pos] - _out[pos-1]) / (_in[pos] - _in[pos-1]) + _out[pos-1];
}
