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
	writeLine(0, 0, "Ready");
	display.display();
}

void loop()
{
}

void drawCharacter(uint8_t line, uint8_t pos, char c)
{
	display.drawChar(pos * 6, line * 10, c, 1, 0, 1);
}

void writeLine(uint8_t line, uint8_t pos, String text)
{
	for (uint8_t i = 0; i < text.length(); i++)
	{
		drawCharacter(line, pos + i, text[i]);
	}
}