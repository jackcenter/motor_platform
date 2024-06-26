#ifndef ACTUATORS_BRUSHED_MOTOR_H
#define ACTUATORS_BRUSHED_MOTOR_H

#include <tuple>

#include "../types/status.h"
namespace actuators {
struct BrushedMotorOptions {
  double voltage_multiplier{0.0};  // Allows user to change direction of rotation
  std::pair<double, double> voltage_range{0.0, 0.0};
};

bool operator==(const BrushedMotorOptions& lhs, const BrushedMotorOptions& rhs);

class BrushedMotor {
 public:
  BrushedMotor(const BrushedMotorOptions& options);

  types::Status close();
  types::Status open();
  types::Status write(const double input);

  const BrushedMotorOptions& getOptions() const;
  bool isActive() const;
  double read() const;

 private:
  BrushedMotorOptions options_;

  bool active_;
  double input_;
};

bool operator==(const BrushedMotor& lhs, const BrushedMotor& rhs);

}  // namespace actuators
#endif  // ACTUATORS_BRUSHED_MOTOR_H
