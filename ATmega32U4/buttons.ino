void setupButtons() {
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
}

void checkButtons() {
    for (uint8_t i = 0; i < 11; i++) {
        if (!digitalRead(keyPin[i]) && !keyPressed[i] && bounceTime[i] + BOUNCE_DELAY < millis()) {
            sendButtonPress(i);
            keyPressed[i] = true;
            bounceTime[i] = millis();

            if (i == 10) {
                if (displayButtonPressedTime + DOUBLE_PRESS_MAX_DELAY > millis()) {
                    if (serial1Disabled) enableSerial1();
                    else disableSerial1();
                }
                turnDisplayOn();
                displayButtonPressedTime = millis();
            }
        }

        if (!digitalRead(keyPin[i]) && keyPressed[i] && !keyLongPressed[i] && bounceTime[i] + BOUNCE_DELAY + HOLD_TIME < millis()) {
            sendLongButtonPress(i);
            keyLongPressed[i] = true;
        }

        if (digitalRead(keyPin[i]) && keyPressed[i] && bounceTime[i] + BOUNCE_DELAY < millis()) {
            keyPressed[i] = false;
            keyLongPressed[i] = false;
            bounceTime[i] = millis();
        }
    }
}
