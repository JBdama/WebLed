/*
  Released under Creative Commons Attribution 4.0
  by bitluni 2016
  https://creativecommons.org/licenses/by/4.0/
  Attribution means you can use it however you like as long you
  mention that it's base on my stuff.
  I'll be pleased if you'd do it by sharing http://youtube.com/bitlunislab
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <vector>
#include <bits/stdc++.h>

#include "text.h"
#include "LedStates.h"
#include "SimpleFunction.h"
#include "SimpleFunction_2.h"
#include "SimpleFunction_3.h"

const int LED_PIN = D4;
const int LED_COUNT = 8;
const char *ssid = "Devolo";
const char *password = "62122607890816550026";
using namespace std;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
ESP8266WebServer server(80);
LedStates states(strip);
//files file();
String slave;
String newslave;
vector<String> slaves_list;
uint8_t slaves_count = 0;
void wifiSetup();
void scanSlave();
void handleRoot() 
{
  String message = "<html><head></head><body style='font-family: sans-serif; font-size: 12px'>Following functions are available:<br><br>";
  server.send(200, "text/html", message);
}
void handleNotFound()
{
  String message = "File Not Found\n\n";
  server.send(404, "text/plain", message);
}
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
  wifiSetup();

  server.on("/", handleRoot);
  server.on("/setleds", []()
            {
              server.send(200, "text/plain", "setleds");
              SimpleFunction *f = new SimpleFunction();
              f->getRGB(100, 0, 0);
              checkFadeAndSetLedFunction(f);
            });
  server.on("/wave", []()
            {
              server.send(200, "text/plain", "setleds");
              SimpleFunction_2 *f = new SimpleFunction_2();
              f->getRGB(0,  100, 0);
              checkFadeAndSetLedFunction(f);
            });
  server.on("/rainbow", []()
            {
              server.send(200, "text/plain", "setleds");
              SimpleFunction_3 *f = new SimpleFunction_3();
              f->getRGB(0, 0, 100);
              checkFadeAndSetLedFunction(f);
            });
  server.begin();
  strip.begin();
  strip.show();
  scanSlave();
}
void loop()
{
  server.handleClient();
  states.loope();
  MDNS.update();
}

void wifiSetup()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  String ip = WiFi.localIP().toString();
  String MDNS_name = "esp";
  MDNS_name += ip.substring(ip.length()-2);
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
  slaves_count = n;
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

      slave = "http://" + slave + "/post";
      //slave_array[i]  = slave;
      slaves_list.push_back(MDNS.IP(i).toString());
    }
    //slave_array = slafe;
  }
  for (int i = 0; i < n; i++)
  {
  }
  //Serial.println(slave_array[i]);
}
