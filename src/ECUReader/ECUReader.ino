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
  console.init(115200);
}

void loop()
{
  performanceMonitor.update();
  vanagon.update();
  console.update();
}