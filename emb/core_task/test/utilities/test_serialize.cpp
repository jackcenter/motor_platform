#include "../../src/utilities/serialize.h"

#include <ArduinoJson.h>
#include <gtest/gtest.h>

#include "../../src/types/header.h"
#include "../../src/types/input.h"
#include "../../src/types/measurement.h"
#include "../../src/types/state.h"
#include "../../src/types/timestamp.h"

namespace utilities {

types::Header getDefaultHeader() {
  types::Header header{};
  header.sequence = 1;
  header.timestamp.microseconds = 2;

  return header;
}

TEST(SerializeHeader, ContainsExpectedData) {
  const types::Header header{getDefaultHeader()};
  DynamicJsonDocument result{serialize(header)};

  EXPECT_TRUE(result["sequence"] == header.sequence);
  EXPECT_TRUE(result["timestamp"]["microseconds"] == header.timestamp.microseconds);
}

TEST(SerializeInput, ContainsExpectedData) {
  types::Input input{};
  input.header = getDefaultHeader();
  input.voltage = 0.1;

  DynamicJsonDocument result{serialize(input)};

  EXPECT_TRUE(result["voltage"] == input.voltage);
  EXPECT_TRUE(result["header"]["sequence"] == input.header.sequence);
  EXPECT_TRUE(result["header"]["timestamp"]["microseconds"] == input.header.timestamp.microseconds);
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
  EXPECT_TRUE(result["header"]["timestamp"]["microseconds"] == measurement.header.timestamp.microseconds);
}

TEST(SerializeState, ContainsExpectedData) {
types::State state{};
state.header = getDefaultHeader();
state.joint_1_position_rad = 0.1;
state.joint_1_velocity_rps = 1.2;
state.joint_2_position_rad = 2.3;
state.joint_2_velocity_rps = 3.4;

DynamicJsonDocument result{serialize(state)};

EXPECT_TRUE(result["joint_1_position_rad"] == state.joint_1_position_rad);
EXPECT_TRUE(result["joint_1_velocity_rps"] == state.joint_1_velocity_rps);
EXPECT_TRUE(result["joint_2_position_rad"] == state.joint_2_position_rad);
EXPECT_TRUE(result["joint_2_velocity_rps"] == state.joint_2_velocity_rps);
EXPECT_TRUE(result["header"]["sequence"] == state.header.sequence);
EXPECT_TRUE(result["header"]["timestamp"]["microseconds"] == state.header.timestamp.microseconds);
}

TEST(SerializeTimestamp, ContainsExpectedData) {
  types::Timestamp timestamp{};
  timestamp.microseconds = 1;

  DynamicJsonDocument result{serialize(timestamp)};

  EXPECT_TRUE(result["microseconds"] == timestamp.microseconds);
}
}  // namespace utilities
