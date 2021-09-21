
#include "server_helper.h"

void setup()
{
  Serial.begin(115200);
  start_up();
  startWifi();
  startWebSocket();
}

void loop()
{
  loopen();
}
