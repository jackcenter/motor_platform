#include "platform_interface_json_provider.h"

#include <ArduinoJson.h>

#include "actuator_interface.h"
#include "../config/hardware_config.h"
#include "platform_interface.h"
#include "sensor_interface.h"

// cppcheck-suppress unusedFunction
PlatformInterface PlatformInterfaceJsonProvider::provide(const JsonDocument& doc) const {
  const config::PinAssignment pin_assignment{config::loadPinAssignment()};

  hardware::QuadratureEncoderOptions encoder_1_options{};
  encoder_1_options.CH_A = pin_assignment.encoder_1_a_pin;
  encoder_1_options.CH_B = pin_assignment.encoder_1_b_pin;
  hardware::QuadratureEncoder encoder_1{encoder_1_options};

  hardware::QuadratureEncoderOptions encoder_2_options{};
  encoder_2_options.CH_A = pin_assignment.encoder_2_a_pin;
  encoder_2_options.CH_B = pin_assignment.encoder_2_b_pin;
  hardware::QuadratureEncoder encoder_2{encoder_2_options};

  interfaces::SensorInterfaceOptions sensor_interface_options{};
  interfaces::SensorInterface sensor_interface{std::move(encoder_1), std::move(encoder_2), sensor_interface_options};

  hardware::Tb6612fngOptions tb6612fng_options;
  tb6612fng_options.PWMB = pin_assignment.motor_b_pwm_pin;
  tb6612fng_options.BIN2 = pin_assignment.motor_b_input_2_pin;
  tb6612fng_options.BIN1 = pin_assignment.motor_b_input_1_pin;
  tb6612fng_options.STBY = pin_assignment.motor_standby_pin;
  tb6612fng_options.AIN1 = pin_assignment.motor_a_input_1_pin;
  tb6612fng_options.AIN2 = pin_assignment.motor_a_input_2_pin;
  tb6612fng_options.PWMA = pin_assignment.motor_a_pwm_pin;

  hardware::Tb6612fng tb6612fng{tb6612fng_options};

  interfaces::ActuatorInterfaceOptions actuator_interface_options{};
  actuator_interface_options.voltage_range = {-5.0, 5.0};

  interfaces::ActuatorInterace actuator_interface{tb6612fng, actuator_interface_options};

  const PlatformInterfaceOptions platform_interface_options{};
  return PlatformInterface{actuator_interface, sensor_interface, platform_interface_options};
}