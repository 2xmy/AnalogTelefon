#include "esphome.h"
#include "esphome/components/AnalogTelefon/AnalogTelefon.h"

namespace esphome {
namespace analog_telefon_component {

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

}  // namespace esphome
}  // namespace analog_telefon_component
