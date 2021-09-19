/*
  Released under Creative Commons Attribution 4.0
  by bitluni 2016
  https://creativecommons.org/licenses/by/4.0/
  Attribution means you can use it however you like as long you
  mention that it's base on my stuff.
  I'll be pleased if you'd do it by sharing http://youtube.com/bitlunislab
*/

#include "LedFunction.h"
#include <math.h>
class SimpleFunction_2: public LedFunction
{
  public:
    int a = 5;
    long sinTab[256];
    uint8_t rgb[3] = {100, 0, 0};
    int start;
    bool set = false;
    bool mode = false;

    SimpleFunction_2()
    {
      for (int i = 0; i < 256; i++)
        sinTab[i] = sin(3.1415 / 128 * i) * 0x7fff + 0x8000;
      start = millis();
    }
    virtual void modes( ) {
      mode = true;
      set = false;
    }
    virtual void init() {
      loadRGB(rgb);
      return;
    }

    virtual void render()
    {
      delay(10);
      int j = ((millis() - start) / 63) & 255;
      int k = ((millis() - start) / 71) & 255;
      for (int i = 0; i < state->count; i++)
      {
        long s = (sinTab[(i * 3 + j) & 255] >> 8) * (sinTab[-(i * 4 + k) & 255] >> 8);
        state->setRgb(i, (rgb[0] * s) >> 16, (rgb[1] * s) >> 16, (rgb[2] * s) >> 16, mode);
      }
    }
};
