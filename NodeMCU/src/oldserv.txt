/*
  Qyay
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <ESP8266mDNS.h>
#include <Arduino.h>
#include <ArduinoJson.h>

#include <bits/stdc++.h>
#include <Adafruit_NeoPixel.h>
#include <vector>
#include <bits/stdc++.h>

#include "websocket_help.h"
#include "server_help.h"
#include "text.h"
#include "LedStates.h"
#include "SimpleFunction.h"
#include "SimpleFunction_2.h"
#include "SimpleFunction_3.h"
using namespace std;

const int LED_PIN = D4;
const int LED_COUNT = 8;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
ESP8266WebServer server(80);
WebSocketsServer webs(81);
LedStates states(strip);
const char *rbgNames[] = {"r", "g", "b"};
uint8_t color1[3];
int b;
bool power = true;
bool sync = true;
String newslave;
files file;
websocket_help ws(webs);
server_help sev(server);

void handleLed();
void handleJSON();
void createcommands();
void handleRoot();
void handleNotFound();
void updateLed();
void checkFadeAndSetLedFunction(LedFunction *f)
{
  f->init();
  states.setFunction(f);
  states.fader_start();
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Serial startet:");
  sev.start();
  sev.scanSlave();

  server.on("/", handleRoot);
  server.on("/setleds", []()
            {
              server.send(200, "text/plain", "setleds");
              SimpleFunction *f = new SimpleFunction();
              f->getRGB(100, 0, 0);
              checkFadeAndSetLedFunction(f);
            });
  server.on("/json", handleJSON);
  server.begin();
  strip.begin();
  strip.show();
}
void loop()
{
  server.handleClient();
  ws.updateWS();
  states.loope();
  MDNS.update();
}

void handleRoot()
{
  server.send(200, "text/html", file.get_html());
}
void handleNotFound()
{
  String message = "File Not Found\n\n";
  server.send(404, "text/plain", message);
}

void createcommands(String command, JsonObject obje)
{
  if (command == "b")
    Serial.print("b");
}
uint8_t brightness = 0;
void handleJSON()
{
  String data = server.arg("plain");
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, data);
  if (error)
  {
    Serial.println("Error");
    Serial.println(error.c_str());
  }
  JsonObject obj = doc.as<JsonObject>();
  uint8_t r = obj["r"];
  brightness = obj["b"];
  vector<String> commands;
  String key;
  for (JsonPair kv : obj)
  {
    key = kv.key().c_str();
    //Serial.println(key);
    commands.push_back(kv.key().c_str());
    if (key == "b")
    {
      Serial.println("b ist gesetzt");
      b = obj[key];
      Serial.println(b);
    }
    else if (key == "c")
    {
      Serial.println("c ist gesetzt");
      for (int i = 0; i < 3; i++)
      {
        color1[i] = obj[key][rgbNames[i]];
        Serial.println(color1[i]);
      }
      updateLed();
    } else if (key == "p") {
      power = obj[key];
      Serial.println(power);
    } else if (key == "a") {
      String test = obj[key];
      Serial.println(test);
    }
    //createcommands(kv.key().c_str(), obj);
    //Serial.println(kv.value().as<char*>());
  }
  //createcommands(commands);
  server.send(204, "Daten Empfangen");
}
void updateLed() {

}