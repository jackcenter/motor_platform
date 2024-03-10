#include "platform_json_provider.h"

#include <ArduinoJson.h>

#include "../config/hardware_config.h"
#include "../interfaces/actuator_interface.h"
#include "../interfaces/sensor_interface.h"
#include "platform.h"

namespace components {
// cppcheck-suppress unusedFunction
Platform PlatformJsonProvider::provide(const JsonDocument& doc) const {
  sensors::QuadratureEncoderOptions encoder_1_options{};
  sensors::QuadratureEncoder encoder_1{encoder_1_options};

  sensors::QuadratureEncoderOptions encoder_2_options{};
  sensors::QuadratureEncoder encoder_2{encoder_2_options};

  interfaces::SensorInterfaceOptions sensor_interface_options{};
  interfaces::SensorInterface sensor_interface{encoder_1, encoder_2, sensor_interface_options};

  interfaces::ActuatorInterfaceOptions actuator_interface_options{};

  actuators::BrushedMotorOptions motor_options{};
  motor_options.voltage_range.first = doc["platform"]["actuator_interface"]["motor"]["options"]["min_voltage"];
  motor_options.voltage_range.second = doc["platform"]["actuator_interface"]["motor"]["options"]["max_voltage"];
  actuators::BrushedMotor motor{motor_options};

  interfaces::ActuatorInterace actuator_interface{motor, actuator_interface_options};

  const PlatformOptions platform_interface_options{};
  return Platform{actuator_interface, sensor_interface, platform_interface_options};
}
}  // namespace components
