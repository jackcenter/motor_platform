#include "controller.h"

#include <tuple>

#include "../types/input.h"
#include "../types/state.h"
#include "../types/status.h"
#include "../types/timestamp.h"

namespace components {
bool operator==(const ControllerOptions& lhs, const ControllerOptions& rhs) {
  return std::make_tuple(lhs.proportional_gain, lhs.integral_gain, lhs.derivative_gain) ==
         std::make_tuple(rhs.proportional_gain, rhs.integral_gain, rhs.derivative_gain);
}

Controller::Controller(const ControllerOptions& options) : options_{options} {}

types::Status Controller::activate() {
  is_active_ = true;
  return types::Status::OKAY;
}

types::Status Controller::deactivate() {
  is_active_ = false;
  return types::Status::OKAY;
}

types::Status Controller::initialize() {
  is_initialized = true;
  return types::Status::OKAY;
}

types::Input Controller::cycle(const double reference, const types::State& state, const types::Timestamp& timestamp) {
  // check if active
  if (!is_active_) {
    return getInputToDisableControl(timestamp);
  }

  if (!is_initialized) {
    // This doesn't do anything at the moment
    is_initialized = true;
  }

  const double error_rad = reference - state.joint_1_position_rad;
  const double proportional_input = options_.proportional_gain * error_rad;

  types::Input input;
  input.header.timestamp = timestamp;
  input.voltage = proportional_input;

  return input;
}

const ControllerOptions& Controller::getOptions() const { return options_; }
bool Controller::isActive() const { return is_active_; }
bool Controller::isInitialized() const { return is_initialized; }

types::Input Controller::getInputToDisableControl(const types::Timestamp& timestamp) const {
  types::Input input;
  input.header.timestamp = timestamp;
  input.voltage = 0.0;

  return input;
}

bool operator==(const Controller& lhs, const Controller& rhs) { return lhs.getOptions() == rhs.getOptions(); }

}  // namespace components
