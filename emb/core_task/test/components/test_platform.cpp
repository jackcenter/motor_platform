#include "../../src/components/platform.h"

#include <gtest/gtest.h>

#include "../../src/actuators/brushed_motor.h"
#include "../../src/interfaces/actuator_interface.h"
#include "../../src/interfaces/sensor_interface.h"
#include "../../src/sensors/quadrature_encoder.h"
#include "../../src/types/measurement.h"

namespace components {
Platform getDefaultPlatform() {
  const sensors::QuadratureEncoderOptions encoder_1_options{};
  const sensors::QuadratureEncoder encoder_1{encoder_1_options};

  const sensors::QuadratureEncoderOptions encoder_2_options{};
  const sensors::QuadratureEncoder encoder_2{encoder_2_options};

  const interfaces::SensorInterfaceOptions sensor_interface_options{};
  const interfaces::SensorInterface sensor_interface{encoder_1, encoder_2, sensor_interface_options};

  actuators::BrushedMotorOptions motor_options{};
  motor_options.voltage_range.first = -5.0;
  motor_options.voltage_range.second = 5.0;
  const actuators::BrushedMotor motor{motor_options};

  const interfaces::ActuatorInterfaceOptions actuator_interface_options{};
  const interfaces::ActuatorInterace actuator_interface{motor, actuator_interface_options};

  const PlatformOptions platform_interface_options{};
  return Platform{actuator_interface, sensor_interface, platform_interface_options};
}

TEST(Platform, Construction) { Platform platform{getDefaultPlatform()}; }

TEST(Platform, UpdateMeasurement) {
  Platform platform{getDefaultPlatform()};

  types::Measurement measurement;
  measurement.header = {};
  measurement.encoder_1_pos = 100;
  measurement.encoder_2_pos = -200;
  types::Status result{platform.write(measurement)};
  ASSERT_EQ(types::Status::OKAY, result);

  types::Measurement read_measurement{platform.readMeasurement()};
  EXPECT_EQ(measurement, read_measurement);
}

}  // namespace components
