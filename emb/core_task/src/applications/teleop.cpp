#include "teleop.h"

#include "../types/input.h"
#include "../types/measurement.h"
#include "../types/state.h"
#include "../types/status.h"

namespace applications {
Teleop::Teleop(interfaces::PlatformInterface& platform_interface,
               const interfaces::StateEstimationInterface& state_estimation_interface)
    : platform_interface_{platform_interface}, state_estimation_interface_{state_estimation_interface} {}

// cppcheck-suppress unusedFunction
types::Status Teleop::cycle() {
  const types::Measurement measurement{platform_interface_.read()};

  state_estimation_interface_.write(state_.input, measurement);
  const types::State state{state_estimation_interface_.read()};

  // TODO: Move reference generation out of here.
  types::State reference{};
  reference.joint_1_position_rad = state.joint_2_position_rad;

  // TODO: Put controller here
  types::State error{};
  error.joint_1_position_rad = state.joint_1_position_rad - reference.joint_1_position_rad;

  types::Input input{};
  input.voltage = 0.001 * error.joint_1_position_rad;

  const types::Status result{platform_interface_.write(input)};
  if (result != types::Status::OKAY) {
    return result;
  }

  state_.input = input;
  state_.measurement = measurement;
  state_.state = state;

  return types::Status::OKAY;
}

// cppcheck-suppress unusedFunction
const TeleopState& Teleop::getState() const { return state_; }
}  // namespace applications
