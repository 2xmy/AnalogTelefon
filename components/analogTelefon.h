#include "analogTelefon.h"
#include "esphome.h"

void AnalogButtonsComponent::setup() {
  // Setup code here
}

void AnalogButtonsComponent::loop() {
  static unsigned long last_time = 0;
  if (millis() - last_time > 1000) { // Every 1 second
    last_time = millis();
    ESP_LOGI("custom", "One second passed");
  }
}
