#ifndef HARDWARE_BUTTON_JSON_PROVIDER_H
#define HARDWARE_BUTTON_JSON_PROVIDER_H

#include <ArduinoJson.h>

#include "button.h"

namespace hardware {
class ButtonOptionsJsonProvider {
 public:
  ButtonOptionsJsonProvider() = default;
  ButtonOptions provide(const JsonDocument& doc) const;
};

class ButtonJsonProvider {
 public:
  ButtonJsonProvider() = default;
  Button provide(const JsonDocument& doc) const;
};
}  // namespace hardware
#endif  // HARDWARE_BUTTON_JSON_PROVIDER_H