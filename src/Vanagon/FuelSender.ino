int fuelDeviderResistance = 330;

double readFuelSender()
{
  int senderValue = analogRead(in_fuelLevel);
  double voltage = map(senderValue, 0, 1023, 0, 500) / 100.0;
  double resistance = (voltage*fuelDeviderResistance)/(inputVoltage-voltage);
  double fuelLevel = fuelResistanceToLiters(resistance);

  return fuelLevel;
}

double fuelResistanceToLiters(double resistance)
{
  return (4.794908061*pow(10,-4)*pow(resistance, 2))-(4.726976404*pow(10,-1)*resistance)+99.48112787;
  //return -(pow(5, 3/2)*sqrt(340080*resistance-2263567)-115625)/4251;
}
