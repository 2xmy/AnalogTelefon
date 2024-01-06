#include "esphome.h"

class AnalogTelefonComponent : public Component {
 public:
  void setup() override {
    // Setup code here
  }

  void loop() override {
    static unsigned long last_time = 0;
    if (millis() - last_time > 1000) { // Every 1 second
      last_time = millis();
      ESP_LOGI("custom", "One second passed");
    }
  }
};

// Registration macro
ESPHOME_REGISTER_COMPONENT(AnalogTelefonComponent, AnalogTelefonComponent)
