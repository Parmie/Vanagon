int batteryPin = A0;

double readBatteryLevel()
{
  int senderValue = analogRead(batteryPin);
  double batteryLevel = map(senderValue, 0, 1023, 0, 1500) / 100.0;
  return batteryLevel;
}
