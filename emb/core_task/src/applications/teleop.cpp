#include "teleop.h"

#include <iostream>
#include <tuple>

#include "../components/controller.h"
#include "../components/platform.h"
#include "../components/state_estimation.h"
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

bool operator==(const TeleopOptions& lhs, const TeleopOptions& rhs) { return true; }

bool operator!=(const TeleopState& lhs, const TeleopState& rhs) { return !(lhs == rhs); }

Teleop::Teleop(const components::Platform& platform, const components::Controller& controller,
               const components::StateEstimation& state_estimation, const TeleopOptions& options)
    : platform_{platform}, controller_{controller}, state_estimation_{state_estimation}, state_{}, options_{options} {}

types::Status Teleop::open() {
  const types::Status platform_status{platform_.open()};
  if (platform_status != types::Status::OKAY) {
    close();
    return platform_status;
  }

  const types::Status controller_status{controller_.activate()};
  if (controller_status != types::Status::OKAY) {
    close();
    return controller_status;
  }

  const types::Status state_estimation_status{state_estimation_.open()};
  if (state_estimation_status != types::Status::OKAY) {
    close();
    return state_estimation_status;
  }

  is_active_ = true;
  return types::Status::OKAY;
}

types::Status Teleop::close() {
  const types::Status platform_status{platform_.close()};
  const types::Status controller_status{controller_.deactivate()};
  const types::Status state_estimation_status{state_estimation_.close()};

  if (platform_status != types::Status::OKAY) {
    // return UNKOWN here since it won't be clear which component failed to close
    return types::Status::UNKNOWN;
  }

  if (controller_status != types::Status::OKAY) {
    // return UNKOWN here since it won't be clear which component failed to close
    return types::Status::UNKNOWN;
  }

  if (state_estimation_status != types::Status::OKAY) {
    // return UNKOWN here since it won't be clear which component failed to close
    return types::Status::UNKNOWN;
  }

  is_active_ = false;
  return types::Status::OKAY;
}

// cppcheck-suppress unusedFunction
types::Status Teleop::cycle(const types::Timestamp& timestamp) {
  if (!isActive()) {
    return types::Status::UNAVAILABLE;
  }

  const types::Measurement measurement{platform_.readMeasurement(timestamp)};
  state_.measurement = measurement;

  state_estimation_.write(measurement);
  const types::State state{state_estimation_.read()};
  state_.state = state;

  const double reference{state.joint_2_position_rad};
  const types::Input input{controller_.cycle(reference, state, timestamp)};
  state_.input = input;
  const types::Status result{platform_.write(input)};
  if (result != types::Status::OKAY) {
    return result;
  }

  return types::Status::OKAY;
}

types::Status Teleop::write(const types::Measurement& measurement) { return platform_.write(measurement); };

const TeleopOptions& Teleop::getOptions() const { return options_; }

const components::Platform& Teleop::getPlatform() const { return platform_; }

// cppcheck-suppress unusedFunction
const TeleopState& Teleop::getState() const { return state_; }

const components::StateEstimation& Teleop::getStateEstimation() const { return state_estimation_; }

const bool Teleop::isActive() const { return is_active_; };

const types::Input Teleop::read() const { return platform_.readInput(); };

bool operator==(const Teleop& lhs, const Teleop& rhs) {
  return std::make_tuple(lhs.getPlatform(), lhs.getStateEstimation(), lhs.getState(), lhs.getOptions()) ==
         std::make_tuple(rhs.getPlatform(), rhs.getStateEstimation(), rhs.getState(), rhs.getOptions());
}
}  // namespace applications
