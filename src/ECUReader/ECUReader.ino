#include "Arduino\PerformanceMonitor.cpp"
#include "Vanagon.cpp"
#include "Console.cpp"

PerformanceMonitor performanceMonitor;

Vanagon vanagon;
Console console(&vanagon, &performanceMonitor);

void setup()
{
  // Using internal 5V as reference.
  // Don't provide USB power! It's unstable and ruins our reference.
  analogReference(DEFAULT);
  console.init(9600);
}

void loop()
{
  float pin7 = analogRead(A7);
  vanagon.reference = 1024 * (4.096 / pin7);
  //voltage = value * (reference / 1024)
  //4.096 = pin7 * (reference / 1024)
  //4.096 / pin7 = reference / 1024
  //(4.096 / pin7) * 1024 = reference
  //vanagon.reference = 5.04;

  performanceMonitor.update();
  vanagon.update();
  console.update();
}