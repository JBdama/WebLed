#include <ESPAsyncWebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <vector>
#include <bits/stdc++.h>
#include <ArduinoJson.h>
#include "LedStates.h"
#include "mgr.h"
#include "text.h"
#include "liveview.h"
const int LED_PIN = D4;
const int LED_COUNT = 200;

AsyncWebServer server(80);
AsyncWebSocket wSocket("/ws");
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
LedStates states(strip);
mgr mager(states);
std::stringstream ss;
std::string ss2;
std::vector<String> slaves_list;

const uint8_t gRb[3] = {1, 0, 2};
uint8_t *point ;
bool lv = false;
const char *ssid = "Devolo";
const char *password = "62122607890816550026";
bool ledState = false;
void start_up()
{
  mager.setup_mgr();
}
void choose_command(JsonObject dataa)
{
  for (JsonPair kv : dataa)
  {
    const char *key = kv.key().c_str();
    //Serial.println(key);
    if (strcmp(key, "b") == 0)
    {
      mager.b = dataa[key];
      states.set_brs(mager.b);
      Serial.println(states.brs);
    }
    if (strcmp(key, "c") == 0)
    {
      mager.rgb[0] = dataa[key]["r"];
      mager.rgb[1] = dataa[key]["g"];
      mager.rgb[2] = dataa[key]["b"];
      Serial.println("color");

      mager.updateLeds();
    }
    if (strcmp(key, "c_g") == 0) {
      states.active_c[0] = dataa[key][0];
      states.active_c[1] = dataa[key][1];
      states.active_c[2] = dataa[key][2];
    }
    if (strcmp(key, "m") == 0)
    {
      mager.m = dataa[key];
      mager.updateLeds();
    }
    if (strcmp(key, "p") == 0)
    {
      mager.power = dataa[key];
      mager.fade_power(mager.power);
    }
    if (strcmp(key, "lv") == 0)
    {
      lv = !lv;
      point = strip.getPixels();
    }
  }
}
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len)
{
  AwsFrameInfo *info = (AwsFrameInfo *)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
  {
    String fetch = (char *)data;
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, data);
    if (error)
    {
      Serial.println("Error");
      Serial.println(error.c_str());
    }
    JsonObject obj = doc.as<JsonObject>();

    Serial.println(fetch);
    choose_command(obj);
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
  server.on("/liveview", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/html", message_lv); });
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
String getLeds() {
  std::string led_array = "";
  for (int i = 0; i < LED_COUNT ; i ++) {
    led_array += "\"";
    for (int j = 0  ; j < 3; j++) {
      ss.str(std::string());
      ss <<  std::hex << (int)point[3*i + gRb[j]];
      if (ss.str().size() < 2) led_array += "0" ;
      led_array += ss.str();
    }
    led_array += "\"";
    led_array += ",";
  }
  led_array.pop_back();
  led_array = "{\"leds\":[" + led_array + "]}";
  //Serial.println(led_array.c_str());
  return led_array.c_str();
}
void loopen()
{
  states.loope();
  if (lv)
  {
    wSocket.textAll(getLeds());
  }
  wSocket.cleanupClients();
}
