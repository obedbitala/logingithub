#include <Arduino.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h> //https://github.com/esp8266/Arduino
#else
#include <WiFi.h>
#endif
// needed for library
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h> //https://github.com/tzapu/WiFiManager
#include <SPI.h>
#include"SPIFFS.h"
#define reset 19
//listes des profs
//int professeurs[]={};
AsyncWebServer server(80);
DNSServer dns;
void setup() {
 Serial.begin(115200);
  Serial.println("\n");

  AsyncWiFiManager wifiManager(&server, &dns);
  // reset saved settings

  // set custom ip for portal
  // wifiManager.setAPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
  // fetches ssid and pass from eeprom and tries to connect
  // if it does not connect it starts an access point with the specified name
  // here  "AutoConnectAP"
  // and goes into a blocking loop awaiting configuration
  
  // or use this for auto generated name ESP + ChipID
  // wifiManager.autoConnect();
  // if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
  wifiManager.autoConnect("AliceApConect");
  //----------------------------------------------------Serial
  if (reset == 1)
  wifiManager.resetSettings();
  //------------------GESTION DE WIFI-------------
  //----------------------------------------------------SPIFFS
  if(!SPIFFS.begin())
  {
    Serial.println("Erreur SPIFFS...");
    return;
  }

  File root = SPIFFS.open("/");
  File file = root.openNextFile();

  while(file)
  {
    Serial.print("File: ");
    Serial.println(file.name());
    file.close();
    file = root.openNextFile();
  }
  //----------------------------------------------------WIFI
	Serial.print("Tentative de connexion...");

    //----------------------------------------------------SERVER
   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/index.html", "text/html");
  });
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/index2.html", "text/html");
  });

  server.on("/w3.css", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/w3.css", "text/css");
  });
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/script.js", "text/javascript");
  });
  server.on("/jquery-3.7.1.min.js", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/jquery-3.7.1.min.js", "text/javascript");
  });
}

void loop() {

}

