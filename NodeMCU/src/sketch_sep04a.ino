
#include <Adafruit_NeoPixel.h>
#include "LedStates.h"
#include "server_helper.h"
const int LED_PIN = D4;
const int LED_COUNT = 8;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
LedStates states(strip);

serv_help serv(states);



void setup()
{
  Serial.begin(115200);
  serv.startWifi();
  serv.startWebSocket();

}

void loop()
{
  serv.loop();
  states.loope();
  
}
