#include "serialize.h"

#include <ArduinoJson.h>

namespace utilities {
DynamicJsonDocument serialize(const types::Header& header) {
  DynamicJsonDocument doc{1024};
  doc["sequence"] = header.sequence;
  doc["timestamp"] = serialize(header.timestamp);
  return doc;
}

DynamicJsonDocument serialize(const types::Input& input) {
  DynamicJsonDocument doc{1024};
  doc["header"] = serialize(input.header);
  doc["voltage"] = input.voltage;
  return doc;
}

DynamicJsonDocument serialize(const types::Measurement& measurement) {
  DynamicJsonDocument doc{1024};
  doc["header"] = serialize(measurement.header);
  doc["encoder_1_pos"] = measurement.encoder_1_pos;
  doc["encoder_2_pos"] = measurement.encoder_2_pos;
  return doc;
}

DynamicJsonDocument serialize(const types::State& state) {
  DynamicJsonDocument doc{1024};
  doc["header"] = serialize(state.header);
  doc["joint_1_position_rad"] = state.joint_1_position_rad;
  doc["joint_1_velocity_rps"] = state.joint_1_velocity_rps;
  doc["joint_2_position_rad"] = state.joint_2_position_rad;
  doc["joint_2_velocity_rps"] = state.joint_2_velocity_rps;
  return doc;
}

DynamicJsonDocument serialize(const types::Timestamp& timestamp) {
  DynamicJsonDocument doc{1024};
  doc["microseconds"] = timestamp.microseconds;
  return doc;
}
}  // namespace utilities