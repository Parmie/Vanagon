#ifndef Button_cpp
#define Button_cpp

#include <Arduino.h>
#include "..\Arduino\DigitalInput.cpp"

class Button {
  private:
    DigitalInput *_input;
    void (*_clickHandler)(void*);
    void *_clickHandlerData;
    typedef void (*callback)(void*);

  public:
    template<typename T>
    Button(DigitalInput *input, void (*clickHandler)(T*), T *userData)
    {
      _input = input;
      _clickHandler = (callback)clickHandler;
      _clickHandlerData = (void*)userData;
    };

    void read()
    {
      _input->read();
      if (_input->getRising())
      {
        _clickHandler(_clickHandlerData);
      }
    };
};

#endif