
#include "src/core_task.h"

#include <unordered_map>

#include <Arduino.h>
#include <ArduinoJson.h>

#include "src/actuator_interface.h"
#include "src/config/hardware_config.h"
#include "src/config/hardware_limits.h"
#include "src/hardware/tb6612fng.h"
#include "src/hardware/quadrature_encoder.h"
#include "src/sensor_interface.h"
#include "src/types/input.h"
#include "src/types/measurement.h"
#include "src/types/status.h"
#include "src/utilities/serialize.h"

struct State
{
  float count_A;
  float count_B;
};

int main()
{
  const config::PinAssignment pin_assignment{config::loadPinAssignment()};
  const config::HardwareLimits hardware_limits{config::loadHardwareLimits()};

  hardware::QuadratureEncoderOptions encoder_1_options{};
  encoder_1_options.CH_A = pin_assignment.encoder_1_a_pin;
  encoder_1_options.CH_B = pin_assignment.encoder_1_b_pin;

  hardware::QuadratureEncoderOptions encoder_2_options{};
  encoder_2_options.CH_A = pin_assignment.encoder_2_a_pin;
  encoder_2_options.CH_B = pin_assignment.encoder_2_b_pin;
  
  SensorInterfaceOptions sensor_interface_options{};
  SensorInterface sensor_interface{ encoder_1_options, 
                                    encoder_2_options,
                                    sensor_interface_options};

  hardware::Tb6612fngOptions tb6612fng_options;
  tb6612fng_options.PWMB = pin_assignment.motor_b_pwm_pin;
  tb6612fng_options.BIN2 = pin_assignment.motor_b_input_2_pin;
  tb6612fng_options.BIN1 = pin_assignment.motor_b_input_1_pin;
  tb6612fng_options.STBY = pin_assignment.motor_standby_pin;

  hardware::Tb6612fng tb6612fng{ tb6612fng_options };

  ActuatorInterfaceOptions actuator_interface_options{};
  actuator_interface_options.voltage_range = { -5.0, 5.0 };

  ActuatorInterace actuator_interface{ tb6612fng, actuator_interface_options };

  pinMode(pin_assignment.led_pin, OUTPUT);

  actuator_interface.activate();

  Serial.begin(9600);

  bool led_level = LOW;
  int motor_level = 0;

  for(;;)
  {
    static std::unordered_map<int,double> motor_voltage_map{
      {0, 0.0},
      {1, 2.0},
      {2, 4.0},
      {3, 2.0},
      {4, 0.0},
      {5, -2.0},
      {6, -4.0},
      {7, -2.0}
    };

    types::Input input{};
    input.voltage = motor_voltage_map[ motor_level % 8 ];

    types::Status result { actuator_interface(input) };
    // TODO: check the result

    types::Measurement measurement{ sensor_interface() };

    JsonDocument doc1{};
    doc1["input"] = utilities::serialize(input);
    serializeJson(doc1, Serial);
    Serial.println();

    JsonDocument doc2{};
    doc2["measurement"] = utilities::serialize(measurement);
    serializeJson(doc2, Serial);
    Serial.println();

    led_level = led_level ? LOW : HIGH;
    ++motor_level;
    delay(1000); // wait for a second
    yield();
  }

  return 0;
}
