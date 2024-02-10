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

DynamicJsonDocument serialize(const types::Timestamp& timestamp) {
  DynamicJsonDocument doc{1024};
  doc["seconds"] = timestamp.seconds;
  doc["nanoseconds"] = timestamp.nanoseconds;
  return doc;
}
}  // namespace utilities