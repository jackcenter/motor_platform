#include "../../src/utilities/serialize.h"

#include <ArduinoJson.h>
#include <gtest/gtest.h>

#include "../../src/types/header.h"
#include "../../src/types/input.h"
#include "../../src/types/measurement.h"
#include "../../src/types/timestamp.h"

namespace utilities {

types::Header getDefaultHeader() {
  types::Header header{};
  header.sequence = 1;
  header.timestamp.seconds = 2;
  header.timestamp.nanoseconds = 3;

  return header;
}

TEST(SerializeHeader, ContainsExpectedData) {
  const types::Header header{getDefaultHeader()};
  DynamicJsonDocument result{serialize(header)};

  EXPECT_TRUE(result["sequence"] == header.sequence);
  EXPECT_TRUE(result["timestamp"]["seconds"] == header.timestamp.seconds);
  EXPECT_TRUE(result["timestamp"]["nanoseconds"] == header.timestamp.nanoseconds);
}

TEST(SerializeInput, ContainsExpectedData) {
  types::Input input{};
  input.header = getDefaultHeader();
  input.voltage = 0.1;

  DynamicJsonDocument result{serialize(input)};

  EXPECT_TRUE(result["voltage"] == input.voltage);
  EXPECT_TRUE(result["header"]["sequence"] == input.header.sequence);
  EXPECT_TRUE(result["header"]["timestamp"]["seconds"] == input.header.timestamp.seconds);
  EXPECT_TRUE(result["header"]["timestamp"]["nanoseconds"] == input.header.timestamp.nanoseconds);
}

TEST(SerializeMeasurement, ContainsExpectedData) {
  types::Measurement measurement{};
  measurement.header = getDefaultHeader();
  measurement.encoder_1_pos = 1;
  measurement.encoder_2_pos = 2;

  DynamicJsonDocument result{serialize(measurement)};

  EXPECT_TRUE(result["encoder_1_pos"] == measurement.encoder_1_pos);
  EXPECT_TRUE(result["encoder_2_pos"] == measurement.encoder_2_pos);
  EXPECT_TRUE(result["header"]["sequence"] == measurement.header.sequence);
  EXPECT_TRUE(result["header"]["timestamp"]["seconds"] == measurement.header.timestamp.seconds);
  EXPECT_TRUE(result["header"]["timestamp"]["nanoseconds"] == measurement.header.timestamp.nanoseconds);
}

TEST(SerializeTimestamp, ContainsExpectedData) {
  types::Timestamp timestamp{};
  timestamp.seconds = 1;
  timestamp.nanoseconds = 2;

  DynamicJsonDocument result{serialize(timestamp)};

  EXPECT_TRUE(result["seconds"] == timestamp.seconds);
  EXPECT_TRUE(result["nanoseconds"] == timestamp.nanoseconds);
}
}  // namespace utilities
