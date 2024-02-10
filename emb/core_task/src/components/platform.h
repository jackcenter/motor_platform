#ifndef COMPONENTS_PLATFORM
#define COMPONENTS_PLATFORM

#include "../interfaces/actuator_interface.h"
#include "../interfaces/sensor_interface.h"
#include "../types/input.h"
#include "../types/status.h"

namespace components {
struct PlatformOptions {};

bool operator==(const PlatformOptions& lhs, const PlatformOptions& rhs);

class Platform {
 public:
  Platform(const interfaces::ActuatorInterface& actuator_interface, const interfaces::SensorInterface& sensor_interface,
           const PlatformOptions& options);

  types::Status close();
  types::Status open();
  types::Input readInput() const;
  types::Measurement readMeasurement(const types::Timestamp& timestamp) const;
  types::Status write(const types::Input& input);
  types::Status write(const types::Measurement& measurement);

  const interfaces::ActuatorInterface& getActuatorInterface() const;
  const interfaces::SensorInterface& getSensorInterface() const;
  const PlatformOptions& getOptions() const;

 private:
  interfaces::ActuatorInterface actuator_interface_;
  interfaces::SensorInterface sensor_interface_;
  PlatformOptions options_;
};

bool operator==(const Platform& lhs, const Platform& rhs);
}  // namespace components

#endif  // COMPONENTS_PLATFORM
