void setupServer() {
    server.on("/", handleRoot);
    server.on("/save_preset", HTTP_POST, handleSavePreset);
    server.on("/get_preset", HTTP_POST, handleGetPreset);
    server.begin();
    Serial.println("Web server started");
}

void handleRoot() {
    server.send_P(200, "text/html", htmlPage);
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

        sendPresetToSerial(preset);

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
