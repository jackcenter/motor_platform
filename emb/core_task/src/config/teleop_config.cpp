#include "teleop_config.h"

#include <ArduinoJson.h>

namespace config {
// cppcheck-suppress unusedFunction
JsonDocument loadTeleopConfig() {
  JsonDocument doc{};
  doc["controller"]["options"]["proportional_gain"] = 4.0;
  doc["controller"]["options"]["integral_gain"] = 0.01;
  doc["controller"]["options"]["derivative_gain"] = 0.0;
  doc["controller"]["options"]["cycle_period_ms"] = 2;
  doc["controller"]["options"]["input_range_min"] = -5.0;
  doc["controller"]["options"]["input_range_max"] = 5.0;
  doc["controller"]["options"]["deadband_range_min"] = -0.02;
  doc["controller"]["options"]["deadband_range_max"] = 0.02;
  doc["platform"]["actuator_interface"]["motor"]["options"]["min_voltage"] = -5.0;
  doc["platform"]["actuator_interface"]["motor"]["options"]["max_voltage"] = 5.0;
  doc["platform"]["actuator_interface"]["motor"]["options"]["voltage_multiplier"] = 1.0;
  doc["state_estimation"]["options"]["joint_1_counts_per_revolution"] = 8400;
  doc["state_estimation"]["options"]["joint_2_counts_per_revolution"] = 2400;

  return doc;
}
}  // namespace config
