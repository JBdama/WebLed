#include <ESP8266WebServer.h>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
class server_help
{
public:
  vector<String> slaves_list;
  const char *ssid = "Devolo";
  const char *password = "62122607890816550026";
  ESP8266WebServer &server;
  server_help(ESP8266WebServer &s) : server(s) {}
  void start()
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

};