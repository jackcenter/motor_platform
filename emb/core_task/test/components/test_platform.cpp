#include "../../src/components/platform.h"

#include <gtest/gtest.h>

#include "../../src/actuators/brushed_motor.h"
#include "../../src/interfaces/actuator_interface.h"
#include "../../src/interfaces/sensor_interface.h"
#include "../../src/sensors/quadrature_encoder.h"
#include "../../src/types/input.h"
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
  const interfaces::ActuatorInterface actuator_interface{motor, actuator_interface_options};

  const PlatformOptions platform_interface_options{};
  return Platform{actuator_interface, sensor_interface, platform_interface_options};
}

types::Input getDefaultInput()
{
  types::Input input{};
  input.header.sequence = 0;
  input.header.timestamp.microseconds = 1;
  input.voltage = 3.4;

  return input;
}

types::Measurement getDefaultMeasurement()
{
  types::Measurement measurement{};
  measurement.header.sequence = 0;
  measurement.header.timestamp.microseconds = 1;
  measurement.encoder_1_pos = -300;
  measurement.encoder_2_pos = 400;

  return measurement;
}

TEST(Platform, Construction) { Platform platform{getDefaultPlatform()}; }

TEST(Platform, UpdateMeasurement) {
  Platform platform{getDefaultPlatform()};

  ASSERT_EQ(types::Status::OKAY, platform.open());
  EXPECT_EQ(types::Measurement{}, platform.readMeasurement(types::Timestamp{}));

  const types::Measurement default_measurement{ getDefaultMeasurement() };
  ASSERT_EQ(types::Status::OKAY, platform.write(getDefaultMeasurement()));
  EXPECT_EQ(default_measurement, platform.readMeasurement(default_measurement.header.timestamp));
  
  ASSERT_EQ(types::Status::OKAY, platform.close());
  EXPECT_EQ(types::Measurement{}, platform.readMeasurement(types::Timestamp{}));
}

TEST(Platform, UpdateInput) {
  Platform platform{getDefaultPlatform()};
  
  ASSERT_EQ(types::Status::OKAY, platform.open());
  EXPECT_EQ(types::Input{}, platform.readInput());
  ASSERT_EQ(types::Status::OKAY, platform.write(getDefaultInput()));
  EXPECT_EQ(getDefaultInput(), platform.readInput());
  ASSERT_EQ(types::Status::OKAY, platform.close());
  EXPECT_EQ(types::Input{}, platform.readInput());
}

}  // namespace components
