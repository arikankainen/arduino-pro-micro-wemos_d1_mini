#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "html_file.h"
#include "secrets.h"

ESP8266WebServer server(80);

void handleRoot() {
  server.send_P(200, "text/html", htmlPage);
}

void handleClick() {
  String textarea = server.arg("textarea");
  String checkbox = server.arg("checkbox");

  Serial.print("Textarea: ");
  Serial.println(textarea);
  Serial.print("Checkbox: ");
  Serial.println(checkbox);

  String response = "Data received: " + textarea + " | Checkbox: " + checkbox;
  server.send(200, "text/plain", response);
}

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
}

void loop() {
  server.handleClient();
}
