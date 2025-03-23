#include <Keyboard.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include <avr/pgmspace.h>

#define BOUNCE_DELAY 100
#define DOUBLE_PRESS_MAX_DELAY 500
#define HOLD_TIME 1000
#define DISPLAY_ON_TIME 20000

uint8_t keyPin[11];
bool keyPressed[11];
bool keyLongPressed[11];
unsigned long bounceTime[16] = { 0 };
unsigned long backlightTurnedOnTime;
unsigned long displayButtonPressedTime;

String receivedData;
bool receiving;
bool serial1Disabled;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    setupButtons();
    setupDisplay();
    setupSerial();
    setupKeyboard();
}

void loop() {
    checkButtons();
    checkDisplay();
    checkSerial();
}
