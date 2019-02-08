#include <gfxfont.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define RST 12
#define CE 11
#define DC 10
#define DIN 9
#define CLK 8

Adafruit_PCD8544 display = Adafruit_PCD8544(CLK, DIN, DC, CE, RST);

void initDisplay()
{
  display.begin();
}

void drawDisplay(float batteryLevel, float fuelLevel, float oilPressure, float mixture)
{
  display.setContrast(55);
  display.clearDisplay();
  writeString(0, 0, "Batt");
  writeString(0, 5, String(batteryLevel) + " V");
  writeString(1, 0, "Fuel");
  writeString(1, 5, String(fuelLevel) + " L");
  writeString(2, 0, "Oil");
  writeString(2, 5, String(oilPressure) + " bar");
  writeString(3, 0, "Oxygen");
  writeString(3, 7, String(mixture) + " V");
  display.display();
}

void writeCharacter(uint8_t line, uint8_t pos, char c)
{
 display.drawChar(pos * 6, line * 10, c, 1, 0, 1);
}

void writeString(uint8_t line, uint8_t pos, String text)
{
  for (uint8_t i = 0; i < text.length(); i++)
  {
    writeCharacter(line, pos + i, text[i]);
  }
}
