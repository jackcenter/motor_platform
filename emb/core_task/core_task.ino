#include <ArduinoJson.h>
#include <Encoder.h>
#include "src/core_task.h"
#include "src/actuators/motor.h"
#include "src/config/hardware_config.h"
#include "src/config/hardware_limits.h"

struct State
{
  float count_A;
  float count_B;
};

const config::PinAssignment pin_assignment{config::loadPinAssignment()};
const config::HardwareLimits hardware_limits{config::loadHardwareLimits()};

Encoder enc_1{pin_assignment.encoder_1_a_pin, pin_assignment.encoder_1_b_pin};
Encoder enc_2{pin_assignment.encoder_2_a_pin, pin_assignment.encoder_2_b_pin};

actuators::MotorOptions motor_options{
    pin_assignment.motor_b_pwm_pin, pin_assignment.motor_b_input_1_pin,
    pin_assignment.motor_b_input_2_pin, pin_assignment.motor_standby_pin,
    hardware_limits.motor_b_pwm_range};
actuators::Motor motor{motor_options};

bool led_level = LOW;
bool motor_level = LOW;

// the setup routine runs once when you press reset:
void setup()
{
  // initialize the digital pin as an output.
  pinMode(pin_assignment.encoder_1_a_pin, INPUT_PULLUP);
  pinMode(pin_assignment.encoder_1_b_pin, INPUT_PULLUP);
  pinMode(pin_assignment.encoder_2_a_pin, INPUT_PULLUP);
  pinMode(pin_assignment.encoder_2_b_pin, INPUT_PULLUP);
  pinMode(pin_assignment.led_pin, OUTPUT);

  enc_1.write(0);
  enc_2.write(0);

  digitalWrite(pin_assignment.led_pin, led_level);

  motor.open();

  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop()
{
  digitalWrite(pin_assignment.led_pin, led_level);

  //  if (motor_level)
  //  {
  //    motor.write(HIGH, LOW, 100);
  //  }
  //  else
  //  {
  //    motor.write(LOW, LOW, 255);
  //  }
  motor.write(LOW, LOW, 255);

  State test_state;
  test_state.count_A = enc_1.read();
  test_state.count_B = enc_2.read();

  JsonDocument doc;
  doc["count_A"] = test_state.count_A;
  doc["count_B"] = test_state.count_B;

  serializeJson(doc, Serial);
  Serial.println();

  led_level = led_level ? LOW : HIGH;
  motor_level = motor_level ? LOW : HIGH;
  delay(1000); // wait for a second
}