#include "../../src/applications/teleop.h"

#include <ArduinoJson.h>
#include <gtest/gtest.h>

#include "../../src/actuators/brushed_motor.h"
#include "../../src/components/controller.h"
#include "../../src/components/platform.h"
#include "../../src/components/state_estimation.h"
#include "../../src/interfaces/actuator_interface.h"
#include "../../src/interfaces/sensor_interface.h"
#include "../../src/sensors/quadrature_encoder.h"
#include "../../src/types/input.h"
#include "../../src/types/measurement.h"
#include "../../src/types/status.h"
#include "../../src/types/timestamp.h"

namespace applications {
Teleop getDefualtTelop() {
  sensors::QuadratureEncoderOptions encoder_1_options{};
  sensors::QuadratureEncoder encoder_1{encoder_1_options};

  sensors::QuadratureEncoderOptions encoder_2_options{};
  sensors::QuadratureEncoder encoder_2{encoder_2_options};

  interfaces::SensorInterfaceOptions sensor_interface_options{};
  interfaces::SensorInterface sensor_interface{encoder_1, encoder_2, sensor_interface_options};

  actuators::BrushedMotorOptions motor_options{};
  motor_options.voltage_multiplier = 1.0;
  motor_options.voltage_range.first = -5.0;
  motor_options.voltage_range.second = 5.0;
  actuators::BrushedMotor motor{motor_options};

  interfaces::ActuatorInterfaceOptions actuator_interface_options{};
  interfaces::ActuatorInterface actuator_interface{motor, actuator_interface_options};

  components::PlatformOptions platform_options{};
  components::Platform platform{actuator_interface, sensor_interface, platform_options};

  components::ControllerOptions controller_options{};
  controller_options.proportional_gain = 1.0;
  controller_options.integral_gain = 0.2;
  controller_options.derivative_gain = 0.3;
  controller_options.cycle_period_ms = 2.0;
  controller_options.input_range = {-5.0, 5.0};
  controller_options.deadband_range = {-0.00, 0.00};
  components::Controller controller{controller_options};

  components::StateEstimationOptions state_estimation_options{};
  state_estimation_options.joint_1_counts_per_revolution = 1000;
  state_estimation_options.joint_2_counts_per_revolution = 2000;
  components::StateEstimation state_estimation{state_estimation_options};

  TeleopOptions options{};
  return Teleop{platform, controller, state_estimation, options};
}

types::Measurement getDefualtMeasurement() {
  types::Measurement measurement{};
  measurement.header.sequence = 0;
  measurement.header.timestamp.microseconds = 2000;
  measurement.encoder_1_pos = -3;
  measurement.encoder_2_pos = 4;

  return measurement;
}

TEST(Teleop, Construction) { Teleop teleop_application{getDefualtTelop()}; }

TEST(Teleop, CycleProvidesCorretInput) {
  Teleop teleop_application{getDefualtTelop()};

  ASSERT_EQ(types::Status::OKAY, teleop_application.open());
  EXPECT_EQ(types::Input{}, teleop_application.read());

  ASSERT_EQ(types::Status::OKAY, teleop_application.write(getDefualtMeasurement()));
  EXPECT_EQ(types::Input{}, teleop_application.read());
  EXPECT_EQ(TeleopState{}, teleop_application.getState());

  types::Timestamp timestamp{};
  timestamp.microseconds = 4000;

  ASSERT_EQ(types::Status::OKAY, teleop_application.cycle(timestamp));

  const types::State state{teleop_application.getState().state};
  const types::Measurement measurement{teleop_application.getState().measurement};
  EXPECT_NE(TeleopState{}, teleop_application.getState());
  EXPECT_NE(0.0, teleop_application.read().voltage);
}
}  // namespace applications
