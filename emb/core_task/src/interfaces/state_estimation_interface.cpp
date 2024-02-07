#include "state_estimation_interface.h"

namespace interfaces {
StateEstimationInterface::StateEstimationInterface(const StateEstimationInterfaceOptions& options)
    : state_{}, options_{options} {}

types::State StateEstimationInterface::read() const { return state_; }

void StateEstimationInterface::write(const types::Input& input, const types::Measurement& measurement) {
  state_.joint_1_position_rad = measurement.encoder_1_pos;
  state_.joint_1_velocity_rps = 0.0;
  state_.joint_2_position_rad = measurement.encoder_2_pos;
  state_.joint_2_velocity_rps = 0.0;
}
}  // namespace interfaces