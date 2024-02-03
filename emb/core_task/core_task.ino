#include <string>
#include <unordered_map>
#include <utility>

#include <Arduino.h>
#include <ArduinoJson.h>

#include "src/applications/teleop.h"
#include "src/config/platform_interface_config.h"
#include "src/interfaces/platform_interface.h"
#include "src/interfaces/platform_interface_json_provider.h"
#include "src/types/status.h"
#include "src/utilities/serialize.h"

int main() {
  JsonDocument config{config::getPlatformInterfaceConfig()};
  interfaces::PlatformInterfaceJsonProvider platform_interface_json_provider{};
  interfaces::PlatformInterface platform_interface{platform_interface_json_provider.provide(config)};

  applications::Teleop teleop_application{platform_interface};

  bool led_level = false;

  pinMode(13, OUTPUT);
  Serial.begin(9600);

  for (;;) {
    digitalWrite(13, led_level);
    led_level = led_level ? false : true;

    teleop_application.cycle();
    applications::TeleopState teleop_state{teleop_application.getState()};

    JsonDocument doc1{};
    doc1["input"] = utilities::serialize(teleop_state.input);
    serializeJson(doc1, Serial);
    Serial.println();

    JsonDocument doc2{};
    doc2["measurement"] = utilities::serialize(teleop_state.measurement);
    serializeJson(doc2, Serial);
    Serial.println();

    delay(2);

    yield();
  }

  return 0;
}
