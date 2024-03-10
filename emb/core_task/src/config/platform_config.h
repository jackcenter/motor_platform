#ifndef CONFIG_PLATFORM_CONFIG_H
#define CONFIG_PLATFORM_CONFIG_H

#include <ArduinoJson.h>

namespace config {
DynamicJsonDocument getPlatformConfig();
}  // namespace config
#endif  // CONFIG_PLATFORM_CONFIG_H
