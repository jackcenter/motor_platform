
#include <Arduino.h>
#include <ArduinoJson.h>
#include <Encoder.h>

#include "src/core_task.h"
#include "src/hardware/tb6612fng.h"
#include "src/config/hardware_config.h"
#include "src/config/hardware_limits.h"

struct State
{
  float count_A;
  float count_B;
};

int main()
{
  const config::PinAssignment pin_assignment{config::loadPinAssignment()};
  const config::HardwareLimits hardware_limits{config::loadHardwareLimits()};

  Encoder enc_1{pin_assignment.encoder_1_a_pin, pin_assignment.encoder_1_b_pin};
  Encoder enc_2{pin_assignment.encoder_2_a_pin, pin_assignment.encoder_2_b_pin};

  hardware::Tb6612fngOptions tb6612fng_options;
  tb6612fng_options.PWMB = pin_assignment.motor_b_pwm_pin;
  tb6612fng_options.BIN2 = pin_assignment.motor_b_input_2_pin;
  tb6612fng_options.BIN1 = pin_assignment.motor_b_input_1_pin;
  tb6612fng_options.STBY = pin_assignment.motor_standby_pin;

  hardware::Tb6612fng tb6612fng{ tb6612fng_options };

  // initialize the digital pin as an output.
  pinMode(pin_assignment.encoder_1_a_pin, INPUT_PULLUP);
  pinMode(pin_assignment.encoder_1_b_pin, INPUT_PULLUP);
  pinMode(pin_assignment.encoder_2_a_pin, INPUT_PULLUP);
  pinMode(pin_assignment.encoder_2_b_pin, INPUT_PULLUP);
  pinMode(pin_assignment.led_pin, OUTPUT);

  enc_1.write(0);
  enc_2.write(0);

  tb6612fng.open();

  Serial.begin(9600);

  bool led_level = LOW;
  bool motor_level = LOW;

  for(;;)
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
    tb6612fng.write(hardware::Channel::B, LOW, LOW, 255);

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
    yield();
  }

  return 0;
}
