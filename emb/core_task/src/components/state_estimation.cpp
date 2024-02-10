#include "state_estimation.h"

#include <tuple>

#include "../types/input.h"
#include "../types/measurement.h"
#include "../types/state.h"
#include "../types/status.h"
#include "../types/timestamp.h"
#include "../utilities/time.h"

namespace components {
bool operator==(const StateEstimationOptions& lhs, const StateEstimationOptions& rhs) { return true; }

StateEstimation::StateEstimation(const StateEstimationOptions& options) : state_{}, options_{options} {}

types::Status StateEstimation::open() {
  is_active_ = true;
  is_initialized_ = false;
  state_ = types::State{};
  return types::Status::OKAY;
}

types::Status StateEstimation::close() {
  is_active_ = false;
  is_initialized_ = false;
  state_ = types::State{};
  return types::Status::OKAY;
}

types::State StateEstimation::read() const { return getState(); }

types::Status StateEstimation::write(const types::Measurement& measurement) {
  if (is_active_ == false) {
    return types::Status::UNAVAILABLE;
  }

  if (is_initialized_ == false) {
    state_ = initializeState(measurement);
    is_initialized_ = true;
    return types::Status::OKAY;
  }

  types::State previous_state{state_};
  types::State state{};
  state.header = measurement.header;

  state.joint_1_position_rad = options_.joint_1_rad_per_count * measurement.encoder_1_pos;
  state.joint_1_velocity_rps = computeVelocity(state.joint_1_position_rad, previous_state.joint_1_position_rad,
                                               state.header.timestamp, previous_state.header.timestamp);

  state.joint_2_position_rad = options_.joint_2_rad_per_count * measurement.encoder_2_pos;
  state.joint_2_velocity_rps = computeVelocity(state.joint_2_position_rad, previous_state.joint_2_position_rad,
                                               state.header.timestamp, previous_state.header.timestamp);

  state_ = state;
  return types::Status::OKAY;
}

types::State StateEstimation::initializeState(const types::Measurement& measurement) const {
  types::State state{};
  state.header.sequence = 0;
  state.header.timestamp = measurement.header.timestamp;
  state.joint_1_position_rad = options_.joint_1_rad_per_count * measurement.encoder_1_pos;
  state.joint_1_velocity_rps = 0.0;
  state.joint_2_position_rad = options_.joint_2_rad_per_count * measurement.encoder_2_pos;
  state.joint_2_velocity_rps = 0.0;

  return state;
}

double StateEstimation::computeVelocity(const double current_position, const double previous_position,
                                        const types::Timestamp& current_timestamp,
                                        const types::Timestamp& previous_timestamp) {
  // TODO: Check times are okay
  // TODO: update Timestamp to give time elapsed and some other useful things.
  return (current_position - previous_position) / utilities::getDuration(previous_timestamp, current_timestamp).toSec();
}

const bool StateEstimation::isActive() const { return is_active_; }

const bool StateEstimation::isInitialized() const { return is_initialized_; }

const types::State& StateEstimation::getState() const { return state_; }

const StateEstimationOptions& StateEstimation::getOptions() const { return options_; }

bool operator==(const StateEstimation& lhs, const StateEstimation& rhs) {
  return std::make_tuple(lhs.getState(), lhs.getOptions(), lhs.isActive(), lhs.isInitialized()) ==
         std::make_tuple(rhs.getState(), rhs.getOptions(), rhs.isActive(), rhs.isInitialized());
}
}  // namespace components
