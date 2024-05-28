#include "controller.h"

#include <tuple>

#include "../types/input.h"
#include "../types/state.h"
#include "../types/status.h"
#include "../types/timestamp.h"
#include "../utilities/common.h"

namespace components {
bool operator==(const ControllerOptions& lhs, const ControllerOptions& rhs) {
  return std::make_tuple(lhs.proportional_gain, lhs.integral_gain, lhs.derivative_gain, lhs.cycle_period_ms,
                         lhs.input_range, lhs.deadband_range) ==
         std::make_tuple(rhs.proportional_gain, rhs.integral_gain, rhs.derivative_gain, rhs.cycle_period_ms,
                         rhs.input_range, rhs.deadband_range);
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
  error_sum_rad_ = 0.0;
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

  // proportional
  const double error_rad = reference - state.joint_1_position_rad;
  const double proportional_input = options_.proportional_gain * error_rad;

  // integral
  double error_sum_rad = error_sum_rad_;

  // check deadband
  if (!utilities::isInRange(error_rad, options_.deadband_range.first, options_.deadband_range.second)) {
    error_sum_rad += error_rad * (1e-3 * options_.cycle_period_ms);
  }
  double integral_input = options_.integral_gain * error_sum_rad;

  // derivative
  const double previous_error_rad = error_rad_;
  const double error_rate_rps = (error_rad - previous_error_rad) * (1e-3 * options_.cycle_period_ms);
  const double derivative_input = options_.derivative_gain * error_rate_rps;

  // check for wind up
  double proposed_input{proportional_input + integral_input - derivative_input};
  if (!utilities::isInRange(proposed_input, options_.input_range.first, options_.input_range.second) &&
      utilities::getSign(proposed_input) == utilities::getSign(error_rad)) {
    error_sum_rad = error_sum_rad_;
    integral_input = options_.integral_gain * error_sum_rad;
  }

  const double desired_input{proportional_input + integral_input + derivative_input};
  const double input_value{
      utilities::clamp<double>(desired_input, options_.input_range.first, options_.input_range.second)};

  error_rad_ = error_rad;
  error_sum_rad_ = error_sum_rad;

  types::Input input;
  input.header.timestamp = timestamp;
  input.voltage = input_value;

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
