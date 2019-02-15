#ifndef ListView_cpp
#define ListView_cpp

#include <Arduino.h>
#include "Tools\Display.cpp"

struct ListItem
{
  String title;
  String unit;
  float value;
};

class ListView : public View
{
  private:
    ListItem _items[5];

  public:
    void configure(byte index, String title, String unit)
    {
      _items[index].title = title;
      _items[index].unit = unit;
    }

    void setValue(byte index, float value)
    {
      _items[index].value = value;
    }

    void draw(Display *display) override
    {
      for (int i = 0; i < 5; i++)
      {
        if (_items[i].title.length() > 0)
        {
          display->writeString(i, 0, _items[i].title);
          String value = String(_items[i].value);
          display->writeString(i, 5+6-value.length(), value);
          display->writeString(i, 11, _items[i].unit);
        }
      }
    };
};

#endif