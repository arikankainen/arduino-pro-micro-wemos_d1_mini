void savePreset(String preset, String content) {
    File file = SPIFFS.open("/preset_" + preset + ".txt", "w");
    if (!file) {
        Serial.println("Failed to open file for writing");
        return;
    }

    file.print(content);
    file.close();

    Serial.println("Preset #" + preset + " saved to SPIFFS");
    sendPresetSavedToSerial(preset);
}

String loadPreset(String preset) {
    File file = SPIFFS.open("/preset_" + preset + ".txt", "r");
    if (!file) return "";

    String content = file.readString();
    file.close();

    Serial.println("Preset #" + preset + "read from SPIFFS");
    return content;
}
