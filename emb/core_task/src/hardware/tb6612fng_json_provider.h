#ifndef HARDWARE_TB6612FNG_JSON_PROVIDER_H
#define HARDWARE_TB6612FNG_JSON_PROVIDER_H

#include <ArduinoJson.h>

#include "tb6612fng.h"

namespace hardware {
class Tb6612fngOptionsJsonProvider {
 public:
  Tb6612fngOptionsJsonProvider() = default;
  Tb6612fngOptions provide(const JsonDocument& doc) const;
};

class Tb6612fngJsonProvider {
 public:
  Tb6612fngJsonProvider() = default;
  Tb6612fng provide(const JsonDocument& doc) const;
};
}  // namespace hardware

#endif  // HARDWARE_TB6612FNG_JSON_PROVIDER_H
