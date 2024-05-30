#ifndef COMPONENTS_STATE_ESTIMATION_JSON_PROVIDER_H
#define COMPONENTS_STATE_ESTIMATION_JSON_PROVIDER_H

#include <ArduinoJson.h>

#include "state_estimation.h"

namespace components {
class StateEstimationOptionsJsonProvider {
 public:
  StateEstimationOptionsJsonProvider() = default;
  StateEstimationOptions provide(const JsonDocument& doc) const;
};

class StateEstimationJsonProvider {
 public:
  StateEstimationJsonProvider() = default;
  StateEstimation provide(const JsonDocument& doc) const;
};
}  // namespace components
#endif  // COMPONENTS_STATE_ESTIMATION_JSON_PROVIDER_H
