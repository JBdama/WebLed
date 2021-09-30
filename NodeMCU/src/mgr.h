#include <ArduinoJson.h>
#include "LedFunction.h"
#include "waveFunction.h"
#include "SimpleFunction.h"
#include "G_Simple.h"

//#include "LedStates.h"
class mgr
{
public:
    bool power = true;
    uint8_t rgb[3] = {0, 0, 0};
    uint8_t b = 100;
    uint8_t m = 1;
    LedStates &states;
    mgr(LedStates &l) : states(l)
    {
    }
    void setup_mgr() {
        SimpleFunction *f = new SimpleFunction;
        f->getRGB(0, 0, 0);
        f->init();
        SimpleFunction *g = new SimpleFunction;
        g->getRGB(0, 0, 0);
        g->init();
        states.setFunction(f);
        states.setFunction(g);
        states.fader_start();
    }
    void initLeds(LedFunction *f)
    {
        f->getRGB(rgb[0], rgb[1], rgb[2]);
        f->init();
        states.setFunction(f);
        states.fader_start();
    }
    void updateLeds()
    {
        if (m == 0)
        {
            SimpleFunction *f = new SimpleFunction;
            initLeds(f);
        }
        else if (m == 1)
        {
            waveFunction *f = new waveFunction;
            initLeds(f);
        } else if (m == 2) {
            G_Simple *f = new G_Simple;   
            initLeds(f);
        }
    }
    void fade_power(bool state)
    {
        if (state)             //fade from 0 to 1
        {
            updateLeds();
        }
        else            //frade from 1 to 0
        {
            SimpleFunction *f = new SimpleFunction;
            f->getRGB(0, 0, 0);
            f->init();
            states.setFunction(f);
            states.fader_start();
        }
    }
};