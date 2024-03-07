#ifndef INTERFACES_PLATFORM_INTERFACE
#define INTERFACES_PLATFORM_INTERFACE

#include "actuator_interface.h"
#include "sensor_interface.h"
#include "../types/measurement.h"
#include "../types/status.h"

namespace interfaces {
struct PlatformInterfaceOptions {};

bool operator==(const PlatformInterfaceOptions& lhs, const PlatformInterfaceOptions& rhs);

class PlatformInterface {
 public:
  PlatformInterface(const interfaces::ActuatorInterace& actuator_interface,
                    interfaces::SensorInterface& sensor_interface, const PlatformInterfaceOptions& options);

  void close();
  void open();
  types::Measurement read();
  types::Status write(const types::Input& input);

  const ActuatorInterace& getActuatorInterface() const;
  const SensorInterface& getSensorInterface() const;
  const PlatformInterfaceOptions& getOptions() const;

 private:
  ActuatorInterace actuator_interface_;
  SensorInterface sensor_interface_;
  PlatformInterfaceOptions options_;
};

bool operator==(const PlatformInterface& lhs, const PlatformInterface& rhs);
}  // namespace interfaces

#endif  // INTERFACES_PLATFORM_INTERFACE
