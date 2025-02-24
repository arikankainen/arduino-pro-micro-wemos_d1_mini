#include <Keyboard.h>

String receivedData;
bool receiving;

void setup() {
    Serial.begin(115200);   // For debugging via USB
    Serial1.begin(115200);  // For communication with ESP8266
    Keyboard.begin();
}

void loop() {
    receiveData();
}

void receiveData() {
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
        }
    }
}

void dataReceived() {
    Serial.println("*************************");
    Serial.println(receivedData);
    Serial.println("*************************");
}
