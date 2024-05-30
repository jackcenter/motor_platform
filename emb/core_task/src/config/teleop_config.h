#ifndef CONFIG_TELEOP_CONFIG_H
#define CONFIG_TELEOP_CONFIG_H

#include <ArduinoJson.h>

namespace config {
JsonDocument loadTeleopConfig();
}  // namespace config
#endif  // CONFIG_TELEOP_CONFIG_H
