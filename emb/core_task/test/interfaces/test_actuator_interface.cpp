#include "../../src/interfaces/actuator_interface.h"

#include <gtest/gtest.h>

#include "../../src/types/input.h"
#include "../../src/types/status.h"

namespace interfaces {
ActuatorInterface getDefaultActuatorInterface()
{
  actuators::BrushedMotorOptions motor_options{};
  motor_options.voltage_range.first = -1.0;
  motor_options.voltage_range.second = 2.0;
  actuators::BrushedMotor motor{motor_options};

  ActuatorInterfaceOptions actuator_interface_options{};
  return ActuatorInterface{motor, actuator_interface_options};
}

TEST(ActuatorInterface, UpdatesCorrectly)
{
  ActuatorInterface actuator_interface{ getDefaultActuatorInterface() };
  EXPECT_FALSE(actuator_interface.isActive());

  {
    const types::Status result{actuator_interface.open()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
    EXPECT_EQ(types::Input{}, actuator_interface.read());
  }

  {
    types::Input input{};
    input.voltage = 1.0;
    const types::Status result{actuator_interface.write(input)};
    ASSERT_EQ(types::Status::OKAY, result) << result;
    EXPECT_EQ(input, actuator_interface.read());
  }

  {
    const types::Status result{actuator_interface.close()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
    EXPECT_EQ(types::Input{}, actuator_interface.read());
  }
}

TEST(ActuatorInterface, OpenFailsWhenAlreadyOpen)
{
  ActuatorInterface actuator_interface{ getDefaultActuatorInterface() };

  {
    const types::Status result{actuator_interface.open()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
  }

  {
    const types::Status result{actuator_interface.open()};
    EXPECT_EQ(types::Status::PRECONDITION_FAILED, result) << result;
  }
}

TEST(ActuatorInterface, CloseFailsWhenAlreadyClosed)
{
  ActuatorInterface actuator_interface{ getDefaultActuatorInterface() };

  {
    const types::Status result{actuator_interface.open()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
  }

  {
    const types::Status result{actuator_interface.close()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
  }

  {
    const types::Status result{actuator_interface.close()};
    EXPECT_EQ(types::Status::PRECONDITION_FAILED, result) << result;
  }
}

TEST(ActuatorInterface, WriteFailsWhenInactive)
{
  ActuatorInterface actuator_interface{ getDefaultActuatorInterface() };

  types::Input input{};
  input.voltage = 1.0;
  const types::Status result{actuator_interface.write(input)};
  EXPECT_EQ(types::Status::UNAVAILABLE, result) << result;
}

TEST(ActuatorInterface, WriteFailsWhenOutOfRange)
{
  ActuatorInterface actuator_interface{ getDefaultActuatorInterface() };

  {
    const types::Status result{actuator_interface.open()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
  }

  {
    types::Input input{};
    input.voltage = 3.0;
    const types::Status result{actuator_interface.write(input)};
    EXPECT_EQ(types::Status::OUT_OF_RANGE, result) << result;
  }

} 
} // interfaces
