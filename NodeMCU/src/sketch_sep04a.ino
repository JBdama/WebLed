#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <vector>
#include <bits/stdc++.h>
#include <WiFiClient.h>
#include <ESPAsyncWebServer.h>

#include "websocket_help.h"
#include "server_help.h"
#include "text.h"
#include "LedStates.h"
#include "SimpleFunction.h"
#include "SimpleFunction_2.h"
#include "SimpleFunction_3.h"
using namespace std;
bool ledState = true;
const int LED_PIN = D4;
const int LED_COUNT = 8;
const char* ssid = "Devolo";
const char* password =  "62122607890816550026";
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
LedStates states(strip);

String  message = R"rawliteral(
<html><head></head><body><i>Hello World</i>
  <p><button id="button" class="button">Toggle</button></p><script>
  var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;
  window.addEventListener('load', onLoad);
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage; // <-- add this line
  }
  function onOpen(event) {
    console.log('Connection opened');
  }
  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }
  function onMessage(event) {
    var state;
    console.log(event.data);
    if (event.data == "1"){
      state = "ON";
    }
    else{
      state = "OFF";
    }
    console.log("state", state);
  }
  function onLoad(event) {
    initWebSocket();
    initButton();
  }
  function initButton() {
    document.getElementById('button').addEventListener('click', toggle);
  }
  function toggle(){
    console.log("ES toggelt");
    websocket.send('toggle');
    
  }

</script></body></html>
)rawliteral";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
uint8_t leds[1][3] = {{0}};
void rainbow() {
  
}
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
void notifyClients() {
  ws.textAll(String(ledState));
}
void checkFadeAndSetLedFunction(LedFunction *f)
{
  f->init();
  states.setFunction(f);
  states.fader_start();
}
void toggleAnim() {
  SimpleFunction_3 *f = new SimpleFunction_3();
  f->getRGB(100, 0, 0);
  checkFadeAndSetLedFunction(f);
}
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    Serial.println(ledState);
    Serial.println((char*)data);
    if (strcmp((char*)data, "toggle") == 0) {
      ledState = !ledState;
      notifyClients();
      if(ledState) toggleAnim();
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
    switch (type) {
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

void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {request->send(200, "text/html", message);});
  ws.onEvent(onEvent);
  server.addHandler(&ws);
  
  server.begin(); 
}

void loop(){
  states.loope();
  ws.cleanupClients();
}


