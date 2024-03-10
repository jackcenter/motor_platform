#include "actuator_interface.h"

#include "../actuators/brushed_motor.h"
#include "../types/input.h"
#include "../types/status.h"

namespace interfaces {
bool operator==(const ActuatorInterfaceOptions& lhs, const ActuatorInterfaceOptions& rhs) { return true; }

ActuatorInterace::ActuatorInterace(const actuators::BrushedMotor& motor, const ActuatorInterfaceOptions& options)
    : motor_{motor}, options_{options} {}

types::Input ActuatorInterace::read() const {
  types::Input input{};
  input.header = {};
  input.voltage = motor_.read();

  return input;
}

types::Status ActuatorInterace::write(const types::Input& input) { return motor_.write(input.voltage); }

void ActuatorInterace::activate() { motor_.open(); }

void ActuatorInterace::deactivate() { motor_.close(); }

const actuators::BrushedMotor& ActuatorInterace::getMotor() const { return motor_; }

const ActuatorInterfaceOptions& ActuatorInterace::getOptions() const { return options_; }

bool operator==(const ActuatorInterace& lhs, const ActuatorInterace& rhs) {
  return std::make_tuple(lhs.getMotor(), lhs.getOptions()) == std::make_tuple(rhs.getMotor(), rhs.getOptions());
}
}  // namespace interfaces
