#include <ArduinoJson.h>
#include "LedFunction.h"
#include "SimpleFunction_2.h"
#include "SimpleFunction.h"

//#include "LedStates.h"
class mgr
{
public:
    uint8_t rgb[3] = {0, 0, 0};
    uint8_t b = 100;
    uint8_t m = 1;
    LedStates &states;
    mgr(LedStates &l) : states(l)
    {
    }
    void initLeds(LedFunction *f)
    {
        f->getRGB(rgb[0], rgb[1], rgb[2]);
        f->init();
        states.setFunction(f);
        states.fader_start();
    }
    void setLeds()
    {
        if (m == 0)
        {
            SimpleFunction *f = new SimpleFunction;
            initLeds(f);
        }
        else if (m == 1)
        {
            SimpleFunction_2 *f = new SimpleFunction_2;
            initLeds(f);
        }
    }
    void comm(String json)
    {
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, json);
        if (error)
        {
            Serial.println("Error");
            Serial.println(error.c_str());
        }
        JsonObject obj = doc.as<JsonObject>();
        //String key;
        uint8_t b;
        for (JsonPair kv : obj)
        {
            const char *key = kv.key().c_str();
            Serial.println(key);
            if (strcmp(key, "b") == 0)
            {
                b = obj[key];
                states.set_brs(b);
                Serial.println(states.brs);
            }
            if (strcmp(key, "c") == 0)
            {
                rgb[0] = obj[key]["r"];
                rgb[1] = obj[key]["g"];
                rgb[2] = obj[key]["b"];
                Serial.println("color");
                Serial.println(rgb[0]);
                Serial.println(rgb[1]);
                Serial.println(rgb[2]);
                setLeds();
            }
            if (strcmp(key, "m") == 0)
            {
                m = obj[key];
                setLeds();
            }
        }
    }
};