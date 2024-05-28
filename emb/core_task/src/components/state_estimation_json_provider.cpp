#include "state_estimation_json_provider.h"

#include <ArduinoJson.h>

#include "state_estimation.h"

namespace components {
StateEstimationOptions StateEstimationOptionsJsonProvider::provide(const JsonDocument& doc) const {
  StateEstimationOptions options;
  options.joint_1_counts_per_revolution = doc["joint_1_counts_per_revolution"];
  options.joint_2_counts_per_revolution = doc["joint_2_counts_per_revolution"];

  return options;
}

StateEstimation StateEstimationJsonProvider::provide(const JsonDocument& doc) const {
  StateEstimationOptionsJsonProvider options_provider{};
  StateEstimationOptions options{options_provider.provide(doc["options"])};

  return StateEstimation{options};
}
}  // namespace components
