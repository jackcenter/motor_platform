#include "teleop.h"

#include <iostream>
#include <tuple>

#include "../types/input.h"
#include "../types/measurement.h"
#include "../types/state.h"
#include "../types/status.h"
#include "../types/timestamp.h"

namespace applications {
bool operator==(const TeleopState& lhs, const TeleopState& rhs) {
  return std::make_tuple(lhs.input, lhs.measurement, lhs.state) ==
         std::make_tuple(rhs.input, rhs.measurement, rhs.state);
}

bool operator!=(const TeleopState& lhs, const TeleopState& rhs) { return !(lhs == rhs); }

bool operator==(const TeleopOptions& lhs, const TeleopOptions& rhs) { return lhs.gain == rhs.gain; }

Teleop::Teleop(const components::Platform& platform, const components::StateEstimation& state_estimation,
               const TeleopOptions& options)
    : platform_{platform}, state_estimation_{state_estimation}, state_{}, options_{options} {}

types::Status Teleop::close() {
  const types::Status platform_status{platform_.close()};
  const types::Status state_estimation_status{state_estimation_.close()};

  if (platform_status != types::Status::OKAY) {
    // return UNKOWN here since it won't be clear which component failed to close
    return types::Status::UNKNOWN;
  }

  if (state_estimation_status != types::Status::OKAY) {
    // return UNKOWN here since it won't be clear which component failed to close
    return types::Status::UNKNOWN;
  }

  return types::Status::OKAY;
}

// cppcheck-suppress unusedFunction
types::Status Teleop::cycle(const types::Timestamp& timestamp) {
  const types::Measurement measurement{platform_.readMeasurement(timestamp)};

  state_estimation_.write(measurement);
  const types::State state{state_estimation_.read()};

  // TODO: Move reference generation out of here.
  types::State reference{};
  reference.joint_1_position_rad = state.joint_2_position_rad;

  // TODO: Put controller here
  types::State error{};
  error.joint_1_position_rad = state.joint_1_position_rad - reference.joint_1_position_rad;

  types::Input input{};
  input.header.timestamp = timestamp;
  input.voltage = options_.gain * error.joint_1_position_rad;

  const types::Status result{platform_.write(input)};
  if (result != types::Status::OKAY) {
    return result;
  }

  state_.input = input;
  state_.measurement = measurement;
  state_.state = state;

  return types::Status::OKAY;
}

types::Status Teleop::open() {
  const types::Status platform_status{platform_.open()};
  if (platform_status != types::Status::OKAY) {
    close();
    return platform_status;
  }

  const types::Status state_estimation_status{state_estimation_.open()};
  if (state_estimation_status != types::Status::OKAY) {
    close();
    return state_estimation_status;
  }

  return types::Status::OKAY;
}

types::Status Teleop::write(const types::Measurement& measurement) { return platform_.write(measurement); };

const TeleopOptions& Teleop::getOptions() const { return options_; }

const components::Platform& Teleop::getPlatform() const { return platform_; }

// cppcheck-suppress unusedFunction
const TeleopState& Teleop::getState() const { return state_; }

const components::StateEstimation& Teleop::getStateEstimation() const { return state_estimation_; }

const types::Input Teleop::read() const { return platform_.readInput(); };

bool operator==(const Teleop& lhs, const Teleop& rhs) {
  return std::make_tuple(lhs.getPlatform(), lhs.getStateEstimation(), lhs.getState(), lhs.getOptions()) ==
         std::make_tuple(rhs.getPlatform(), rhs.getStateEstimation(), rhs.getState(), rhs.getOptions());
}
}  // namespace applications
