#include "actuator_interface.h"

#include "../actuators/brushed_motor.h"
#include "../types/input.h"
#include "../types/status.h"

namespace interfaces {
bool operator==(const ActuatorInterfaceOptions& lhs, const ActuatorInterfaceOptions& rhs) { return true; }

ActuatorInterface::ActuatorInterface(const actuators::BrushedMotor& motor, const ActuatorInterfaceOptions& options)
    : motor_{motor}, options_{options}, active_{false}, timestamp_{} {}

types::Status ActuatorInterface::open() {
  if (isActive()) {
    motor_.open();
    return types::Status::PRECONDITION_FAILED;
  }

  active_ = true;
  write(types::Input{});
  return motor_.open();
}

types::Status ActuatorInterface::close() {
  if (!isActive()) {
    motor_.close();
    return types::Status::PRECONDITION_FAILED;
  }

  write(types::Input{});
  active_ = false;
  return motor_.close();
}

types::Status ActuatorInterface::write(const types::Input& input) {
  types::Status result{motor_.write(input.voltage)};
  timestamp_ = input.header.timestamp;

  if (types::Status::OKAY != result) {
    return result;
  }

  return types::Status::OKAY;
}

const actuators::BrushedMotor& ActuatorInterface::getMotor() const { return motor_; }

const ActuatorInterfaceOptions& ActuatorInterface::getOptions() const { return options_; }

bool ActuatorInterface::isActive() const { return active_; }

types::Input ActuatorInterface::read() const {
  types::Input input{};
  input.header.timestamp = timestamp_;
  input.voltage = motor_.read();
  return input;
}

bool operator==(const ActuatorInterface& lhs, const ActuatorInterface& rhs) {
  return std::make_tuple(lhs.getMotor(), lhs.getOptions()) == std::make_tuple(rhs.getMotor(), rhs.getOptions());
}
}  // namespace interfaces
