#include "tb6612fng_json_provider.h"

#include <ArduinoJson.h>

#include "tb6612fng.h"

namespace hardware {
Tb6612fngOptions Tb6612fngOptionsJsonProvider::provide(const JsonDocument& doc) const {
  Tb6612fngOptions options;
  options.PWMB = doc["motor_b_pwm_pin"];
  options.BIN2 = doc["motor_b_input_2_pin"];
  options.BIN1 = doc["motor_b_input_1_pin"];
  options.STBY = doc["motor_standby_pin"];
  options.AIN1 = doc["motor_a_input_1_pin"];
  options.AIN2 = doc["motor_a_input_2_pin"];
  options.PWMA = doc["motor_a_pwm_pin"];
  options.pwm_range = {doc["pwm_range_min"], doc["pwm_range_max"]};
  options.voltage_range = {doc["voltage_range_min"], doc["voltage_range_max"]};

  return options;
}

Tb6612fng Tb6612fngJsonProvider::provide(const JsonDocument& doc) const {
  Tb6612fngOptionsJsonProvider options_provider{};
  Tb6612fngOptions options{options_provider.provide(doc["options"])};
  return Tb6612fng{options};
}
}  // namespace hardware
