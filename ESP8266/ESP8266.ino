#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <ArduinoJson.h>

#include "html_file.h"
#include "secrets.h"

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
    server.on("/save_preset", HTTP_POST, handleSavePreset);
    server.on("/get_preset", HTTP_POST, handleGetPreset);

    server.begin();
    Serial.println("Web server started");

    if (!SPIFFS.begin()) {
        Serial.println("SPIFFS Mount Failed");
        return;
    }

    loadPreset("1");
}

void loop() {
    server.handleClient();
}

void handleRoot() {
    server.send_P(200, "text/html", htmlPage);
}

void savePreset(String preset, String content) {
    File file = SPIFFS.open("/preset_" + preset + ".txt", "w");
    if (!file) {
        Serial.println("Failed to open file for writing");
        return;
    }

    file.print(content);
    file.close();

    Serial.println("Preset #" + preset + " saved to SPIFFS");
    Serial.println(content);
}

String loadPreset(String preset) {
    File file = SPIFFS.open("/preset_" + preset + ".txt", "r");
    if (!file) return "";

    String content = file.readString();
    file.close();

    Serial.println("Preset #" + preset + "read from SPIFFS:");
    Serial.println(content);

    return content;
}

void handleSavePreset() {
    if (server.hasArg("plain")) {
        String jsonData = server.arg("plain");

        StaticJsonDocument<256> doc;
        DeserializationError error = deserializeJson(doc, jsonData);

        if (error) {
            server.send(400, "text/plain", "JSON Parsing Failed");
            return;
        }

        String preset = doc["preset"];
        String content = doc["content"];
        savePreset(preset, content);

        server.send(200, "text/plain", "Macro #" + preset + " saved!");
    } else {
        server.send(400, "text/plain", "No data received");
    }
}

void handleGetPreset() {
    if (server.hasArg("plain")) {
        String jsonData = server.arg("plain");

        StaticJsonDocument<256> doc;
        DeserializationError error = deserializeJson(doc, jsonData);

        if (error) {
            server.send(400, "text/plain", "JSON Parsing Failed");
            return;
        }

        String preset = doc["preset"];
        String content = loadPreset(preset);

        server.send(200, "text/plain", content);
    } else {
        server.send(400, "text/plain", "No data received");
    }
}
