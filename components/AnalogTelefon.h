#include "AnalogTelefon.h"
#include "esphome.h"

void AnalogTelefonComponent::setup() {
  // Setup code here
}

void AnalogTelefonComponent::loop() {
  static unsigned long last_time = 0;
  if (millis() - last_time > 1000) { // Every 1 second
    last_time = millis();
    ESP_LOGI("custom", "One second passed");
  }
}
