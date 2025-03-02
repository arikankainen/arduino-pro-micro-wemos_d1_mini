IPAddress local_IP(192, 168, 4, 22);
IPAddress gateway(192, 168, 4, 9);
IPAddress subnet(255, 255, 255, 0);


void setupWifi() {
    beginWifiStationMode();
}

void sendStationModeIpAddress() {
    Serial.print("station_ip=");
    Serial.println(WiFi.localIP());
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

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
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
