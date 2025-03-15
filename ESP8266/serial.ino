void setupSerial() {
    Serial.begin(115200);
}

void checkSerial() {
    if (Serial.available()) {
        String line = Serial.readStringUntil('\n');
        line.trim();

        // Serial.print("<DATA>");
        // Serial.print(line);
        // Serial.println("</DATA>");

        if (line == "button_long=10") {
            handleDisplayButtonLongPress();
        }

        if (line == "get_ip_address") {
            if (wifiApMode) sendApModeIpAddress();
            else sendStationModeIpAddress();
        }

        if (line.indexOf("button=") != -1) {
            String button = line.substring(line.indexOf('=') + 1);
            uint8_t preset = button.toInt() + 1;

            if (preset <= 10) sendPresetToSerial(String(preset));
        }
    }
}

void sendPresetToSerial(String preset) {
    String content = loadPreset(preset);
    Serial.println("###START###");
    Serial.println(content);
    Serial.println("###END###");
}

void handleDisplayButtonLongPress() {
    toggleWifiMode();
}

void sendPresetSavedToSerial(String preset) {
    Serial.print("preset_saved=");
    Serial.println(preset);
}