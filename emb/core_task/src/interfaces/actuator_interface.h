#ifndef INTERFACE_ACTUATOR_INTERFACE_H
#define INTERFACE_ACTUATOR_INTERFACE_H

#include <utility>

#include "../actuators/brushed_motor.h"
#include "../types/common.h"
#include "../types/input.h"
#include "../types/status.h"

namespace interfaces {
struct ActuatorInterfaceOptions {};

bool operator==(const ActuatorInterfaceOptions& lhs, const ActuatorInterfaceOptions& rhs);

class ActuatorInterace {
 public:
  ActuatorInterace(const actuators::BrushedMotor& motor, const ActuatorInterfaceOptions& options);

  types::Input read() const;
  types::Status write(const types::Input& input);

  void activate();
  void deactivate();

  const actuators::BrushedMotor& getMotor() const;
  const ActuatorInterfaceOptions& getOptions() const;

 private:
  actuators::BrushedMotor motor_;
  ActuatorInterfaceOptions options_;
};

bool operator==(const ActuatorInterace& lsh, const ActuatorInterace& rhs);
}  // namespace interfaces
#endif  // INTERFAC_ACTUATOR_INTERFACE_H
