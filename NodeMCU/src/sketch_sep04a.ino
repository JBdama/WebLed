
#include "server_helper.h"

void setup()
{
  Serial.begin(115200);
  startWifi();
  startWebSocket();
}

void loop()
{
  loopen();
}
