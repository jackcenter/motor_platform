#ifndef UTILITIES_SERIALIZE_H
#define UTILITIES_SERIALIZE_H

#include <ArduinoJson.h>

#include "../types/header.h"
#include "../types/input.h"
#include "../types/measurement.h"
#include "../types/state.h"
#include "../types/timestamp.h"

namespace utilities {
DynamicJsonDocument serialize(const types::Header& header);
DynamicJsonDocument serialize(const types::Input& input);
DynamicJsonDocument serialize(const types::Measurement& measurement);
DynamicJsonDocument serialize(const types::State& state);
DynamicJsonDocument serialize(const types::Timestamp& timestamp);
}  // namespace utilities
#endif  // UTILITIES_SERIALIZE_H
