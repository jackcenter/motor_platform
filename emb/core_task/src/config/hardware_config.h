#ifndef CORE_TASK_CONFIG_HARDWARE_CONFIG_H
#define CORE_TASK_CONFIG_HARDWARE_CONFIG_H

#include <utility>

namespace config
{
struct PinAssignment
{ 
  int encoder_1_a_pin;
  int encoder_1_b_pin;
  int encoder_2_a_pin;
  int encoder_2_b_pin;
  int led_pin;
  int motor_b_pwm_pin;
  int motor_b_input_1_pin;
  int motor_b_input_2_pin;
  int motor_standby_pin;
};

PinAssignment loadPinAssignment();
}
#endif  // CORE_TASK_CONFIG_HARDWARE_CONFIG_H