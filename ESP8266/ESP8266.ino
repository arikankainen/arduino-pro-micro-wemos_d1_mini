#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "html_file.h"
#include "secrets.h"
#include <FS.h>

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  Serial.print("ESP8266 IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/click", HTTP_POST, handleClick);

  server.begin();
  Serial.println("Web server started");

  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }

  loadMacro("1");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  server.send_P(200, "text/html", htmlPage);
}

void saveMacro(String preset, String macro) {
  File file = SPIFFS.open("/macro" + preset + ".txt", "w");
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }

  file.print(macro);
  file.close();

  Serial.println("Macro #" + preset + " saved to SPIFFS");
}

String loadMacro(String preset) {
  File file = SPIFFS.open("/macro" + preset + ".txt", "r");
  if (!file) return "";

  String macro = file.readString();
  file.close();

  Serial.println("Macro #" + preset + "read from SPIFFS:");
  Serial.println(macro);

  return macro;
}

void handleClick() {
  String macro1 = server.arg("macro1");
  saveMacro("1", macro1);

  Serial.print("Macro #1:");
  Serial.println(macro1);

  String response = macro1;
  server.send(200, "text/plain", response);
}
