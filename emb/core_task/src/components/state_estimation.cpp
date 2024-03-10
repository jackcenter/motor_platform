#include "state_estimation.h"

#include <tuple>

#include "../types/state.h"

namespace components {
bool operator==(const StateEstimationOptions& lhs, const StateEstimationOptions& rhs) { return true; }

StateEstimation::StateEstimation(const StateEstimationOptions& options) : state_{}, options_{options} {}

types::State StateEstimation::read() const { return state_; }

void StateEstimation::write(const types::Input& input, const types::Measurement& measurement) {
  state_.joint_1_position_rad = measurement.encoder_1_pos;
  state_.joint_1_velocity_rps = 0.0;
  state_.joint_2_position_rad = measurement.encoder_2_pos;
  state_.joint_2_velocity_rps = 0.0;
}

const types::State& StateEstimation::getState() const { return state_; }

const StateEstimationOptions& StateEstimation::getOptions() const { return options_; }

bool operator==(const StateEstimation& lhs, const StateEstimation& rhs) {
  return std::make_tuple(lhs.getState(), lhs.getOptions()) == std::make_tuple(rhs.getState(), rhs.getOptions());
}
}  // namespace components
