#include "tb6612fng.h"

#include <tuple>

#include <Arduino.h>

#include "../types/status.h"
#include "../types/common.h"

namespace hardware {
bool operator==(const Tb6612fngOptions& lhs, const Tb6612fngOptions& rhs) {
  return std::tuple(lhs.AIN1, lhs.AIN2, lhs.BIN1, lhs.BIN2, lhs.pwm_range, lhs.PWMA, lhs.PWMB, lhs.STBY,
                    lhs.voltage_range) == std::tuple(rhs.AIN1, rhs.AIN2, rhs.BIN1, rhs.BIN2, rhs.pwm_range, rhs.PWMA,
                                                     rhs.PWMB, rhs.STBY, rhs.voltage_range);
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

const Tb6612fngOptions& Tb6612fng::getOptions() const { return options_; }

bool operator==(const Tb6612fng& lhs, const Tb6612fng& rhs) { return lhs.getOptions() == rhs.getOptions() }
}  // namespace hardware
