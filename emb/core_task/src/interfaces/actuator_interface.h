#ifndef INTERFACE_ACTUATOR_INTERFACE_H
#define INTERFACE_ACTUATOR_INTERFACE_H

#include <utility>

#include "../actuators/brushed_motor.h"
#include "../types/common.h"
#include "../types/input.h"
#include "../types/status.h"
#include "../types/timestamp.h"

namespace interfaces {
struct ActuatorInterfaceOptions {};

bool operator==(const ActuatorInterfaceOptions& lhs, const ActuatorInterfaceOptions& rhs);

class ActuatorInterface {
 public:
  ActuatorInterface(const actuators::BrushedMotor& motor, const ActuatorInterfaceOptions& options);

  types::Status open();
  types::Status close();
  types::Status write(const types::Input& input);

  const actuators::BrushedMotor& getMotor() const;
  const ActuatorInterfaceOptions& getOptions() const;
  bool isActive() const;
  types::Input read() const;

 private:
  actuators::BrushedMotor motor_;
  ActuatorInterfaceOptions options_;
  bool active_;
  types::Timestamp timestamp_;
};

bool operator==(const ActuatorInterface& lsh, const ActuatorInterface& rhs);
}  // namespace interfaces
#endif  // INTERFAC_ACTUATOR_INTERFACE_H
