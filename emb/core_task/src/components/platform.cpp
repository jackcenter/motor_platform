#include "platform.h"

#include <tuple>

#include "../interfaces/actuator_interface.h"
#include "../interfaces/sensor_interface.h"
#include "../types/input.h"
#include "../types/measurement.h"
#include "../types/status.h"

namespace components {
bool operator==(const PlatformOptions& lhs, const PlatformOptions& rhs) { return true; }

Platform::Platform(const interfaces::ActuatorInterace& actuator_interface,
                   const interfaces::SensorInterface& sensor_interface, const PlatformOptions& options)
    : actuator_interface_{actuator_interface}, sensor_interface_{sensor_interface}, options_{options} {}

void Platform::close() { actuator_interface_.deactivate(); }

void Platform::open() { actuator_interface_.activate(); }

types::Input Platform::readInput() const { return actuator_interface_.read(); }

types::Measurement Platform::readMeasurement() const { return sensor_interface_.read(); }

types::Status Platform::write(const types::Input& input) { return actuator_interface_.write(input); }

types::Status Platform::write(const types::Measurement& measurement) { return sensor_interface_.write(measurement); }

const interfaces::ActuatorInterace& Platform::getActuatorInterface() const { return actuator_interface_; }

const interfaces::SensorInterface& Platform::getSensorInterface() const { return sensor_interface_; }

const PlatformOptions& Platform::getOptions() const { return options_; }

bool operator==(const Platform& lhs, const Platform& rhs) {
  return std::make_tuple(lhs.getActuatorInterface(), lhs.getSensorInterface(), lhs.getOptions()) ==
         std::make_tuple(rhs.getActuatorInterface(), rhs.getSensorInterface(), rhs.getOptions());
}
}  // namespace components
