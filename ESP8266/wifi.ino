IPAddress local_IP(192, 168, 4, 22);
IPAddress gateway(192, 168, 4, 9);
IPAddress subnet(255, 255, 255, 0);

String getEncryptionTypeName(uint8_t encType) {
    switch (encType) {
        case ENC_TYPE_WEP: return "WEP";
        case ENC_TYPE_TKIP: return "WPA";
        case ENC_TYPE_CCMP: return "WPA2";
        case ENC_TYPE_AUTO: return "WPA/WPA2";
        case ENC_TYPE_NONE: return "Open";
        default: return "Unknown";
    }
}

String getSignalQuality(int rssi) {
    if (rssi >= -50) return "Excellent";
    if (rssi >= -60) return "Very Good";
    if (rssi >= -70) return "Good";
    if (rssi >= -80) return "Weak";
    return "Very Poor";
}

void setupWifi() {
    beginWifiStationMode();
}

void prinScanResult(int networksFound) {
    Serial.printf("%d network(s) found\n", networksFound);
    for (int i = 0; i < networksFound; i++) {
        Serial.printf("%d: %s, Ch:%d (%ddBm) %s\n", i + 1, WiFi.SSID(i).c_str(), WiFi.channel(i), WiFi.RSSI(i), WiFi.encryptionType(i) == ENC_TYPE_NONE ? "open" : "");
    }
}

void sendStationModeIpAddress() {
    if (WiFi.status() == WL_CONNECTED) {
        Serial.print("station_ip=");
        Serial.println(WiFi.localIP());
    } else {
        sendErrorConnecting();
    }
}

void sendErrorConnecting() {
    Serial.print("error_code=");
    Serial.println(WiFi.status());
}

void sendStationModeConnecting() {
    Serial.println("station_connecting");
}

void sendApModeIpAddress() {
    Serial.print("ap_ip=");
    Serial.println(WiFi.softAPIP());
}

void sendApModeConnecting() {
    Serial.println("ap_connecting");
}

void beginWifiStationMode() {
    sendStationModeConnecting();
    WiFi.softAPdisconnect(true);
    wifiApMode = false;

    String ssid = readFile("ssid.txt");
    String password = readFile("pass.txt");

    WiFi.mode(WIFI_STA);
    WiFi.setPhyMode(WIFI_PHY_MODE_11G);
    WiFi.begin(ssid.c_str(), password.c_str());

    Serial.print("Connecting to WiFi...");

    unsigned long startAttemptTime = millis();
    const unsigned long timeout = 20000;

    while (WiFi.status() != WL_CONNECTED) {
        if (millis() - startAttemptTime > timeout) {
            Serial.println("\nWiFi connection failed. Giving up.");

            Serial.print("WiFi Status Code: ");
            Serial.println(WiFi.status());

            Serial.print("SSID:'");
            Serial.print(ssid);
            Serial.println("'");

            Serial.print("Pass:'");
            Serial.print(password);
            Serial.println("'");

            sendErrorConnecting();
            return;
        }
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
    sendStationModeIpAddress();
}

void beginWifiApMode() {
    sendApModeConnecting();
    WiFi.disconnect(true);
    wifiApMode = true;

    Serial.print("Setting soft-AP configuration... ");
    Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

    Serial.print("Setting soft-AP... ");
    Serial.println(WiFi.softAP(WIFI_AP_SSID, WIFI_AP_PASSWORD) ? "Ready" : "Failed!");

    Serial.print("Soft-AP IP address: ");
    Serial.println(WiFi.softAPIP());
    sendApModeIpAddress();
}

void toggleWifiMode() {
    if (wifiApMode) beginWifiStationMode();
    else beginWifiApMode();
}
