#include "hardware_config.h"

namespace config {
PinAssignment loadPinAssignment() {
  PinAssignment pin_assignment;
  pin_assignment.encoder_1_a_pin = 8;
  pin_assignment.encoder_1_b_pin = 9;
  pin_assignment.encoder_2_a_pin = 10;
  pin_assignment.encoder_2_b_pin = 11;
  pin_assignment.led_pin = 13;
  pin_assignment.motor_b_pwm_pin = 14;
  pin_assignment.motor_b_input_1_pin = 15;
  pin_assignment.motor_b_input_2_pin = 16;
  pin_assignment.motor_standby_pin = 17;

  return pin_assignment;
}
}  // namespace config
