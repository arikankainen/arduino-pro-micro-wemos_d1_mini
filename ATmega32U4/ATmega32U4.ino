#include <Keyboard.h>

void setup() {
    Serial.begin(115200);   // For debugging via USB
    Serial1.begin(115200);  // For communication with ESP8266
    Keyboard.begin();
}

void loop() {
    if (Serial1.available()) {
        String received = Serial1.readStringUntil('\n');
        // String received = Serial1.readString();
        received.trim();
        Serial.print("Received: ");
        Serial.println(received);

        // if (received == "clicked") {
        //     Serial.println("Button was clicked!");
        //     Keyboard.print("Button was clicked !");
        // }
    }
}
