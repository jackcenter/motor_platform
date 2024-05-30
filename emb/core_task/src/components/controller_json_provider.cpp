#include "controller_json_provider.h"

#include <ArduinoJson.h>

#include "controller.h"

namespace components {
ControllerOptions ControllerOptionsJsonProvider::provide(const JsonDocument& doc) const {
  ControllerOptions options;
  options.proportional_gain = doc["proportional_gain"];
  options.integral_gain = doc["integral_gain"];
  options.derivative_gain = doc["derivative_gain"];
  options.cycle_period_ms = doc["cycle_period_ms"];
  options.input_range = {doc["input_range_min"], doc["input_range_max"]};
  options.deadband_range = {doc["deadband_range_min"], doc["deadband_range_max"]};

  return options;
}

Controller ControllerJsonProvider::provide(const JsonDocument& doc) const {
  ControllerOptionsJsonProvider options_provider{};
  ControllerOptions options{options_provider.provide(doc["options"])};
  return Controller(options);
}
}  // namespace components
