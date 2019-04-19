#ifndef Display_cpp
#define Display_cpp

#include <Arduino.h>
#include <gfxfont.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define RST 12
#define CE 11
#define DC 10
#define DIN 9
#define CLK 8

class Display;

class View {
  public:
    virtual void draw(Display *display);
};

class Display {
  private:
    Adafruit_PCD8544 _display = Adafruit_PCD8544(CLK, DIN, DC, CE, RST);
    bool _initialized = false;

  public:
    void update(View *view)
    {
      if (!_initialized)
      {
        _display.begin();
        _initialized = true;
      }

      _display.setContrast(55);
      _display.clearDisplay();
      view->draw(this);
      _display.display();
    };

    void writeCharacter(uint8_t line, uint8_t pos, char c)
    {
      _display.drawChar(pos * 6, line * 10, c, 1, 0, 1);
    };

    void writeString(uint8_t line, uint8_t pos, String text)
    {
      for (uint8_t i = 0; i < text.length(); i++)
      {
        writeCharacter(line, pos + i, text[i]);
      }
    };

    void drawPixel(unsigned int x, unsigned int y)
    {
      _display.drawPixel(x, y, BLACK);
    };
};

#endif
