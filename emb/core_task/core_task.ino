#include <string>
#include <unordered_map>
#include <utility>

#include <Arduino.h>
#include <ArduinoJson.h>

#include "src/interfaces/platform_interface.h"
#include "src/interfaces/platform_interface_json_provider.h"
#include "src/config/platform_interface_config.h"
#include "src/types/status.h"
#include "src/utilities/serialize.h"

int main() {
  JsonDocument config{config::getPlatformInterfaceConfig()};
  PlatformInterfaceJsonProvider platform_interface_json_provider{};
  PlatformInterface platform_interface{platform_interface_json_provider.provide(config)};

  bool led_level = false;
  int motor_level = 0;

  pinMode(13, OUTPUT);
  Serial.begin(9600);

  static std::unordered_map<int, double> motor_voltage_map{{0, 0.0}, {1, 2.0},  {2, 4.0},  {3, 2.0},
                                                           {4, 0.0}, {5, -2.0}, {6, -4.0}, {7, -2.0}};

  for (;;) {
    digitalWrite(13, led_level);

    types::Input input{};
    input.voltage = motor_voltage_map[motor_level % 8];

    const types::Status result{platform_interface.write(input)};
    if (result != types::Status::OKAY) {
      return 1;
    }

    types::Measurement measurement{platform_interface.read()};

    led_level = led_level ? false : true;
    ++motor_level;

    JsonDocument doc1{};
    doc1["input"] = utilities::serialize(input);
    serializeJson(doc1, Serial);
    Serial.println();

    JsonDocument doc2{};
    doc2["measurement"] = utilities::serialize(measurement);
    serializeJson(doc2, Serial);
    Serial.println();

    delay(1000);  // wait for a second

    yield();
  }

  return 0;
}
