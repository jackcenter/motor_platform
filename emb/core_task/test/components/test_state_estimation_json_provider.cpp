#include "../../src/components/state_estimation_json_provider.h"

#include <ArduinoJson.h>
#include <gtest/gtest.h>

#include "../../src/components/state_estimation.h"

namespace components {
TEST(StateEstimationOptionsJsonProvider, ReturnsExpectedOptions) {
  const long joint_1_counts_per_revolution{1000};
  const long joint_2_counts_per_revolution{2000};

  JsonDocument temp_doc{};
  temp_doc["options"]["joint_1_counts_per_revolution"] = joint_1_counts_per_revolution;
  temp_doc["options"]["joint_2_counts_per_revolution"] = joint_2_counts_per_revolution;

  const JsonDocument doc{temp_doc};
  StateEstimationOptionsJsonProvider options_provider{};
  StateEstimationOptions options_from_json{options_provider.provide(doc["options"])};

  StateEstimationOptions expected_options{};
  expected_options.joint_1_counts_per_revolution = joint_1_counts_per_revolution;
  expected_options.joint_2_counts_per_revolution = joint_2_counts_per_revolution;

  EXPECT_EQ(expected_options, options_from_json);
}

TEST(StateEstimationJsonProvider, ReturnsExpectedStateEstimation) {
  const long joint_1_counts_per_revolution{1000};
  const long joint_2_counts_per_revolution{2000};

  JsonDocument temp_doc{};
  temp_doc["state_estimation"]["options"]["joint_1_counts_per_revolution"] = joint_1_counts_per_revolution;
  temp_doc["state_estimation"]["options"]["joint_2_counts_per_revolution"] = joint_2_counts_per_revolution;

  const JsonDocument doc{temp_doc};
  StateEstimationJsonProvider provider{};
  StateEstimation state_estimation_from_json{provider.provide(doc["state_estimation"])};

  StateEstimationOptions expected_options{};
  expected_options.joint_1_counts_per_revolution = joint_1_counts_per_revolution;
  expected_options.joint_2_counts_per_revolution = joint_2_counts_per_revolution;
  StateEstimation expected_state_estimation{expected_options};

  EXPECT_EQ(expected_state_estimation, state_estimation_from_json);
}
}  // namespace components