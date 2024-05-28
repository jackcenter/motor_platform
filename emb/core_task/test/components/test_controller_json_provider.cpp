#include "../../src/components/controller_json_provider.h"

#include <ArduinoJson.h>
#include <gtest/gtest.h>

#include "../../src/components/controller.h"

namespace components {
TEST(ControllerOptionsJsonProvider, ReturnsExpectedOptions) {
  const double proportional_gain{1.0};
  const double integral_gain{2.0};
  const double derivative_gain{3.0};
  const double cycle_period_ms{4.0};
  const double input_range_min{5.0};
  const double input_range_max{6.0};
  const double deadband_range_min{7.0};
  const double deadband_range_max{8.0};

  JsonDocument temp_doc{};
  temp_doc["options"]["proportional_gain"] = proportional_gain;
  temp_doc["options"]["integral_gain"] = integral_gain;
  temp_doc["options"]["derivative_gain"] = derivative_gain;
  temp_doc["options"]["cycle_period_ms"] = cycle_period_ms;
  temp_doc["options"]["input_range_min"] = input_range_min;
  temp_doc["options"]["input_range_max"] = input_range_max;
  temp_doc["options"]["deadband_range_min"] = deadband_range_min;
  temp_doc["options"]["deadband_range_max"] = deadband_range_max;

  const JsonDocument doc{temp_doc};
  ControllerOptionsJsonProvider options_provider{};
  ControllerOptions options_from_json{options_provider.provide(doc["options"])};

  ControllerOptions expected_options{};
  expected_options.proportional_gain = proportional_gain;
  expected_options.integral_gain = integral_gain;
  expected_options.derivative_gain = derivative_gain;
  expected_options.cycle_period_ms = cycle_period_ms;
  expected_options.input_range = {input_range_min, input_range_max};
  expected_options.deadband_range = {deadband_range_min, deadband_range_max};

  EXPECT_EQ(expected_options, options_from_json);
}

TEST(ControllerJsonProvider, ReturnsExpectedController) {
  const double proportional_gain = 1.0;
  const double integral_gain = 2.0;
  const double derivative_gain = 3.0;
  const double cycle_period_ms = 4.0;
  const double input_range_min = 5.0;
  const double input_range_max = 6.0;
  const double deadband_range_min = 7.0;
  const double deadband_range_max = 8.0;

  JsonDocument temp_doc{};
  temp_doc["controller"]["options"]["proportional_gain"] = proportional_gain;
  temp_doc["controller"]["options"]["integral_gain"] = integral_gain;
  temp_doc["controller"]["options"]["derivative_gain"] = derivative_gain;
  temp_doc["controller"]["options"]["cycle_period_ms"] = cycle_period_ms;
  temp_doc["controller"]["options"]["input_range_min"] = input_range_min;
  temp_doc["controller"]["options"]["input_range_max"] = input_range_max;
  temp_doc["controller"]["options"]["deadband_range_min"] = deadband_range_min;
  temp_doc["controller"]["options"]["deadband_range_max"] = deadband_range_max;

  const JsonDocument& doc{temp_doc};
  ControllerJsonProvider provider{};
  Controller controller_from_json{provider.provide(doc["controller"])};

  ControllerOptions expected_options{};
  expected_options.proportional_gain = proportional_gain;
  expected_options.integral_gain = integral_gain;
  expected_options.derivative_gain = derivative_gain;
  expected_options.cycle_period_ms = cycle_period_ms;
  expected_options.input_range = {input_range_min, input_range_max};
  expected_options.deadband_range = {deadband_range_min, deadband_range_max};
  Controller expected_controller{expected_options};

  EXPECT_EQ(expected_controller, controller_from_json);
}
}  // namespace components