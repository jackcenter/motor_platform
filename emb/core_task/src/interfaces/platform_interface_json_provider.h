#ifndef INTERFACES_PLATFORM_INTERFACE_PROVIDER_H
#define INTERFACES_PLATFORM_INTERFACE_PROVIDER_H

#include <ArduinoJson.h>

#include "platform_interface.h"

class PlatformInterfaceJsonProvider {
 public:
  PlatformInterfaceJsonProvider() = default;
  PlatformInterface provide(const JsonDocument& doc) const;
};

#endif  // INTERFACES_PLATFORM_INTERFACE_PROVIDER_H