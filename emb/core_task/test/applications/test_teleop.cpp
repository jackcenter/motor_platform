#include "../../src/applications/teleop.h"

#include <ArduinoJson.h>
#include <gtest/gtest.h>

#include "../../src/components/platform.h"
#include "../../src/components/platform_json_provider.h"
#include "../../src/components/state_estimation.h"
#include "../../src/config/platform_config.h"
#include "../../src/types/input.h"
#include "../../src/types/measurement.h"
#include "../../src/types/status.h"
#include "../../src/types/timestamp.h"

namespace applications {
Teleop getDefualtTelop() {
  DynamicJsonDocument config{config::getPlatformConfig()};
  components::PlatformJsonProvider platform_json_provider{};
  components::Platform platform{platform_json_provider.provide(config)};

  components::StateEstimationOptions state_estimation_options{};
  state_estimation_options.joint_1_rad_per_count = 0.1;
  state_estimation_options.joint_2_rad_per_count = 0.2;

  components::StateEstimation state_estimation{state_estimation_options};

  TeleopOptions options{};
  options.gain = 1.0;

  return Teleop{platform, state_estimation, options};
}

types::Measurement getDefualtMeasurement() {
  types::Measurement measurement{};
  measurement.header.sequence = 0;
  measurement.header.timestamp.microseconds = 1;
  measurement.encoder_1_pos = -3;
  measurement.encoder_2_pos = 4;

  return measurement;
}

TEST(Teleop, Construction) { Teleop teleop_application{getDefualtTelop()}; }

TEST(Teleop, CycleProvidesCorretInput) {
  Teleop teleop_application{getDefualtTelop()};

  ASSERT_EQ(types::Status::OKAY, teleop_application.open());
  EXPECT_EQ(types::Input{}, teleop_application.read());

  ASSERT_EQ(types::Status::OKAY, teleop_application.write(getDefualtMeasurement()));
  EXPECT_EQ(types::Input{}, teleop_application.read());
  EXPECT_EQ(TeleopState{}, teleop_application.getState());

  types::Timestamp timestamp{};
  timestamp.microseconds = 11;

  ASSERT_EQ(types::Status::OKAY, teleop_application.cycle(timestamp));

  const types::State state{teleop_application.getState().state};
  const types::Measurement measurement{ teleop_application.getState().measurement};
  EXPECT_NE(TeleopState{}, teleop_application.getState());
  EXPECT_NE(0.0, teleop_application.read().voltage) << state.joint_1_position_rad << " " << state.joint_2_position_rad
    << " " << measurement.encoder_1_pos << " " << measurement.encoder_2_pos;
}
}  // namespace applications
