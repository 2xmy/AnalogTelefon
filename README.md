# Analog Telefon ESPHome Component

This project allows you to control an analog telephone with an ESP32 device through ESPHome. When buttons 1-9 on the telephone keypad are pressed, it triggers corresponding scenes in Home Assistant.

## Hardware Setup

Connect your analog telephone keypad to the ESP32 as follows:

- Common pins (rows):
  - Common Pin 1: GPIO 13
  - Common Pin 2: GPIO 15
  - Common Pin 3: GPIO 16

- Key pins (columns):
  - Key Pin 1: GPIO 2
  - Key Pin 2: GPIO 14
  - Key Pin 3: GPIO 4

This creates a 3x3 matrix for the 9 keys on the telephone keypad.

## Installation

1. Copy the `components/AnalogTelefon` directory to your ESPHome configuration directory.
2. Copy the `analog_telefon.yaml` file to your ESPHome configuration directory.
3. Update the secrets in your `secrets.yaml` file:
   ```yaml
   wifi_ssid: "your_wifi_ssid"
   wifi_password: "your_wifi_password"
   api_encryption_key: "your_32_character_encryption_key"
   ota_password: "your_ota_password"
   fallback_password: "your_fallback_password"
   ```
4. Flash the ESP32 with the configuration:
   ```
   esphome run analog_telefon.yaml
   ```

## Home Assistant Configuration

Create scenes in Home Assistant for each key on the telephone keypad. The component will trigger scenes with entity IDs in the format `scene.phone_key_X` where X is the key number (1-9).

Example scene configuration for Home Assistant:

```yaml
scene:
  - name: "Phone Key 1"
    id: phone_key_1
    entities:
      light.living_room: on
      
  - name: "Phone Key 2"
    id: phone_key_2
    entities:
      light.bedroom: on
      
  # ... and so on for keys 3-9
```

## Testing

The ESPHome configuration includes test buttons that you can use to simulate key presses from the Home Assistant dashboard. These are useful for testing your scenes without having to physically press the buttons on the telephone.

## Customization

You can modify the pin assignments in the `AnalogTelefon.h` file if your hardware setup is different. You can also change the scene naming pattern by modifying the `trigger_scene` method.

## Original Arduino Code

The original Arduino code that this component is based on can be found in the `components/originalcode.example` file.

