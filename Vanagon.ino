#include <gfxfont.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define RST 12
#define CE 11
#define DC 10
#define DIN 9
#define CLK 8

Adafruit_PCD8544 display = Adafruit_PCD8544(CLK, DIN, DC, CE, RST);

void setup()
{
	display.begin(55); // Contrast 55 seems to be the best for Nokia 5110
	display.clearDisplay();
	writeString(0, 0, "RPM:");
	writeString(0, 7, "2800");
	writeString(1, 0, "Temp:");
	writeString(1, 7, "89 C");
	writeString(2, 0, "Speed:");
	writeString(2, 7, "72 kmh");
	writeString(3, 0, "Fuel:");
	writeString(3, 7, "34 %");
	display.display();
}

void loop()
{
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