void dataReceived() {
    parseMacro(receivedData);
    Keyboard.releaseAll();
}

void parseMacro(String json) {
    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, json);
    if (error) return;

    for (JsonObject action : doc.as<JsonArray>()) {
        if (action.containsKey("text")) {
            const char* text = action["text"];
            Keyboard.print(text);
        }

        if (action.containsKey("key")) {
            const char* key = action["key"];
            int repeat = action.containsKey("repeat") ? action["repeat"].as<int>() : 1;
            bool press = action.containsKey("press") ? action["press"].as<bool>() : false;
            bool release = action.containsKey("release") ? action["release"].as<bool>() : false;

            if (key) {
                int keyValue = getKeyValue(key);
                if (press) {
                    Serial.print("PRESS");
                    Serial.println(key);
                }

                for (int i = 0; i < repeat; i++) {
                    if (press) Keyboard.press(keyValue);
                    else if (release) Keyboard.release(keyValue);
                    else Keyboard.write(keyValue);
                    if (repeat > 1) delay(10);
                }
            }
        }

        if (action.containsKey("release")) {
            const char* release = action["release"];
            if (release == "all") Keyboard.releaseAll();
        }

        if (action.containsKey("delay")) {
            int del = action["delay"];
            delay(del);
        }

        delay(10);
    }
}

int getKeyValue(const char* keyName) {
    if (strcmp(keyName, "KEY_UP_ARROW") == 0) return KEY_UP_ARROW;
    if (strcmp(keyName, "KEY_DOWN_ARROW") == 0) return KEY_DOWN_ARROW;
    if (strcmp(keyName, "KEY_LEFT_ARROW") == 0) return KEY_LEFT_ARROW;
    if (strcmp(keyName, "KEY_RIGHT_ARROW") == 0) return KEY_RIGHT_ARROW;
    if (strcmp(keyName, "KEY_LEFT_CTRL") == 0) return KEY_LEFT_CTRL;
    // if (strcmp(keyName, "KEY_LEFT_SHIFT") == 0) return KEY_LEFT_SHIFT;
    // if (strcmp(keyName, "KEY_LEFT_ALT") == 0) return KEY_LEFT_ALT;
    // if (strcmp(keyName, "KEY_LEFT_GUI") == 0) return KEY_LEFT_GUI;
    // if (strcmp(keyName, "KEY_RIGHT_CTRL") == 0) return KEY_RIGHT_CTRL;
    // if (strcmp(keyName, "KEY_RIGHT_SHIFT") == 0) return KEY_RIGHT_SHIFT;
    // if (strcmp(keyName, "KEY_RIGHT_ALT") == 0) return KEY_RIGHT_ALT;
    // if (strcmp(keyName, "KEY_RIGHT_GUI") == 0) return KEY_RIGHT_GUI;
    // if (strcmp(keyName, "KEY_TAB") == 0) return KEY_TAB;
    // if (strcmp(keyName, "KEY_CAPS_LOCK") == 0) return KEY_CAPS_LOCK;
    // if (strcmp(keyName, "KEY_BACKSPACE") == 0) return KEY_BACKSPACE;
    if (strcmp(keyName, "KEY_RETURN") == 0) return KEY_RETURN;
    // if (strcmp(keyName, "KEY_MENU") == 0) return KEY_MENU;
    // if (strcmp(keyName, "KEY_INSERT") == 0) return KEY_INSERT;
    // if (strcmp(keyName, "KEY_DELETE") == 0) return KEY_DELETE;
    // if (strcmp(keyName, "KEY_HOME") == 0) return KEY_HOME;
    // if (strcmp(keyName, "KEY_END") == 0) return KEY_END;
    // if (strcmp(keyName, "KEY_PAGE_UP") == 0) return KEY_PAGE_UP;
    // if (strcmp(keyName, "KEY_PAGE_DOWN") == 0) return KEY_PAGE_DOWN;
    // if (strcmp(keyName, "KEY_NUM_LOCK") == 0) return KEY_NUM_LOCK;
    // if (strcmp(keyName, "KEY_KP_SLASH") == 0) return KEY_KP_SLASH;
    // if (strcmp(keyName, "KEY_KP_ASTERISK") == 0) return KEY_KP_ASTERISK;
    // if (strcmp(keyName, "KEY_KP_MINUS") == 0) return KEY_KP_MINUS;
    // if (strcmp(keyName, "KEY_KP_PLUS") == 0) return KEY_KP_PLUS;
    // if (strcmp(keyName, "KEY_KP_ENTER") == 0) return KEY_KP_ENTER;
    // if (strcmp(keyName, "KEY_KP_1") == 0) return KEY_KP_1;
    // if (strcmp(keyName, "KEY_KP_2") == 0) return KEY_KP_2;
    // if (strcmp(keyName, "KEY_KP_3") == 0) return KEY_KP_3;
    // if (strcmp(keyName, "KEY_KP_4") == 0) return KEY_KP_4;
    // if (strcmp(keyName, "KEY_KP_5") == 0) return KEY_KP_5;
    // if (strcmp(keyName, "KEY_KP_6") == 0) return KEY_KP_6;
    // if (strcmp(keyName, "KEY_KP_7") == 0) return KEY_KP_7;
    // if (strcmp(keyName, "KEY_KP_8") == 0) return KEY_KP_8;
    // if (strcmp(keyName, "KEY_KP_9") == 0) return KEY_KP_9;
    // if (strcmp(keyName, "KEY_KP_0") == 0) return KEY_KP_0;
    // if (strcmp(keyName, "KEY_KP_DOT") == 0) return KEY_KP_DOT;
    // if (strcmp(keyName, "KEY_ESC") == 0) return KEY_ESC;
    // if (strcmp(keyName, "KEY_F1") == 0) return KEY_F1;
    if (strcmp(keyName, "KEY_F2") == 0) return KEY_F2;
    // if (strcmp(keyName, "KEY_F3") == 0) return KEY_F3;
    // if (strcmp(keyName, "KEY_F4") == 0) return KEY_F4;
    // if (strcmp(keyName, "KEY_F5") == 0) return KEY_F5;
    // if (strcmp(keyName, "KEY_F6") == 0) return KEY_F6;
    // if (strcmp(keyName, "KEY_F7") == 0) return KEY_F7;
    // if (strcmp(keyName, "KEY_F8") == 0) return KEY_F8;
    // if (strcmp(keyName, "KEY_F9") == 0) return KEY_F9;
    // if (strcmp(keyName, "KEY_F10") == 0) return KEY_F10;
    // if (strcmp(keyName, "KEY_F11") == 0) return KEY_F11;
    // if (strcmp(keyName, "KEY_F12") == 0) return KEY_F12;
    // if (strcmp(keyName, "KEY_PRINT_SCREEN") == 0) return KEY_PRINT_SCREEN;
    // if (strcmp(keyName, "KEY_SCROLL_LOCK") == 0) return KEY_SCROLL_LOCK;
    // if (strcmp(keyName, "KEY_PAUSE") == 0) return KEY_PAUSE;
    return 0;
}