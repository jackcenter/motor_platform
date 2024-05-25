#include "../../src/applications/teleop.h"

#include <ArduinoJson.h>
#include <gtest/gtest.h>

#include "../../src/components/controller.h"
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

  components::ControllerOptions controller_options{};
  controller_options.proportional_gain = 1.0;
  controller_options.integral_gain = 0.2;
  controller_options.derivative_gain = 0.3;
  controller_options.cycle_period_ms = 2;
  controller_options.input_range = {-5.0, 5.0};
  components::Controller controller{controller_options};

  components::StateEstimationOptions state_estimation_options{};
  state_estimation_options.joint_1_rad_per_count = 0.1;
  state_estimation_options.joint_2_rad_per_count = 0.2;
  components::StateEstimation state_estimation{state_estimation_options};

  TeleopOptions options{};
  return Teleop{platform, controller, state_estimation, options};
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
  const types::Measurement measurement{teleop_application.getState().measurement};
  EXPECT_NE(TeleopState{}, teleop_application.getState());
  EXPECT_NE(0.0, teleop_application.read().voltage);
}
}  // namespace applications
