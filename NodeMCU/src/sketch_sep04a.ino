
#include <Adafruit_NeoPixel.h>
#include "LedStates.h"
#include "server_helper.h"


//serv_help serv(states);



void setup()
{
  Serial.begin(115200);
  startWifi();
  startWebSocket();

}

void loop()
{
  loopen();
  states.loope();
  
}
