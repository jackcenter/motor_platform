#include "../../src/components/controller.h"

#include <gtest/gtest.h>

#include "../../src/types/input.h"
#include "../../src/types/state.h"
#include "../../src/types/timestamp.h"

namespace components {
Controller getDefaultController() {
  ControllerOptions options{};
  options.proportional_gain = 1.0;
  options.integral_gain = 2.0;
  options.derivative_gain = 3.0;

  return Controller{options};
}

TEST(Controller, Construction) {
  Controller controller{getDefaultController()};
  EXPECT_FALSE(controller.isActive());
  EXPECT_FALSE(controller.isInitialized());
}

TEST(Controller, ReturnsExpectedInput) {
  Controller controller{getDefaultController()};
  
  const double reference{ 0.0 };
  types::State state{};
  state.joint_1_position_rad = 1.0;
  const types::Timestamp timestamp{};

  {
    const types::Input input{controller.cycle(reference, state, timestamp)};
    EXPECT_FLOAT_EQ(0.0, input.voltage);
  }

  controller.activate();

  {
    const types::Input input{controller.cycle(reference, state, timestamp)};
    EXPECT_NE(0.0, input.voltage);
  }
}
}  // namespace components
