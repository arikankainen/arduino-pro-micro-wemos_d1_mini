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
            uint8_t key = action["key"];
            int repeat = action.containsKey("repeat") ? action["repeat"].as<int>() : 1;
            bool press = action.containsKey("press") ? action["press"].as<bool>() : false;
            bool release = action.containsKey("release") ? action["release"].as<bool>() : false;

            for (int i = 0; i < repeat; i++) {
                if (press) Keyboard.press(key);
                else if (release) Keyboard.release(key);
                else Keyboard.write(key);
                if (repeat > 1) delay(10);
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
