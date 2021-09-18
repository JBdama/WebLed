/*
#include "WebSocketsServer.h"
class websocket_help
{
public:
  WebSocketsServer &ws;
  websocket_help(WebSocketsServer &s) : ws(s)
  {
  }
  void start()
  {
    ws.begin();
    ws.onEvent(webSocketEvent);
    Serial.println("WebSocket server started");
  }
  void updateWS() {
    ws.loop();
  }
  void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
  {
    switch (type)
    {
    case WStype_DISCONNECTED:
      Serial.println("Disconnected");
      break;
    case WStype_CONNECTED:
    {
      IPAddress ip = ws.remoteIP(num);
      Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
    }
    break;
    case WStype_TEXT:
    }
  }
};
*/