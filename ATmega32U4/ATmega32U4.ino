#include <Keyboard.h>
#include <LiquidCrystal_I2C.h>

#define BOUNCE_DELAY 1000
#define DISPLAY_ON_TIME 20000

uint8_t keyPin[11];
bool keyPressed[11];
bool keyLongPressed[11];
unsigned long bounceTime[16] = { 0 };
unsigned long backlightTurnedOnTime;

String receivedData;
bool receiving;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    keyPin[0] = 4;
    keyPin[1] = 5;
    keyPin[2] = 6;
    keyPin[3] = 7;
    keyPin[4] = 8;
    keyPin[5] = 9;
    keyPin[6] = 10;
    keyPin[7] = 16;
    keyPin[8] = 14;
    keyPin[9] = 15;
    keyPin[10] = 18;

    for (uint8_t i = 0; i < 11; i++) pinMode(keyPin[i], INPUT_PULLUP);

    lcd.init();
    lcd.clear();
    lcd.backlight();

    Serial.begin(115200);   // For debugging via USB
    Serial1.begin(115200);  // For communication with ESP8266
    Keyboard.begin();
}

void loop() {
    checkButtons();
    checkDisplay();
    checkSerial();
}

void sendButtonPress(uint8_t button) {
    Serial1.println("button=" + String(button));
}

void sendLongButtonPress(uint8_t button) {
    Serial1.println("button_long=" + String(button));
}

void turnDisplayOn() {
    backlightTurnedOnTime = millis();
    lcd.backlight();
}

void disableSerial() {
    Serial.println("Serial1 disabled!");
    Serial1.end();
}

void enableSerial() {
    Serial.println("Serial1 enabled!");
    Serial1.begin(115200);
}

void checkButtons() {
    for (uint8_t i = 0; i < 11; i++) {
        if (!digitalRead(keyPin[i]) && !keyPressed[i] && bounceTime[i] + BOUNCE_DELAY < millis()) {
            sendButtonPress(i);
            keyPressed[i] = true;
            bounceTime[i] = millis();
            if (i == 10) turnDisplayOn();
        }

        if (!digitalRead(keyPin[i]) && keyPressed[i] && !keyLongPressed[i] && bounceTime[i] + BOUNCE_DELAY < millis()) {
            if (i == 10) sendLongButtonPress(i);
            if (i == 0) disableSerial();
            keyLongPressed[i] = true;
        }

        if (digitalRead(keyPin[i]) && keyPressed[i] && bounceTime[i] + BOUNCE_DELAY < millis()) {
            if (i == 0) enableSerial();
            keyPressed[i] = false;
            keyLongPressed[i] = false;
            bounceTime[i] = millis();
        }
    }
}

void checkDisplay() {
    if (backlightTurnedOnTime + DISPLAY_ON_TIME < millis()) {
        lcd.noBacklight();
    }
}

void checkSerial() {
    if (Serial1.available()) {
        String line = Serial1.readStringUntil('\n');
        line.trim();

        Serial.print("Received: ");
        Serial.println(line);

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

        if (line.indexOf("ap_connecting") != -1) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Creating");
            lcd.setCursor(0, 1);
            lcd.print("Access Point...");
        }

        if (line.indexOf("station_connecting") != -1) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Connecting To");
            lcd.setCursor(0, 1);
            lcd.print("Network...");
        }
    }
}

void dataReceived() {
    Serial.println("*************************");
    Serial.println(receivedData);
    Serial.println("*************************");
    // Keyboard.print(receivedData);
}
