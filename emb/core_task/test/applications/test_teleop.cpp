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
  components::StateEstimation state_estimation{state_estimation_options};

  TeleopOptions options{};
  options.gain = 0.001;

  return Teleop{platform, state_estimation, options};
}

types::Measurement getDefualtMeasurement() {
  types::Measurement measurement{};
  measurement.header.sequence = 0;
  measurement.header.timestamp.microseconds = 1;
  measurement.encoder_1_pos = -300;
  measurement.encoder_2_pos = 400;

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

  ASSERT_EQ(types::Status::OKAY, teleop_application.cycle(types::Timestamp{}));
  EXPECT_NE(TeleopState{}, teleop_application.getState());

  types::Input expected_input{};
  expected_input.voltage = teleop_application.getOptions().gain * static_cast<double>(-700);
  EXPECT_EQ(expected_input, teleop_application.read());
}
}  // namespace applications
