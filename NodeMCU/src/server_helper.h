#include <ESPAsyncWebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <vector>
#include <bits/stdc++.h>
#include <ArduinoJson.h>
#include "LedStates.h"
#include <Adafruit_NeoPixel.h>

//#include "SimpleFunction_3.h"
#include "mgr.h"
#include "text.h"
const int LED_PIN = D4;
const int LED_COUNT = 8;

AsyncWebServer server(80);
AsyncWebSocket wSocket("/ws");
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
LedStates states(strip);
mgr mager(states);

std::vector<String> slaves_list;
const char *ssid = "Devolo";
const char *password = "62122607890816550026";
bool ledState = false;
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len)
{
  AwsFrameInfo *info = (AwsFrameInfo *)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
  {
    Serial.println("");
    //Serial.println((char *)data);
    String fetch = (char *)data;
    Serial.println(fetch);
    mager.comm(fetch);
  }
}
void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
               void *arg, uint8_t *data, size_t len)
{
  switch (type)
  {
  case WS_EVT_CONNECT:
    Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
    break;
  case WS_EVT_DISCONNECT:
    Serial.printf("WebSocket client #%u disconnected\n", client->id());
    break;
  case WS_EVT_DATA:
    handleWebSocketMessage(arg, data, len);
    break;
  case WS_EVT_PONG:
  case WS_EVT_ERROR:
    break;
  }
}

void sendMsg(String mes)
{
  wSocket.textAll(mes);
}
void notifyRgb()
{
  wSocket.cleanupClients();
  if (ledState)
  {
    String fin = "";
    String mes = "";
    for (int i = 0; i < 5; i++)
    {
      mes += "[";
      for (int j = 0; j < 3; j++)
      {
        //mes += state.values[i][j];
        if (j < 2)
          mes += ",";
      }
      mes += "]";
      if (i < 4)
        mes += ",";
    }
    Serial.println(mes);
    wSocket.textAll(mes);
  }
}
/*
  void checkFadeAndSetLedFunction(LedFunction *f)
  {
    f->init();
    state.setFunction(f);
    state.fader_start();
  }
  void toggleDown()
  {
    SimpleFunction_3 *f = new SimpleFunction_3;
    f->getRGB(25, 0, 0);
    checkFadeAndSetLedFunction(f);
  }
  void toggleAnim()
  {
    SimpleFunction_3 *f = new SimpleFunction_3();
    f->getRGB(255, 0, 200);
    checkFadeAndSetLedFunction(f);
  }
  */

void startWifi()
{
  Serial.println(ssid);
  Serial.println(password);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void startWebSocket()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/html", message_html2); });

  server.on("/icon.css", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "stylesheet/css", message_css2); });
  server.on("/rain.css", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "stylesheet/css", message_css); });
  wSocket.onEvent(onWsEvent);

  server.addHandler(&wSocket);
  server.begin();
}
void startMDNS()
{
  String ip = WiFi.localIP().toString();
  String MDNS_name = "esp";
  MDNS_name += ip.substring(ip.length() - 2);
  if (!MDNS.begin(MDNS_name))
  { // Start the mDNS responder for esp8266.local
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");
  MDNS.addService("esp", "tcp", 80);
}
void scanSlave()
{
  int8_t n = MDNS.queryService("esp", "tcp");
  if (n == 0)
  {
    Serial.println("No Service found");
  }
  else
  {
    for (int i = 0; i < n; i++)
    {
      Serial.println("Service found");
      Serial.println("Host: " + String(MDNS.hostname(i)));
      Serial.print("IP  : ");
      Serial.println(MDNS.IP(i));
      Serial.println("Port: " + String(MDNS.port(i)));

      slaves_list.push_back(MDNS.IP(i).toString());
    }
  }
}
void loopen()
{
    states.loope();
  wSocket.cleanupClients();
}
