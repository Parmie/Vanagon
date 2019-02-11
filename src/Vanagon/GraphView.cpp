#ifndef GraphView_cpp
#define GraphView_cpp

#include <Arduino.h>
#include "Display.cpp"

class GraphView : public View {
  private:
    String _title;
    byte _points[84];
    byte _firstPoint = 0;

  public:
    GraphView(String title)
    {
      _title = title;
    };

    void addPoint(byte value)
    {
      _points[_firstPoint] = value;
      _firstPoint++;
      if (_firstPoint == 84)
      {
        _firstPoint = 0;
      }
    };

    void draw(Display *display) override
    {
      display->writeString(0, 0, _title);
      for (byte x=0; x < 84; x++)
      {
        display->drawPixel(x, 9);
      }

      for (byte i=0; i < 84; i++)
      {
        byte index = _firstPoint+i;
        if (index > 83)
        {
          index = index - 84;
        }
        display->drawPixel(i, 47 - _points[i]);
      }
    };
};

#endif