#ifndef INTERFACES_PLATFORM_INTERFACE_PROVIDER_H
#define INTERFACES_PLATFORM_INTERFACE_PROVIDER_H

#include <ArduinoJson.h>

#include "platform_interface.h"

namespace interfaces {
class PlatformInterfaceJsonProvider {
 public:
  PlatformInterfaceJsonProvider() = default;
  PlatformInterface provide(const JsonDocument& doc) const;
};
}  // namespace interfaces

#endif  // INTERFACES_PLATFORM_INTERFACE_PROVIDER_H