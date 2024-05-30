#ifndef COMPONENTS_CONTROLLER_JSON_PROVIDER_H
#define COMPONENTS_CONTROLLER_JSON_PROVIDER_H

#include <ArduinoJson.h>

#include "controller.h"

namespace components {
class ControllerOptionsJsonProvider {
 public:
  ControllerOptionsJsonProvider() = default;
  ControllerOptions provide(const JsonDocument& doc) const;
};

class ControllerJsonProvider {
 public:
  ControllerJsonProvider() = default;
  Controller provide(const JsonDocument& doc) const;
};
}  // namespace components

#endif  // COMPONENTS_CONTROLLER_JSON_PROVIDER_H