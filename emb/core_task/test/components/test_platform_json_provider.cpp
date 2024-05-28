#include "../../src/components/platform_json_provider.h"

#include <ArduinoJson.h>
#include <gtest/gtest.h>

#include "../../src/components/platform.h"
#include "../../src/actuators/brushed_motor.h"
#include "../../src/interfaces/actuator_interface.h"
#include "../../src/interfaces/sensor_interface.h"
#include "../../src/sensors/quadrature_encoder.h"

namespace components {
TEST(PlatformJsonProvider, ReturnsExpectedPlatform) {
  const double min_voltage{1.0};
  const double max_voltage{2.0};
  const double voltage_multiplier{3.0};

  JsonDocument temp_doc{};
  temp_doc["platform"]["actuator_interface"]["motor"]["options"]["min_voltage"] = min_voltage;
  temp_doc["platform"]["actuator_interface"]["motor"]["options"]["max_voltage"] = max_voltage;
  temp_doc["platform"]["actuator_interface"]["motor"]["options"]["voltage_multiplier"] = voltage_multiplier;

  const JsonDocument doc{temp_doc};
  PlatformJsonProvider provider{};
  Platform platform_from_json{provider.provide(doc["platform"])};

  sensors::QuadratureEncoderOptions encoder_1_options{};
  sensors::QuadratureEncoder encoder_1{encoder_1_options};

  sensors::QuadratureEncoderOptions encoder_2_options{};
  sensors::QuadratureEncoder encoder_2{encoder_2_options};

  interfaces::SensorInterfaceOptions sensor_interface_options{};
  interfaces::SensorInterface sensor_interface{encoder_1, encoder_2, sensor_interface_options};

  actuators::BrushedMotorOptions motor_options{};
  motor_options.voltage_range.first = min_voltage;
  motor_options.voltage_range.second = max_voltage;
  motor_options.voltage_multiplier = voltage_multiplier;
  actuators::BrushedMotor motor{motor_options};

  interfaces::ActuatorInterfaceOptions actuator_interface_options{};
  interfaces::ActuatorInterface actuator_interface{motor, actuator_interface_options};

  PlatformOptions platform_options{};
  Platform expected_platform{actuator_interface, sensor_interface, platform_options};

  EXPECT_EQ(expected_platform, platform_from_json);
}
}