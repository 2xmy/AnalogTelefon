#include "esphome.h"

class AnalogButtonsComponent : public Component {
 private:
  unsigned long last_log_time = 0;

 public:
  void setup() override {
    // Initialize the pins
    pinMode(13, OUTPUT);
    pinMode(15, OUTPUT);
    pinMode(16, OUTPUT);
    pinMode(2, INPUT_PULLUP);
    pinMode(14, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    last_log_time = millis();
  }

  void loop() override {
    // Check the state of each button
    checkKeyState(13, 2, "Key 8 pressed");
    checkKeyState(13, 14, "Key 5 pressed");
    checkKeyState(13, 4, "Key 2 pressed");
    checkKeyState(15, 2, "Key 7 pressed");
    checkKeyState(15, 14, "Key 4 pressed");
    checkKeyState(15, 4, "Key 1 pressed");
    checkKeyState(16, 2, "Key 9 pressed");
    checkKeyState(16, 14, "Key 6 pressed");
    checkKeyState(16, 4, "Key 3 pressed");

    if (millis() - last_log_time > 10000) {  // 10 seconds
      ESP_LOGI("custom", "10 seconds have passed");
      last_log_time = millis();
    }
  }

 private:
  void checkKeyState(int commonPin, int keyPin, const char* message) {
    digitalWrite(13, HIGH);
    digitalWrite(15, HIGH);
    digitalWrite(16, HIGH);
    delay(10);
  
    digitalWrite(commonPin, LOW);
    delay(10);
  
    int keyState = digitalRead(keyPin);
  
    if (keyState == LOW) {
      ESP_LOGI("custom", "%s", message);
      delay(100); // Delay to prevent multiple triggers
    }
  }
};
