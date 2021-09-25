/*
  Released under Creative Commons Attribution 4.0
  by bitluni 2016
  https://creativecommons.org/licenses/by/4.0/
  Attribution means you can use it however you like as long you
  mention that it's base on my stuff.
  I'll be pleased if you'd do it by sharing http://youtube.com/bitlunislab
*/

#include "LedFunction.h"

const int MAX_LED_COUNT = 201;

class LedStates
{
public:
  uint8_t values[MAX_LED_COUNT][3] = {{0}};
  uint8_t values_to[MAX_LED_COUNT][3] = {{0}};
  uint8_t rf, gf, bf; //
  uint8_t fRgb[3] = {0, 0, 0};
  int count = 0;
  float brs = 0;
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
    pixels.begin();
  }
  void set_brs(uint8_t b)
  {
    brs = (float)b / (float)255;
  }
  void loope()
  {
    function->render();
    if (active)
    {

      oldfunction->render();

      fader_commit();
    }
    else
    {
      commit();
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
  void setPixels(long f1 = 1, long f0 = 1)
  {
    for (int i = 0; i < count; i++)
    {
      if (!active)
      {
        fRgb[0] = values[i][0] * brs;
        fRgb[1] = values[i][1] * brs;
        fRgb[2] = values[i][2] * brs;
      }
      else
      {
        fRgb[0] = ((f0 * values[i][0] + f1 * values_to[i][0]) >> 16) * brs;
        fRgb[1] = ((f0 * values[i][1] + f1 * values_to[i][1]) >> 16) * brs;
        fRgb[2] = ((f0 * values[i][2] + f1 * values_to[i][2]) >> 16) * brs;
      }
      for (int j = 0; j < 3; j++)
      {
      }
    }
  }
  void fader_fade(long f0, long f1)
  {
    for (int i = 0; i < count; i++)
    {
      pixels.setPixelColor(i, pixels.Color(((f0 * values[i][0] + f1 * values_to[i][0]) >> 16) * brs, ((f0 * values[i][1] + f1 * values_to[i][1]) >> 16) * brs, ((f0 * values[i][2] + f1 * values_to[i][2]) >> 16) * brs));
      /*
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
      */
    }
    pixels.show();
  }
  void commit()
  {
    for (int i = 0; i < count; i++)
    {
      pixels.setPixelColor(i, pixels.Color(values[i][0]*brs, values[i][1]*brs, values[i][2]*brs));
      /*
          Serial.print(i);
          Serial.print(" Rot ist ");
          Serial.print(values[i][0]*brs);
          Serial.print(" Grün ist " );
          Serial.print(values[i][1]*brs);
          Serial.print(" Blau ist ");
          Serial.println(values[i][2]*brs);
        */
    }
    pixels.show();
  }
  void setFunction(LedFunction *newFunction)
  {
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
};
