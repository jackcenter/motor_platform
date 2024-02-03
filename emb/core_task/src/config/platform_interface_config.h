#ifndef CONFIG_APPLICATION_CONFIG_H
#define CONFIG_APPLICATION_CONFIG_H

#include <ArduinoJson.h>

namespace config {
JsonDocument getPlatformInterfaceConfig();
}  // namespace config
#endif  // CONFIG_APPLICATION_CONFIG_H