#include "actuator_interface.h"

#include <Arduino.h>

#include <cmath>
#include <tuple>
#include <unordered_map>
#include <utility>

#include "../hardware/tb6612fng.h"
#include "../types/common.h"
#include "../types/input.h"
#include "../types/status.h"
#include "../utilities/common.h"

namespace interfaces {
bool operator==(const ActuatorInterfaceOptions& lhs, const ActuatorInterfaceOptions& rhs) {
  return lhs.voltage_range == rhs.voltage_range;
}

ActuatorInterace::ActuatorInterace(const hardware::Tb6612fng& tb6612fng, const ActuatorInterfaceOptions& options)
    : tb6612fng_{tb6612fng}, options_{options} {}

types::Status ActuatorInterace::operator()(const types::Input& input) const {
  static std::unordered_map<int, std::pair<bool, bool>> input_map{
      {1, {true, false}}, {0, {false, true}}, {-1, {false, true}}};

  if (!utilities::isInRange(input.voltage, options_.voltage_range.first, options_.voltage_range.second)) {
    return types::Status::OUT_OF_RANGE;
  }

  const std::pair<bool, bool> input_pair{input_map[utilities::getSign(input.voltage)]};

  const int pwm_value{(utilities::remap<double, int>(
      std::abs(input.voltage), tb6612fng_.getOptions().voltage_range.first,
      tb6612fng_.getOptions().voltage_range.second, tb6612fng_.getOptions().pwm_range.first,
      tb6612fng_.getOptions().pwm_range.second))};

  tb6612fng_.write(types::Channel::B, input_pair.first, input_pair.second, pwm_value);
  return types::Status::OKAY;
}

void ActuatorInterace::activate() const { tb6612fng_.open(); }

void ActuatorInterace::deactivate() const { tb6612fng_.close(); }

const hardware::Tb6612fng& ActuatorInterace::getTb6612fng() const { return tb6612fng_; }

const ActuatorInterfaceOptions& ActuatorInterace::getOptions() const { return options_; }

bool operator==(const ActuatorInterace& lhs, const ActuatorInterace& rhs) {
  return std::tuple(lhs.getTb6612fng(), lhs.getOptions()) == std::tuple(rhs.getTb6612fng(), rhs.getOptions());
}
}  // namespace interfaces