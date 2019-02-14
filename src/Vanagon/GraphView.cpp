#ifndef GraphView_cpp
#define GraphView_cpp

#include <Arduino.h>
#include "Tools\Display.cpp"

#define GRAPH_LENGTH 82
#define GRAPH_HIGHT 38

class GraphView : public View {
  private:
    String _title;
    String _unit;
    float _min;
    float _max;
    float _step1;
    float _step2;
    byte _points[GRAPH_LENGTH];
    byte _firstPoint = 0;
    float _currentValue;

  public:
    GraphView(String title, String unit, float min = 0, float max = GRAPH_HIGHT, float step1 = 0, float step2 = 0)
    {
      _title = title;
      _unit = unit;
      _min = min;
      _max = max;
      _step1 = step1;
      _step2 = step2;
    };

    void addPoint(float value)
    {
      _currentValue = value;
      _points[_firstPoint] = (value - _min) * GRAPH_HIGHT / _max;
      _firstPoint++;
      if (_firstPoint == GRAPH_LENGTH)
      {
        _firstPoint = 0;
      }
    };

    void draw(Display *display) override
    {
      display->writeString(0, 0, _title);
      String valueText = String(_currentValue);
      display->writeString(0, 14-_unit.length()-valueText.length(), valueText);
      display->writeString(0, 14-_unit.length(), _unit);

      if (_step1 > 0)
      {
        for (float i = _min; i <= _max; i = i + _step1)
        {
          byte value = (i - _min) * GRAPH_HIGHT / _max;
          display->drawPixel(0, 47 - value);
        }
      }

      if (_step2 > 0)
      {
        for (float i = _min; i <= _max; i = i + _step2)
        {
          byte value = (i - _min) * GRAPH_HIGHT / _max;
          display->drawPixel(0, 47 - value);
          display->drawPixel(1, 47 - value);
        }
      }

      for (byte i=0; i < GRAPH_LENGTH; i++)
      {
        byte index = _firstPoint+i;
        if (index >= GRAPH_HIGHT)
        {
          index = index - GRAPH_HIGHT;
        }
        byte value = _points[i];
        if (value >= 0 && value <= GRAPH_HIGHT)
        {
          display->drawPixel(2+i, 47 - _points[i]);
        }
      }
    };
};

#endif