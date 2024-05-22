#include "../../src/components/state_estimation.h"

#include <gtest/gtest.h>

#include "../../src/types/measurement.h"
#include "../../src/types/state.h"

namespace components {
StateEstimationOptions getDefaultStateEstimationOptions() {
  StateEstimationOptions state_estimation_options;
  state_estimation_options.joint_1_rad_per_count = 0.1;
  state_estimation_options.joint_2_rad_per_count = 0.2;

  return state_estimation_options;
}

StateEstimation getDefaultStateEstimation() {
  return StateEstimation{getDefaultStateEstimationOptions()};
}

TEST(StateEstimation, Construction) {
  StateEstimation state_estimation{getDefaultStateEstimation()};

  const types::State expected_state{};
  EXPECT_EQ(expected_state, state_estimation.read());
  EXPECT_FALSE(state_estimation.isActive());
  EXPECT_FALSE(state_estimation.isInitialized());
}

TEST(StateEstimation, OpensCorrectly) {
  StateEstimation state_estimation{getDefaultStateEstimation()};
  state_estimation.open();

  const types::State expected_state{};
  EXPECT_EQ(expected_state, state_estimation.read());
  EXPECT_TRUE(state_estimation.isActive());
  EXPECT_FALSE(state_estimation.isInitialized());
}

TEST(StateEstimation, ClosesCorrectly) {
  StateEstimation state_estimation{getDefaultStateEstimation()};
  state_estimation.close();

  const types::State expected_state{};
  EXPECT_EQ(expected_state, state_estimation.read());
  EXPECT_FALSE(state_estimation.isActive());
  EXPECT_FALSE(state_estimation.isInitialized());
}

TEST(StateEstimation, InitializesCorrectly) {
  StateEstimation state_estimation{getDefaultStateEstimation()};

  types::Measurement measurement{};
  measurement.header.sequence = 300;
  measurement.header.timestamp.microseconds = 400;
  measurement.encoder_1_pos = 500;
  measurement.encoder_2_pos = 600;

  EXPECT_EQ(types::Status::UNAVAILABLE, state_estimation.write(measurement));

  state_estimation.open();
  ASSERT_EQ(types::Status::OKAY, state_estimation.write(measurement));
  EXPECT_TRUE(state_estimation.isInitialized());

  types::State expected_state{};
  expected_state.header.sequence = 0;
  expected_state.header.timestamp = measurement.header.timestamp;
  expected_state.joint_1_position_rad =
      state_estimation.getOptions().joint_1_rad_per_count * measurement.encoder_1_pos;
  expected_state.joint_1_velocity_rps = 0.0;
  expected_state.joint_2_position_rad =
      state_estimation.getOptions().joint_2_rad_per_count * measurement.encoder_2_pos;
  expected_state.joint_2_velocity_rps = 0.0;
  EXPECT_EQ(expected_state, state_estimation.read());
}

TEST(StateEstimation, VelocityUpdatesInPositiveDirection) {
  StateEstimation state_estimation{getDefaultStateEstimation()};
  state_estimation.open();

  {
    types::Measurement measurement{};
    measurement.header.sequence = 300;
    measurement.header.timestamp.microseconds = 400;
    measurement.encoder_1_pos = 500;
    measurement.encoder_2_pos = 600;
    ASSERT_EQ(types::Status::OKAY, state_estimation.write(measurement));

    const types::State state{state_estimation.read()};
    EXPECT_FLOAT_EQ(0.0, state.joint_1_velocity_rps);
    EXPECT_FLOAT_EQ(0.0, state.joint_2_velocity_rps);
  }

  {
    types::Measurement measurement{};
    measurement.header.sequence = 301;
    measurement.header.timestamp.microseconds = 410;
    measurement.encoder_1_pos = 510;
    measurement.encoder_2_pos = 610;
    ASSERT_EQ(types::Status::OKAY, state_estimation.write(measurement));

    const types::State state{state_estimation.read()};
    EXPECT_GT(state.joint_1_velocity_rps, 0.0);
    EXPECT_GT(state.joint_2_velocity_rps, 0.0);
  }
}

TEST(StateEstimation, VelocityUpdatesInNegativeDirection) {
  StateEstimation state_estimation{getDefaultStateEstimation()};
  state_estimation.open();

  {
    types::Measurement measurement{};
    measurement.header.sequence = 300;
    measurement.header.timestamp.microseconds = 400;
    measurement.encoder_1_pos = 500;
    measurement.encoder_2_pos = 600;
    ASSERT_EQ(types::Status::OKAY, state_estimation.write(measurement));

    const types::State state{state_estimation.read()};
    EXPECT_FLOAT_EQ(0.0, state.joint_1_velocity_rps);
    EXPECT_FLOAT_EQ(0.0, state.joint_2_velocity_rps);
  }

  {
    types::Measurement measurement{};
    measurement.header.sequence = 301;
    measurement.header.timestamp.microseconds = 410;
    measurement.encoder_1_pos = 490;
    measurement.encoder_2_pos = 590;
    ASSERT_EQ(types::Status::OKAY, state_estimation.write(measurement));

    const types::State state{state_estimation.read()};
    EXPECT_LT(state.joint_1_velocity_rps, 0.0);
    EXPECT_LT(state.joint_2_velocity_rps, 0.0);
  }
}
}  // namespace components