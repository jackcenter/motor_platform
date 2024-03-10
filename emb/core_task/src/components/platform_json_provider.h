#ifndef COMPONENTS_PLATFORM_JSON_PROVIDER_H
#define COMPONENTS_PLATFORM_JSON_PROVIDER_H

#include <ArduinoJson.h>

#include "platform.h"

namespace components {
class PlatformJsonProvider {
 public:
  PlatformJsonProvider() = default;
  Platform provide(const JsonDocument& doc) const;
};
}  // namespace components

#endif  // COMPONENTS_PLATFORM_JSON_PROVIDER_H