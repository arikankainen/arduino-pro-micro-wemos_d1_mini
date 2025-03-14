void setupFile() {
    if (!SPIFFS.begin()) {
        Serial.println("SPIFFS Mount Failed");
        return;
    }
}

bool writeFile(String filename, String content) {
    File file = SPIFFS.open(filename, "w");

    if (!file) {
        Serial.println("Failed to open file for writing");
        return false;
    }

    file.print(content);
    file.close();

    return true;
}

String readFile(String filename) {
    File file = SPIFFS.open(filename, "r");

    if (!file) {
        Serial.println("Failed to open file for writing");
        return "";
    }

    String content = file.readString();
    file.close();

    return content;
}