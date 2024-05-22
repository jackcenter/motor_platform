#include "platform.h"

#include <tuple>

#include "../interfaces/actuator_interface.h"
#include "../interfaces/sensor_interface.h"
#include "../types/input.h"
#include "../types/measurement.h"
#include "../types/status.h"

namespace components {
bool operator==(const PlatformOptions& lhs, const PlatformOptions& rhs) { return true; }

Platform::Platform(const interfaces::ActuatorInterface& actuator_interface,
                   const interfaces::SensorInterface& sensor_interface, const PlatformOptions& options)
    : actuator_interface_{actuator_interface}, sensor_interface_{sensor_interface}, options_{options} {}

types::Status Platform::close() {
  const types::Status actuator_interface_result{actuator_interface_.close()};
  const types::Status sensor_interface_result{sensor_interface_.close()};

  if (types::Status::OKAY != actuator_interface_result) {
    return actuator_interface_result;
  }

  if (types::Status::OKAY != sensor_interface_result) {
    return sensor_interface_result;
  }

  return types::Status::OKAY;
}

types::Status Platform::open() {
  const types::Status actuator_interface_result{actuator_interface_.open()};
  if (types::Status::OKAY != actuator_interface_result) {
    close();
    return actuator_interface_result;
  }

  const types::Status sensor_interface_result{sensor_interface_.open()};
  if (types::Status::OKAY != sensor_interface_result) {
    close();
    return sensor_interface_result;
  }

  return types::Status::OKAY;
}

types::Input Platform::readInput() const { return actuator_interface_.read(); }

types::Measurement Platform::readMeasurement(const types::Timestamp& timestamp) const {
  return sensor_interface_.read(timestamp);
}

types::Status Platform::write(const types::Input& input) { return actuator_interface_.write(input); }

types::Status Platform::write(const types::Measurement& measurement) { return sensor_interface_.write(measurement); }

const interfaces::ActuatorInterface& Platform::getActuatorInterface() const { return actuator_interface_; }

const interfaces::SensorInterface& Platform::getSensorInterface() const { return sensor_interface_; }

const PlatformOptions& Platform::getOptions() const { return options_; }

bool operator==(const Platform& lhs, const Platform& rhs) {
  return std::make_tuple(lhs.getActuatorInterface(), lhs.getSensorInterface(), lhs.getOptions()) ==
         std::make_tuple(rhs.getActuatorInterface(), rhs.getSensorInterface(), rhs.getOptions());
}
}  // namespace components
