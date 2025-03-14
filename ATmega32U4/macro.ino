void dataReceived() {
    // Serial.println("*************************");
    // Serial.println(receivedData);
    // Serial.println("*************************");

    Keyboard.print(receivedData);
    Keyboard.write(KEY_LEFT_ARROW);
    Keyboard.write(KEY_LEFT_ARROW);
    Keyboard.write(KEY_LEFT_ARROW);
    Keyboard.write(KEY_LEFT_ARROW);
    Keyboard.write(KEY_LEFT_ARROW);
    Keyboard.write(KEY_RETURN);
    Keyboard.write(KEY_UP_ARROW);
    Keyboard.write(KEY_RIGHT_ARROW);
    Keyboard.write(KEY_RIGHT_ARROW);
    Keyboard.write(KEY_RIGHT_ARROW);
    Keyboard.write(KEY_F2);
}
