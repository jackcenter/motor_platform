#include "teleop.h"

#include "../types/input.h"
#include "../types/measurement.h"
#include "../types/status.h"

namespace applications {
Teleop::Teleop(interfaces::PlatformInterface& platform_interface) : platform_interface_{platform_interface} {}

// cppcheck-suppress unusedFunction
types::Status Teleop::cycle() {
  const types::Measurement measurement{platform_interface_.read()};
  const double reference = measurement.encoder_2_pos;
  const double error = measurement.encoder_1_pos - reference;

  types::Input input{};
  input.voltage = 0.001 * error;

  const types::Status result{platform_interface_.write(input)};
  if (result != types::Status::OKAY) {
    return result;
  }

  state_.input = input;
  state_.measurement = measurement;

  return types::Status::OKAY;
}

// cppcheck-suppress unusedFunction
const TeleopState& Teleop::getState() const { return state_; }
}  // namespace applications
