#include "teleop.h"

#include "../types/input.h"
#include "../types/measurement.h"
#include "../types/state.h"
#include "../types/status.h"

namespace applications {
Teleop::Teleop(components::Platform& platform, const components::StateEstimation& state_estimation)
    : platform_{platform}, state_estimation_{state_estimation} {}

// cppcheck-suppress unusedFunction
types::Status Teleop::cycle() {
  const types::Measurement measurement{platform_.readMeasurement()};

  state_estimation_.write(state_.input, measurement);
  const types::State state{state_estimation_.read()};

  // TODO: Move reference generation out of here.
  types::State reference{};
  reference.joint_1_position_rad = state.joint_2_position_rad;

  // TODO: Put controller here
  types::State error{};
  error.joint_1_position_rad = state.joint_1_position_rad - reference.joint_1_position_rad;

  types::Input input{};
  input.voltage = 0.001 * error.joint_1_position_rad;

  const types::Status result{platform_.write(input)};
  if (result != types::Status::OKAY) {
    return result;
  }

  state_.input = input;
  state_.measurement = measurement;
  state_.state = state;

  return types::Status::OKAY;
}

const types::Input Teleop::read() const { return platform_.readInput(); };

types::Status Teleop::write(const types::Measurement& measurement) { return platform_.write(measurement); };

// cppcheck-suppress unusedFunction
const TeleopState& Teleop::getState() const { return state_; }
}  // namespace applications
