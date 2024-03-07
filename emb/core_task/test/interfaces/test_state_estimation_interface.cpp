#include "../../src/interfaces/state_estimation_interface.h"

#include <gtest/gtest.h>

#include "../../src/types/state.h"

namespace interfaces {
TEST(StateEstimationInterface, Initialization) {
  StateEstimationInterfaceOptions state_estimation_interface_options;
  StateEstimationInterface state_estimation_interface{state_estimation_interface_options};
  const types::State state{state_estimation_interface.read()};
  
  const types::State expected_state{};
  EXPECT_EQ(expected_state, state.header);
}
}  // namespace interfaces