#ifndef MOTOR_PLATFORM_MOTOR_H
#define MOTOR_PLATFORM_MOTOR_H

#include <utility>

namespace actuators
{
struct MotorOptions
{
  int pwm_pin;
  int input_pin_1;
  int input_pin_2;
  int standby_pin;
  std::pair<int,int> pwm_range;
}; 

class Motor
{
public:
  Motor(const MotorOptions& options);
  
  void open();
  void close();
  void read();
  void write(const int input_1, const int input_2, const int pwm_value);
  void ioctl();

private:
  MotorOptions options_;
};
}  // actuators

#endif // MOTOR_PLATFORM_MOTOR_H