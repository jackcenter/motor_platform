#include "../../src/actuators/brushed_motor.h"

#include <gtest/gtest.h>

#include "../../src/types/status.h"

namespace actuators {
BrushedMotor getDefaultMotor() {
  BrushedMotorOptions motor_options{};
  motor_options.voltage_multiplier = 1.0;
  motor_options.voltage_range.first = -1.0;
  motor_options.voltage_range.second = 2.0;

  return BrushedMotor{motor_options};
}

TEST(BrushedMotor, UpdatesCorrectly) {
  BrushedMotor motor{getDefaultMotor()};

  {
    const types::Status result{motor.open()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
    EXPECT_EQ(0.0, motor.read());
  }

  {
    const types::Status result{motor.write(1.0)};
    ASSERT_EQ(types::Status::OKAY, result) << result;
    EXPECT_EQ(1.0, motor.read());
  }

  {
    const types::Status result{motor.close()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
    EXPECT_EQ(0.0, motor.read());
  }
}

TEST(BrushedMotor, MotorMultiplierModifiesVoltage) {
  BrushedMotorOptions modified_motor_options{};
  modified_motor_options.voltage_multiplier = -1.0;
  modified_motor_options.voltage_range.first = -1.0;
  modified_motor_options.voltage_range.second = 2.0;
  
  BrushedMotor modified_motor{modified_motor_options};
  ASSERT_EQ(types::Status::OKAY, modified_motor.open());
  ASSERT_EQ(types::Status::OKAY, modified_motor.write(1.0));
  EXPECT_FLOAT_EQ(-1.0, modified_motor.read());
}

TEST(BrushedMotor, OpenFailsWhenAlreadyOpen) {
  BrushedMotor motor{getDefaultMotor()};

  {
    const types::Status result{motor.open()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
  }

  {
    const types::Status result{motor.open()};
    EXPECT_EQ(types::Status::PRECONDITION_FAILED, result) << result;
  }
}

TEST(BrushedMotor, CloseFailsWhenAlreadyClosed) {
  BrushedMotor motor{getDefaultMotor()};

  {
    const types::Status result{motor.open()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
  }

  {
    const types::Status result{motor.close()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
  }

  {
    const types::Status result{motor.close()};
    EXPECT_EQ(types::Status::PRECONDITION_FAILED, result) << result;
  }
}

TEST(BrushedMotor, WriteFailsWhenInactive) {
  BrushedMotor motor{getDefaultMotor()};

  const types::Status result{motor.write(1.0)};
  EXPECT_EQ(types::Status::UNAVAILABLE, result) << result;
}

TEST(BrushedMotor, WriteFailsWhenOutOfRange) {
  BrushedMotor motor{getDefaultMotor()};

  {
    const types::Status result{motor.open()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
  }

  {
    const types::Status result{motor.write(3.0)};
    EXPECT_EQ(types::Status::OUT_OF_RANGE, result) << result;
  }
}
}  // namespace actuators