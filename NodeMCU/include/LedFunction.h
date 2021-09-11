/*
  Released under Creative Commons Attribution 4.0
  by bitluni 2016
  https://creativecommons.org/licenses/by/4.0/
  Attribution means you can use it however you like as long you
  mention that it's base on my stuff.
  I'll be pleased if you'd do it by sharing http://youtube.com/bitlunislab
*/

#ifndef LED_FUNCTION_H

#define LED_FUNCTION_H

const char *rgbNames[] = {"r", "g", "b"};

class LedStates;
class LedFunction
{
  public:
    int a = 3;
    bool mode = false;
    bool set;
    uint8_t rgb_s[3] = {0, 0, 0};
    LedStates *state;
    LedFunction()
    {
    }
    virtual ~LedFunction () {}
    virtual void modes() = 0;
    virtual void init() = 0;
    void getRGB (uint8_t r, uint8_t g, uint8_t b) {
      rgb_s[0] = r;
      rgb_s[1] = g;
      rgb_s[2] = b;
    }
    void loadRGB(uint8_t *rgb) {
      rgb[0] = rgb_s[0];
      rgb[1] = rgb_s[1];
      rgb[2] = rgb_s[2];
      return;
    }


    bool loadRGBValues(uint8_t *rgb)
    {
      for (int i = 0; i < 3; i++)
        rgb[i] = 100;
      return true;
    }

    virtual void render() = 0;
};

#endif
