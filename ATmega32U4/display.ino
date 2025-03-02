void setupDisplay() {
    lcd.init();
    lcd.clear();
    lcd.backlight();
}

void checkDisplay() {
    if (serial1Disabled) return;

    if (backlightTurnedOnTime + DISPLAY_ON_TIME < millis()) {
        lcd.noBacklight();
    }
}

void turnDisplayOn() {
    backlightTurnedOnTime = millis();
    lcd.backlight();
}
