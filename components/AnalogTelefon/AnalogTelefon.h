#pragma once

#include "esphome.h"
#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include "esphome/components/api/custom_api_device.h"

namespace esphome {
namespace analog_telefon {

static const char *const TAG = "analog_telefon";

class AnalogTelefonComponent : public Component, public api::CustomAPIDevice {
 private:
  // Pin definitions
  const int commonPin1 = 13; // Common pin 1
  const int commonPin2 = 15; // Common pin 2
  const int commonPin3 = 16; // Common pin 3
  
  const int key1Pin = 2;     // Key input 1
  const int key2Pin = 14;    // Key input 2
  const int key3Pin = 4;     // Key input 3
  
  unsigned long last_key_press_time = 0;
  int last_key_pressed = 0;
  const unsigned long debounce_time = 300; // Debounce time in milliseconds

 public:
  void setup() override {
    // Initialize the pins
    pinMode(commonPin1, OUTPUT);
    pinMode(commonPin2, OUTPUT);
    pinMode(commonPin3, OUTPUT);
    pinMode(key1Pin, INPUT_PULLUP);
    pinMode(key2Pin, INPUT_PULLUP);
    pinMode(key3Pin, INPUT_PULLUP);
    
    // Set all common pins high initially
    digitalWrite(commonPin1, HIGH);
    digitalWrite(commonPin2, HIGH);
    digitalWrite(commonPin3, HIGH);
    
    // Register services to trigger Home Assistant scenes
    register_service(&AnalogTelefonComponent::on_key_pressed, "key_pressed", {"key"});
    
    ESP_LOGI(TAG, "Analog Telefon component initialized");
  }

  void loop() override {
    // Check each key in the matrix
    checkKey(commonPin1, key1Pin, 8);
    checkKey(commonPin1, key2Pin, 5);
    checkKey(commonPin1, key3Pin, 2);
    
    checkKey(commonPin2, key1Pin, 7);
    checkKey(commonPin2, key2Pin, 4);
    checkKey(commonPin2, key3Pin, 1);
    
    checkKey(commonPin3, key1Pin, 9);
    checkKey(commonPin3, key2Pin, 6);
    checkKey(commonPin3, key3Pin, 3);
  }

  void on_key_pressed(int key) {
    // This service can be called from Home Assistant for testing
    ESP_LOGI(TAG, "Service called with key: %d", key);
    
    // Trigger the scene in Home Assistant
    trigger_scene(key);
  }

 private:
  void checkKey(int commonPin, int keyPin, int keyNumber) {
    // Set all common pins high
    digitalWrite(commonPin1, HIGH);
    digitalWrite(commonPin2, HIGH);
    digitalWrite(commonPin3, HIGH);
    delay(5);
    
    // Set the current common pin low
    digitalWrite(commonPin, LOW);
    delay(5);
    
    // Read the key state
    int keyState = digitalRead(keyPin);
    
    // If key is pressed (LOW) and debounce time has passed
    if (keyState == LOW && 
        (millis() - last_key_press_time > debounce_time || last_key_pressed != keyNumber)) {
      ESP_LOGI(TAG, "Key %d pressed", keyNumber);
      
      // Trigger the scene in Home Assistant
      trigger_scene(keyNumber);
      
      // Update last press time and key
      last_key_press_time = millis();
      last_key_pressed = keyNumber;
    }
  }
  
  void trigger_scene(int keyNumber) {
    // Call the Home Assistant service to activate a scene based on the key number
    char service[64];
    snprintf(service, sizeof(service), "scene.turn_on");
    
    char entity_id[64];
    snprintf(entity_id, sizeof(entity_id), "scene.phone_key_%d", keyNumber);
    
    ESP_LOGI(TAG, "Triggering scene: %s", entity_id);
    
    // Call the Home Assistant service
    call_homeassistant_service(service, {
      {"entity_id", entity_id}
    });
  }
};

}  // namespace analog_telefon
}  // namespace esphome

