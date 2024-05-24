#include "platform_config.h"

#include <ArduinoJson.h>

namespace config {
// cppcheck-suppress unusedFunction
DynamicJsonDocument getPlatformConfig() {
  DynamicJsonDocument config_json{1024};
  config_json["platform"]["actuator_interface"]["motor"]["options"]["min_voltage"] = -5.0;
  config_json["platform"]["actuator_interface"]["motor"]["options"]["max_voltage"] = 5.0;
  config_json["platform"]["actuator_interface"]["motor"]["options"]["voltage_multiplier"] = 1.0;

  return config_json;
}
}  // namespace config
