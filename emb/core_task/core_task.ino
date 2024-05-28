#include <cmath>
#include <string>
#include <utility>

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Encoder.h>

#include "src/applications/teleop.h"
#include "src/components/controller.h"
#include "src/components/platform.h"
#include "src/components/platform_json_provider.h"
#include "src/components/state_estimation.h"
#include "src/config/hardware_config.h"
#include "src/config/platform_config.h"
#include "src/hardware/tb6612fng.h"
#include "src/hardware/button.h"
#include "src/types/common.h"
#include "src/types/status.h"
#include "src/types/timestamp.h"
#include "src/utilities/serialize.h"

volatile bool PRINT_FLAG{false};

int main() {
  const unsigned long control_cycle_period_ms{2};

  IntervalTimer print_timer;
  print_timer.begin(setPrintFlag, 1e5);

  config::PinAssignment pin_assignment{config::loadPinAssignment()};
  Encoder encoder_1{pin_assignment.encoder_1_a_pin, pin_assignment.encoder_1_b_pin};
  Encoder encoder_2{pin_assignment.encoder_2_a_pin, pin_assignment.encoder_2_b_pin};

  hardware::Tb6612fngOptions tb6612fng_options{};
  tb6612fng_options.PWMB = pin_assignment.motor_b_pwm_pin;
  tb6612fng_options.BIN2 = pin_assignment.motor_b_input_2_pin;
  tb6612fng_options.BIN1 = pin_assignment.motor_b_input_1_pin;
  tb6612fng_options.STBY = pin_assignment.motor_standby_pin;
  tb6612fng_options.AIN1 = pin_assignment.motor_a_input_1_pin;
  tb6612fng_options.AIN2 = pin_assignment.motor_a_input_2_pin;
  tb6612fng_options.PWMA = pin_assignment.motor_a_pwm_pin;
  tb6612fng_options.pwm_range = {0, 255};
  tb6612fng_options.voltage_range = {0.0, 5.0};
  hardware::Tb6612fng tb6612fng{tb6612fng_options};
  tb6612fng.open();

  pinMode(pin_assignment.led_pin, OUTPUT);
  bool led_level = false;

  JsonDocument config{config::getPlatformConfig()};
  components::PlatformJsonProvider platform_json_provider{};
  components::Platform platform{platform_json_provider.provide(config)};

  components::ControllerOptions controller_options{};
  controller_options.proportional_gain = 1.0;
  controller_options.integral_gain = 0.01;
  controller_options.derivative_gain = 0.5;
  controller_options.cycle_period_ms = control_cycle_period_ms;
  controller_options.input_range = {-5.0, 5.0};
  components::Controller controller{controller_options};

  components::StateEstimationOptions state_estimation_options{};
  state_estimation_options.joint_1_rad_per_count = (2.0 * M_PI) / 8400.0;
  state_estimation_options.joint_2_rad_per_count = (2.0 * M_PI) / 2400.0;
  components::StateEstimation state_estimation{state_estimation_options};

  applications::TeleopOptions teleop_options{};
  applications::Teleop teleop_application{platform, controller, state_estimation, teleop_options};

  hardware::ButtonOptions red_button_options{};
  red_button_options.debounce_delay_ms = 50;
  red_button_options.pin = 2;
  red_button_options.trigger = hardware::SignalState::kRising;
  hardware::Button red_button{red_button_options};

  hardware::ButtonOptions black_button_options{};
  black_button_options.debounce_delay_ms = 50;
  black_button_options.pin = 3;
  black_button_options.trigger = hardware::SignalState::kRising;
  hardware::Button black_button{black_button_options};

  Serial.begin(9600);

  for (;;) {
    types::Timestamp cycle_start_timestamp{micros()};
    digitalWrite(pin_assignment.led_pin, led_level);
    led_level = led_level ? false : true;

    types::Measurement measurement_update;
    measurement_update.encoder_1_pos = encoder_1.read();
    measurement_update.encoder_2_pos = encoder_2.read();
    measurement_update.header.timestamp = cycle_start_timestamp;

    teleop_application.write(measurement_update);

    if (red_button() && teleop_application.isActive()) {
      teleop_application.close();
    }

    if (black_button() && !teleop_application.isActive()) {
      teleop_application.open();
    }

    teleop_application.cycle(cycle_start_timestamp);
    const types::Input input_update{teleop_application.read()};

    tb6612fng.write(types::Channel::B, input_update.voltage);

    if (PRINT_FLAG && teleop_application.isActive()) {
      applications::TeleopState teleop_state{teleop_application.getState()};

      JsonDocument doc1{};
      doc1["input"] = utilities::serialize(teleop_state.input);
      serializeJson(doc1, Serial);
      Serial.println();

      JsonDocument doc2{};
      doc2["measurement"] = utilities::serialize(teleop_state.measurement);
      serializeJson(doc2, Serial);
      Serial.println();

      JsonDocument doc3{};
      doc3["state"] = utilities::serialize(teleop_state.state);
      serializeJson(doc3, Serial);
      Serial.println();

      PRINT_FLAG = false;
    }

    const unsigned long current_cycle_duration_ms{millis() - cycle_start_timestamp.toMilliseconds()};
    if ((current_cycle_duration_ms) < control_cycle_period_ms) {
      const unsigned long cycle_time_remaining_ms{control_cycle_period_ms - current_cycle_duration_ms};
      delay(cycle_time_remaining_ms);
    }

    yield();
  }

  return 0;
}

void setPrintFlag() { PRINT_FLAG = true; }
