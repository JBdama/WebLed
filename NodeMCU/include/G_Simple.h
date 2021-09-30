/*
  Released under Creative Commons Attribution 4.0
  by bitluni 2016
  https://creativecommons.org/licenses/by/4.0/
  Attribution means you can use it however you like as long you
  mention that it's base on my stuff.
  I'll be pleased if you'd do it by sharing http://youtube.com/bitlunislab
*/

#include "LedFunction.h"

class G_Simple : public LedFunction
{
public:
  int a = 4;
  uint8_t rgb[3] = {0, 0, 0};
  bool set = false;
  bool mode = false;

  G_Simple()
  {
  }
  virtual void modes()
  {
    mode = true;
    set = false;
  }
  virtual void init()
  {
    loadRGB(rgb);
    return;
  }
  virtual void render()
  {
    state->loadRGB2(rgb);

    for (int i = 0; i < state->count; i++)
      state->setRgb(i, rgb[0], rgb[1], rgb[2], mode);
    set = true;
  }
};
