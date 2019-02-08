int oilPressureDeviderResistance = 220;
int oilPressureMapIn[] = {11, 29, 47, 65, 82, 100, 117, 134, 151, 167, 184};
int oilPressureMapOut[] = {0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0};

double readOilPressure()
{
  int senderValue = analogRead(in_oilPressure);
  double voltage = map(senderValue, 0, 1023, 0, 500) / 100.0;
  double resistance = (voltage*oilPressureDeviderResistance)/(inputVoltage-voltage);
  double bars = oilPressureResistanceToBars(resistance);

  return bars;
}

double oilPressureResistanceToBars(double resistance)
{
  //return multiMap(resistance, oilPressureMapIn, oilPressureMapOut, 11);
  return -(sqrt(5)*sqrt(6726892997-7364000*resistance)-182325)/3682;
}
