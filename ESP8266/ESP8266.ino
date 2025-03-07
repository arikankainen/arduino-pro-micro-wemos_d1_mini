#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <ArduinoJson.h>
#include <Wire.h>

#include "html_index.h"
#include "html_settings.h"
#include "secrets.h"

ESP8266WebServer server(80);
bool wifiApMode = false;

void setup() {
    setupSerial();
    setupWifi();
    setupServer();
    setupFile();
}

void loop() {
    checkSerial();
    checkServer();
}
