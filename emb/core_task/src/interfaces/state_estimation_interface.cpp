#include "state_estimation_interface.h"

#include <tuple>

#include "../types/state.h"

namespace interfaces {
bool operator==(const StateEstimationInterfaceOptions& lhs, const StateEstimationInterfaceOptions& rhs) { return true; }

StateEstimationInterface::StateEstimationInterface(const StateEstimationInterfaceOptions& options)
    : state_{}, options_{options} {}

types::State StateEstimationInterface::read() const { return state_; }

void StateEstimationInterface::write(const types::Input& input, const types::Measurement& measurement) {
  types::State state{};
  state.header = measurement.header;
  state.joint_1_position_rad = measurement.encoder_1_pos;  // TODO: convert to radians
  state.joint_1_velocity_rps = computeVelocity(state.joint_1_position_rad, state_.joint_1_position_rad,
                                               state.header.timestamp, state_.header.timestamp);
  state.joint_2_position_rad = measurement.encoder_2_pos;  // TODO: convert to radians
  state.joint_2_velocity_rps = computeVelocity(state.joint_2_position_rad, state_.joint_2_position_rad,
                                               state.header.timestamp, state_.header.timestamp);

  state_ = state;
}

double StateEstimationInterface::computeVelocity(const double current_position, const double previous_position,
                                                 const types::Timestamp& current_timestamp,
                                                 const types::Timestamp& previous_timestamp) {
  // TODO: Check times are okay
  // TODO: update Timestamp to give time elapsed and some other useful things.
  return (current_position - previous_position) / 1.0;
}

const types::State& StateEstimationInterface::getState() const { return state_; }

const StateEstimationInterfaceOptions& StateEstimationInterface::getOptions() const { return options_; }

bool operator==(const StateEstimationInterface& lhs, const StateEstimationInterface& rhs) {
  return std::tuple(lhs.getState(), lhs.getOptions()) == std::tuple(rhs.getState(), rhs.getState());
}
}  // namespace interfaces
