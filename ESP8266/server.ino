void setupServer() {
    server.on("/", handleRoot);
    server.on("/scan", HTTP_GET, handleScan);
    server.on("/save_preset", HTTP_POST, handleSavePreset);
    server.on("/get_preset", HTTP_POST, handleGetPreset);
    server.begin();
    Serial.println("Web server started");
}

void checkServer() {
    server.handleClient();
}

void handleRoot() {
    server.send_P(200, "text/html", htmlPage);
}

void handleScan() {
    int networksFound = WiFi.scanNetworks();
    size_t jsonSize = 128 + (networksFound * 100);  // Estimate required size dynamically
    DynamicJsonDocument doc(jsonSize);
    JsonArray networks = doc.createNestedArray("networks");

    for (int i = 0; i < networksFound; i++) {
        int rssi = WiFi.RSSI(i);

        JsonObject net = networks.createNestedObject();
        net["ssid"] = WiFi.SSID(i);
        net["channel"] = WiFi.channel(i);
        net["signalStrength"] = String(rssi) + " dB (" + getSignalQuality(rssi) + ")";
        net["encryption"] = getEncryptionTypeName(WiFi.encryptionType(i));
    }

    String jsonString;
    serializeJson(doc, jsonString);

    server.send(200, "application/json", jsonString);
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
