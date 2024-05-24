#include "brushed_motor.h"

#include "../types/input.h"
#include "../types/status.h"
#include "../utilities/common.h"

namespace actuators {
bool operator==(const BrushedMotorOptions& lhs, const BrushedMotorOptions& rhs) {
  return lhs.voltage_range == rhs.voltage_range;
}

BrushedMotor::BrushedMotor(const BrushedMotorOptions& options) : options_{options}, active_{false}, input_{0.0} {}

types::Status BrushedMotor::close() {
  if (!isActive()) {
    return types::Status::PRECONDITION_FAILED;
  }

  const types::Status write_status{write(0.0)};
  active_ = false;
  return write_status;
}

types::Status BrushedMotor::open() {
  if (isActive()) {
    return types::Status::PRECONDITION_FAILED;
  }

  active_ = true;
  const types::Status write_status{write(0.0)};
  return write_status;
}

types::Status BrushedMotor::write(const double input) {
  if (!isActive()) {
    return types::Status::UNAVAILABLE;
  }

  if (!utilities::isInRange(input, options_.voltage_range.first, options_.voltage_range.second)) {
    return types::Status::OUT_OF_RANGE;
  }
  input_ = options_.voltage_multiplier * input;

  return types::Status::OKAY;
}

const BrushedMotorOptions& BrushedMotor::getOptions() const { return options_; }

bool BrushedMotor::isActive() const { return active_; };

double BrushedMotor::read() const { return input_; }

bool operator==(const BrushedMotor& lhs, const BrushedMotor& rhs) {
  return std::make_tuple(lhs.getOptions(), lhs.isActive(), lhs.read()) ==
         std::make_tuple(rhs.getOptions(), rhs.isActive(), rhs.read());
}

}  // namespace actuators