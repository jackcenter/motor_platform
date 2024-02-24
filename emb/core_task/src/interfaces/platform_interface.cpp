#include "platform_interface.h"

#include "actuator_interface.h"
#include "sensor_interface.h"
#include "../types/input.h"
#include "../types/measurement.h"
#include "../types/status.h"

namespace interfaces {
bool operator==(const PlatformInterfaceOptions& lhs, const PlatformInterfaceOptions& rhs) { return true; }

PlatformInterface::PlatformInterface(const interfaces::ActuatorInterace& actuator_interface,
                                     interfaces::SensorInterface& sensor_interface,
                                     const PlatformInterfaceOptions& options)
    : actuator_interface_{actuator_interface}, sensor_interface_{sensor_interface}, options_{options} {
  actuator_interface.activate();
}

void PlatformInterface::close() { actuator_interface_.deactivate(); }

void PlatformInterface::open() { actuator_interface_.activate(); }

types::Measurement PlatformInterface::read() { return types::Measurement{sensor_interface_()}; }

types::Status PlatformInterface::write(const types::Input& input) {
  const types::Status result{actuator_interface_(input)};
  if (result != types::Status::OKAY) {
    close();
    return result;
  }

  return types::Status::OKAY;
}

const ActuatorInterace& PlatformInterface::getActuatorInterface() const {return actuator_interface_};

const SensorInterface& PlatformInterface::getSensorInterface() const {return sensor_interface_};

const PlatformInterfaceOptions& PlatformInterface::getOptions() const {return options_};

bool operator==(const PlatformInterface& lhs, const PlatformInterface& rhs) { return lhs. }
}  // namespace interfaces