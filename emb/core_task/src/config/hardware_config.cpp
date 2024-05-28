#include "hardware_config.h"

#include <string>

#include <ArduinoJson.h>

namespace config {
JsonDocument loadHardwareConfig() {
  JsonDocument doc{};
  doc["button_1"]["options"]["debounce_delay_ms"] = 50;
  doc["button_1"]["options"]["pin"] = 2;
  doc["button_1"]["options"]["trigger"] = "rising";
  doc["button_2"]["options"]["debounce_delay_ms"] = 50;
  doc["button_2"]["options"]["pin"] = 3;
  doc["button_2"]["options"]["trigger"] = "rising";
  doc["encoder_1"]["channel_a"] = 9;
  doc["encoder_1"]["channel_b"] = 8;
  doc["encoder_2"]["channel_a"] = 10;
  doc["encoder_2"]["channel_b"] = 11;
  doc["led"]["pin"] = 13;
  doc["tb6612fng"]["options"]["motor_b_pwm_pin"] = 14;
  doc["tb6612fng"]["options"]["motor_b_input_2_pin"] = 16;
  doc["tb6612fng"]["options"]["motor_b_input_1_pin"] = 15;
  doc["tb6612fng"]["options"]["motor_standby_pin"] = 17;
  doc["tb6612fng"]["options"]["motor_a_input_1_pin"] = 0;
  doc["tb6612fng"]["options"]["motor_a_input_2_pin"] = 0;
  doc["tb6612fng"]["options"]["motor_a_pwm_pin"] = 0;
  doc["tb6612fng"]["options"]["pwm_range_min"] = 0;
  doc["tb6612fng"]["options"]["pwm_range_max"] = 255;
  doc["tb6612fng"]["options"]["voltage_range_min"] = 0.0;
  doc["tb6612fng"]["options"]["voltage_range_max"] = 5.0;

  return doc;
}
}  // namespace config
