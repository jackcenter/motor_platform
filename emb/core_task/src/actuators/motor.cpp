#include "motor.h"

#include <Arduino.h>

namespace actuators
{
  Motor::Motor(const MotorOptions& options) : options_{ options }
  {
    pinMode(options_.pwm_pin, OUTPUT);
    pinMode(options_.input_pin_1, OUTPUT);
    pinMode(options_.input_pin_2, OUTPUT);
    pinMode(options_.standby_pin, OUTPUT);
    
    digitalWrite(options_.standby_pin, LOW);
    digitalWrite(options_.input_pin_1, LOW);
    digitalWrite(options_.input_pin_2, LOW);
    analogWrite(options_.pwm_pin, options_.pwm_range.second);
  }
  
  void Motor::open()
  {
    digitalWrite(options_.standby_pin, HIGH);
  }
  
  void Motor::close()
  {
    digitalWrite(options_.standby_pin, LOW);
  }
  
  void Motor::read()
  {
  }
  
  void Motor::write(const int input_1, const int input_2, const int pwm_value)
  {
    digitalWrite(options_.input_pin_1, input_1);
    digitalWrite(options_.input_pin_2, input_2);
    analogWrite(options_.pwm_pin, pwm_value);
  }
  
  void Motor::ioctl()
  {
  }
  
}  // actuators