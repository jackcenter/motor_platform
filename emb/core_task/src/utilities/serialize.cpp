#include "serialize.h"

#include <ArduinoJson.h>

namespace utilities {
JsonDocument serialize(const types::Header& header) {
  JsonDocument doc;
  doc["sequence"] = header.sequence;
  doc["timestamp"] = serialize(header.timestamp);

  return doc;
}

JsonDocument serialize(const types::Input& input) {
  JsonDocument doc;
  doc["header"] = serialize(input.header);
  doc["voltage"] = input.voltage;

  return doc;
}

JsonDocument serialize(const types::Measurement& measurement) {
  JsonDocument doc;
  doc["header"] = serialize(measurement.header);
  doc["encoder_1_pos"] = measurement.encoder_1_pos;
  doc["encoder_2_pos"] = measurement.encoder_2_pos;

  return doc;
}

JsonDocument serialize(const types::Timestamp& timestamp) {
  JsonDocument doc;
  doc["seconds"] = timestamp.seconds;
  doc["nanoseconds"] = timestamp.nanoseconds;

  return doc;
}
}  // namespace utilities