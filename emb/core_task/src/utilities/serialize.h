#ifndef UTILITIES_SERIALIZE_H
#define UTILITIES_SERIALIZE_H

#include <ArduinoJson.h>

#include "../types/header.h"
#include "../types/input.h"
#include "../types/measurement.h"
#include "../types/timestamp.h"

namespace utilities {
JsonDocument serialize(const types::Header& header);
JsonDocument serialize(const types::Input& input);
JsonDocument serialize(const types::Measurement& measurement);
JsonDocument serialize(const types::Timestamp& timestamp);
}  // namespace utilities
#endif  // UTILITIES_SERIALIZE_H
