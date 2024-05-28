#include "serialize.h"

#include <ArduinoJson.h>

namespace utilities {
JsonDocument serialize(const types::Header& header) {
  JsonDocument doc{};
  doc["sequence"] = header.sequence;
  doc["timestamp"] = serialize(header.timestamp);
  return doc;
}

JsonDocument serialize(const types::Input& input) {
  JsonDocument doc{};
  doc["header"] = serialize(input.header);
  doc["voltage"] = input.voltage;
  return doc;
}

JsonDocument serialize(const types::Measurement& measurement) {
  JsonDocument doc{};
  doc["header"] = serialize(measurement.header);
  doc["encoder_1_pos"] = measurement.encoder_1_pos;
  doc["encoder_2_pos"] = measurement.encoder_2_pos;
  return doc;
}

JsonDocument serialize(const types::State& state) {
  JsonDocument doc{};
  doc["header"] = serialize(state.header);
  doc["joint_1_position_rad"] = state.joint_1_position_rad;
  doc["joint_1_velocity_rps"] = state.joint_1_velocity_rps;
  doc["joint_2_position_rad"] = state.joint_2_position_rad;
  doc["joint_2_velocity_rps"] = state.joint_2_velocity_rps;
  return doc;
}

JsonDocument serialize(const types::Timestamp& timestamp) {
  JsonDocument doc{};
  doc["microseconds"] = timestamp.microseconds;
  return doc;
}
}  // namespace utilities