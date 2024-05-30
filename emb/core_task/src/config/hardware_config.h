#ifndef CONFIG_HARDWARE_CONFIG
#define CONFIG_HARDWARE_CONFIG

#include <ArduinoJson.h>

namespace config {
JsonDocument loadHardwareConfig();
}

#endif  // CONFIG_HARDWARE_CONFIG