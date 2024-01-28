#ifndef CORE_TASK_CONFIG_HARDWARE_CONFIG_H
#define CORE_TASK_CONFIG_HARDWARE_CONFIG_H

#include <stdint.h>
#include <utility>

namespace config {
struct PinAssignment {
  uint8_t encoder_1_a_pin;
  uint8_t encoder_1_b_pin;
  uint8_t encoder_2_a_pin;
  uint8_t encoder_2_b_pin;
  uint8_t led_pin;
  uint8_t motor_b_pwm_pin;
  uint8_t motor_b_input_1_pin;
  uint8_t motor_b_input_2_pin;
  uint8_t motor_standby_pin;
};

PinAssignment loadPinAssignment();
}  // namespace config
#endif  // CORE_TASK_CONFIG_HARDWARE_CONFIG_H
