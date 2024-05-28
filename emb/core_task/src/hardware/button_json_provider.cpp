#include "button_json_provider.h"

#include <iostream>

#include <ArduinoJson.h>

#include "button.h"

namespace hardware {
ButtonOptions ButtonOptionsJsonProvider::provide(const JsonDocument& doc) const {
  ButtonOptions options;
  options.debounce_delay_ms = doc["debounce_delay_ms"];
  options.pin = doc["pin"];
  options.trigger = signal_state_map.at(doc["trigger"]);

  return options;
}

Button ButtonJsonProvider::provide(const JsonDocument& doc) const {
  ButtonOptionsJsonProvider options_provider{};
  ButtonOptions options{options_provider.provide(doc["options"])};
  return Button{options};
}
}  // namespace hardware
