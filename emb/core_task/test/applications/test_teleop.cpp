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

namespace applications {
Teleop getDefualtTelop() {
  DynamicJsonDocument config{config::getPlatformConfig()};
  components::PlatformJsonProvider platform_json_provider{};
  components::Platform platform{platform_json_provider.provide(config)};

  components::StateEstimationOptions state_estimation_options{};
  components::StateEstimation state_estimation{state_estimation_options};

  return Teleop{platform, state_estimation};
}

TEST(Teleop, Construction) { Teleop teleop_application{getDefualtTelop()}; }

TEST(Teleop, Cycle) {
  Teleop teleop_application{getDefualtTelop()};

  types::Measurement measurement;
  measurement.header = {};
  measurement.encoder_1_pos = 100;
  measurement.encoder_2_pos = -200;
  teleop_application.write(measurement);

  types::Status result{teleop_application.cycle()};
  ASSERT_EQ(types::Status::OKAY, result);

  const types::Input input{teleop_application.read()};
  const TeleopState state{teleop_application.getState()};

  EXPECT_EQ(measurement, state.measurement) << "1: " << state.measurement.encoder_1_pos << " 2: " << state.measurement.encoder_2_pos << "\n";
}
}  // namespace applications
