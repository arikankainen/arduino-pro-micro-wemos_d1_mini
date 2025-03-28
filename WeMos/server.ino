void setupServer() {
    server.on("/", handleRoot);
    server.on("/settings", handleSettings);
    server.on("/scan", HTTP_GET, handleScan);
    server.on("/save_preset", HTTP_POST, handleSavePreset);
    server.on("/get_preset", HTTP_POST, handleGetPreset);
    server.on("/connect", HTTP_POST, handleConnect);
    server.on("/disconnect", HTTP_POST, handleDisconnect);
    server.begin();
    Serial.println("Web server started");
}

void checkServer() {
    server.handleClient();
}

void handleRoot() {
    server.send_P(200, "text/html", indexPage);
}

void handleSettings() {
    server.send_P(200, "text/html", settingsPage);
}

void handleScan() {
    int networksFound = WiFi.scanNetworks();
    String currentSSID = WiFi.SSID();
    int currentChannel = WiFi.channel();

    size_t jsonSize = 128 + (networksFound * 110);  // Estimate required size dynamically
    DynamicJsonDocument doc(jsonSize);

    JsonArray networks = doc.createNestedArray("networks");

    for (int i = 0; i < networksFound; i++) {
        String ssid = WiFi.SSID(i);
        int channel = WiFi.channel(i);
        int rssi = WiFi.RSSI(i);

        JsonObject net = networks.createNestedObject();
        net["ssid"] = ssid;
        net["channel"] = channel;
        net["signalStrengthDb"] = rssi;
        net["signalStrengthQuality"] = getSignalQuality(rssi);
        net["signalStrength"] = String(rssi) + " dB (" + getSignalQuality(rssi) + ")";
        net["encryption"] = getEncryptionTypeName(WiFi.encryptionType(i));
        net["connected"] = (ssid == currentSSID && channel == currentChannel);
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

void handleConnect() {
    if (server.hasArg("plain")) {
        String jsonData = server.arg("plain");

        StaticJsonDocument<256> doc;
        DeserializationError error = deserializeJson(doc, jsonData);

        if (error) {
            server.send(400, "text/plain", "JSON Parsing Failed");
            return;
        }

        String ssid = doc["ssid"];
        String password = doc["password"];

        writeFile("ssid.txt", ssid);
        writeFile("pass.txt", password);

        server.send(200, "text/plain", "OK");
        beginWifiStationMode();
    } else {
        server.send(400, "text/plain", "No data received");
    }
}

void handleDisconnect() {
    Serial.println("disconnected");
    server.send(200, "text/plain", "OK");

    writeFile("ssid.txt", "");
    writeFile("pass.txt", "");

    beginWifiApMode();
}
