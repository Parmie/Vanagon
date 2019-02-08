double readOxygen(int pin)
{
  int senderValue = analogRead(pin);
  double voltage = map(senderValue, 213, 858, 100, 400) / 100.0;
  return voltage;
}
