/*
  Released under Creative Commons Attribution 4.0
  by bitluni 2016
  https://creativecommons.org/licenses/by/4.0/
  Attribution means you can use it however you like as long you
  mention that it's base on my stuff.
  I'll be pleased if you'd do it by sharing http://youtube.com/bitlunislab
*/

#include "LedFunction.h"

const int MAX_LED_COUNT = 300;

class LedStates
{
public:
  uint8_t values[MAX_LED_COUNT][3] = {{0}};
  uint8_t values_to[MAX_LED_COUNT][3] = {{0}};
  int count = 0;
  int duration = 2000;
  long StartTime = 0;
  bool active = false;
  bool dirty = false;
  Adafruit_NeoPixel &pixels;
  LedFunction *function = 0;
  LedFunction *oldfunction = 0;

  LedStates(Adafruit_NeoPixel &ledPixels)
      : pixels(ledPixels)
  {
    count = pixels.numPixels();
  }
  void loope()
  {
    if (function)
    {
      function->render();
      if (active)
      {
        if (oldfunction)
        {
          oldfunction->render();
        }
        fader_commit();
      }
      else
      {
        commit();
      }
    }
  }
  void fader_start()
  {
    if (active)
      return;
    active = true;
    StartTime = millis();
  }
  void fader_commit()
  {
    if (!active)
      return;
    long t = millis() - StartTime;
    Serial.print("Value t ist gerade: ");
    Serial.println(t);
    if (t >= duration || t < 0 || duration == 0)
    {
      active = false;
      function->modes();
      return;
    }
    float f1 = (float)t / duration;
    float f0 = 1 - f1;
    fader_fade(long(f0 * 0x10000), long(f1 * 0x10000));
  }
  void fader_fade(long f0, long f1)
  {
    for (int i = 0; i < count; i++)
    {
      pixels.setPixelColor(i, pixels.Color((f0 * values[i][0] + f1 * values_to[i][0]) >> 16, (f0 * values[i][1] + f1 * values_to[i][1]) >> 16, (f0 * values[i][2] + f1 * values_to[i][2]) >> 16));
      //pixels.setPixelColor(i, pixels.Color(100, 100, 100));
      Serial.print(i);
      Serial.print("Werte von current: ");
      Serial.print((f0 * values[i][0]) >> 16);
      Serial.print(" ");
      Serial.print((f0 * values[i][1]) >> 16);
      Serial.print("  ");
      Serial.print((f0 * values[i][2]) >> 16);
      Serial.print("  ");
      Serial.print("Werte von target: ");
      Serial.print((f1 * values_to[i][0]) >> 16);
      Serial.print(" ");
      Serial.print((f1 * values_to[i][1]) >> 16);
      Serial.print("  ");
      Serial.println((f1 * values_to[i][2]) >> 16);
    }
    pixels.show();
  }

  void setFunction(LedFunction *newFunction)
  {
    uint8_t rgb[3] = {0, 0, 0};
    if (oldfunction)
      delete oldfunction;
    if (function)
    {
      Serial.println("oldfunction gesetzt");
      oldfunction = function;
    }
    function = newFunction;
    if (!function)
      return;

    function->state = this;
    //Serial.println(oldfunction->a);

    Serial.println("2");
  }

  void setRgb(int i, uint8_t r, uint8_t g, uint8_t b, bool mode)
  {
    if (mode)
    {
      values[i][0] = r;
      values[i][1] = g;
      values[i][2] = b;
      dirty = true;
    }
    else
    {
      values_to[i][0] = r;
      values_to[i][1] = g;
      values_to[i][2] = b;
    }
  }

  virtual void render()
  {
    if (function)
      function->render();
  }

  void commit()
  {
    for (int i = 0; i < count; i++)
    {
      pixels.setPixelColor(i, pixels.Color(values[i][0], values[i][1], values[i][2]));
      /*
          Serial.print(i);
          Serial.print(" Rot ist ");
          Serial.print(values[i][0]);
          Serial.print(" Grün ist " );
          Serial.print(values[i][1]);
          Serial.print(" Blau ist ");
          Serial.println(values[i][2]);
        */
    }
    pixels.show();
  }
};
