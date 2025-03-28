void setupSerial() {
    Serial.begin(115200);  // For debugging via USB
    enableSerial1();       // For communication with ESP8266
}

void checkSerial() {
    if (Serial1.available()) {
        String line = Serial1.readStringUntil('\n');
        line.trim();

        if (line == "###START###") {
            receiving = true;
            receivedData = "";
            return;
        }

        if (line == "###END###") {
            receiving = false;
            dataReceived();
            return;
        }

        if (receiving) {
            if (receivedData == "") receivedData = line;
            else receivedData += "\n" + line;
            return;
        }

        if (line.indexOf("ap_ip=") != -1) {
            int equalPos = line.indexOf('=');
            if (equalPos != -1) {
                String ipValue = line.substring(equalPos + 1);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Access Point");
                lcd.setCursor(0, 1);
                lcd.print(ipValue);
                turnDisplayOn();
            }
        }

        if (line.indexOf("station_ip=") != -1) {
            int equalPos = line.indexOf('=');
            if (equalPos != -1) {
                String ipValue = line.substring(equalPos + 1);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Connected");
                lcd.setCursor(0, 1);
                lcd.print(ipValue);
                turnDisplayOn();
            }
        }

        if (line.indexOf("error_code") != -1) {
            int equalPos = line.indexOf('=');
            if (equalPos != -1) {
                String code = line.substring(equalPos + 1);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Error connecting");
                lcd.setCursor(0, 1);
                lcd.print("Code: ");
                lcd.setCursor(6, 1);
                lcd.print(code);
                turnDisplayOn();
            }
        }

        if (line.indexOf("ap_connecting") != -1) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Creating");
            lcd.setCursor(0, 1);
            lcd.print("Access point...");
            turnDisplayOn();
        }

        if (line.indexOf("station_connecting") != -1) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Connecting to");
            lcd.setCursor(0, 1);
            lcd.print("network...");
            turnDisplayOn();
        }

        if (line.indexOf("preset_saved=") != -1) {
            String preset = line.substring(line.indexOf('=') + 1);
            String text = "Preset #" + preset + " saved";
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(text);
            turnDisplayOn();
            delay(2000);
            getIpAddress();
        }
    }
}

void disableSerial1() {
    Serial1.end();
    serial1Disabled = true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Serial disabled");
}

void enableSerial1() {
    Serial1.begin(115200);
    serial1Disabled = false;
    lcd.clear();
    getIpAddress();
}

void getIpAddress() {
    Serial1.println("get_ip_address");
}

void sendButtonPress(uint8_t button) {
    Serial1.println("button=" + String(button));
}

void sendLongButtonPress(uint8_t button) {
    Serial1.println("button_long=" + String(button));
}
