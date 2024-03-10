#include "tb6612fng.h"

#include <cmath>
#include <tuple>
#include <map>

#include <Arduino.h>

#include "../types/status.h"
#include "../types/common.h"
#include "../utilities/common.h"

namespace hardware {
bool operator==(const Tb6612fngOptions& lhs, const Tb6612fngOptions& rhs) {
  return std::make_tuple(lhs.AIN1, lhs.AIN2, lhs.BIN1, lhs.BIN2, lhs.pwm_range, lhs.PWMA, lhs.PWMB, lhs.STBY,
                         lhs.voltage_range) == std::make_tuple(rhs.AIN1, rhs.AIN2, rhs.BIN1, rhs.BIN2, rhs.pwm_range,
                                                               rhs.PWMA, rhs.PWMB, rhs.STBY, rhs.voltage_range);
}

Tb6612fng::Tb6612fng(const Tb6612fngOptions& options) : options_{options} {
  pinMode(options_.PWMB, OUTPUT);
  pinMode(options_.BIN2, OUTPUT);
  pinMode(options_.BIN1, OUTPUT);
  pinMode(options_.STBY, OUTPUT);
  pinMode(options_.AIN1, OUTPUT);
  pinMode(options_.AIN2, OUTPUT);
  pinMode(options_.PWMA, OUTPUT);

  analogWrite(options_.PWMB, options_.pwm_range.second);
  digitalWrite(options_.BIN2, LOW);
  digitalWrite(options_.BIN1, LOW);
  digitalWrite(options_.STBY, LOW);
  digitalWrite(options_.AIN1, LOW);
  digitalWrite(options_.AIN2, LOW);
  analogWrite(options_.PWMA, options_.pwm_range.second);
}

void Tb6612fng::open() const { digitalWrite(options_.STBY, HIGH); }

void Tb6612fng::close() const { digitalWrite(options_.STBY, LOW); }

uint8_t Tb6612fng::read() const { return digitalRead(options_.STBY); }

types::Status Tb6612fng::write(const types::Channel channel, const bool input_1, const bool input_2,
                               const int pwm_value) const {
  if (!read()) {
    return types::Status::UNAVAILABLE;
  }

  if (pwm_value < options_.pwm_range.first || options_.pwm_range.second < pwm_value) {
    return types::Status::OUT_OF_RANGE;
  }

  switch (channel) {
    case types::Channel::A:
      digitalWrite(options_.AIN1, input_1);
      digitalWrite(options_.AIN2, input_2);
      analogWrite(options_.PWMA, static_cast<uint8_t>(pwm_value));
      return types::Status::OKAY;
    case types::Channel::B:
      digitalWrite(options_.BIN1, input_1);
      digitalWrite(options_.BIN2, input_2);
      analogWrite(options_.PWMB, static_cast<uint8_t>(pwm_value));
      return types::Status::OKAY;
    default:
      return types::Status::UNKNOWN;
  }
}

types::Status Tb6612fng::write(const types::Channel channel, const double voltage) {
  const double voltage_magnitude{std::fabs(voltage)};

  if (!utilities::isInRange(voltage_magnitude, options_.voltage_range.first, options_.voltage_range.second)) {
    return types::Status::OUT_OF_RANGE;
  }

  static std::map<Gear, std::pair<bool, bool>> input_map{{forward, std::pair<bool, bool>{HIGH, LOW}},
                                                         {neutral, std::pair<bool, bool>{LOW, HIGH}},
                                                         {reverse, std::pair<bool, bool>{LOW, HIGH}}};

  const Gear required_gear{getRequiredGear(voltage)};
  const std::pair<bool, bool> input_pair{input_map.at(required_gear)};

  const int pwm_value{(utilities::remap<double, int>(voltage_magnitude, getOptions().voltage_range.first,
                                                     getOptions().voltage_range.second, getOptions().pwm_range.first,
                                                     getOptions().pwm_range.second))};

  return write(channel, input_pair.first, input_pair.second, pwm_value);
}

const Tb6612fngOptions& Tb6612fng::getOptions() const { return options_; }

Gear Tb6612fng::getRequiredGear(const double voltage) const {
  switch (utilities::getSign(voltage)) {
    case 1:
      return forward;
    case 0:
      return neutral;
    case -1:
      return reverse;
    default:
      return neutral;
  }
}

bool operator==(const Tb6612fng& lhs, const Tb6612fng& rhs) { return lhs.getOptions() == rhs.getOptions(); }
}  // namespace hardware
