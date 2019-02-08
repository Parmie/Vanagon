double readBatteryLevel()
{
  int senderValue = analogRead(in_battery);
  //double voltage = senderValue * 5.01 / 1024;
  double batteryVoltage = map(senderValue, 643, 966, 1000, 1500) / 100.0;
  return batteryVoltage;
}
