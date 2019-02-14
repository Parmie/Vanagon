#ifndef Button_cpp
#define Button_cpp

#include <Arduino.h>
#include "..\Arduino\DigitalInput.cpp"

class Button {
  private:
    DigitalInput *_input;
    void (*_clickHandler)();

  public:
    Button(DigitalInput *input, void (*clickHandler)())
    {
      _input = input;
      _clickHandler = clickHandler;
    };

    void read()
    {
      _input->read();
      if (_input->getRising())
      {
        _clickHandler();
      }
    };
};

#endif