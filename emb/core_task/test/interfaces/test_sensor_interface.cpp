#include "../../src/interfaces/sensor_interface.h"

#include <gtest/gtest.h>

#include "../../src/sensors/quadrature_encoder.h"
#include "../../src/types/measurement.h"
#include "../../src/types/status.h"

namespace interfaces {
SensorInterface getDefaultSensorInterface()
{
  sensors::QuadratureEncoderOptions encoder_1_options{};
  sensors::QuadratureEncoder encoder_1{encoder_1_options};

  sensors::QuadratureEncoderOptions encoder_2_options{};
  sensors::QuadratureEncoder encoder_2{encoder_2_options};

  SensorInterfaceOptions sensor_interface_options{};
  return SensorInterface{encoder_1, encoder_2, sensor_interface_options};
}

types::Measurement getDefaultMeasurement()
{
  types::Measurement measurement{};
  measurement.header.sequence = 0;
  measurement.header.timestamp.seconds = 1;
  measurement.header.timestamp.nanoseconds = 2;
  measurement.encoder_1_pos = -300;
  measurement.encoder_2_pos = 400;

  return measurement;
}

TEST(SensorInterface, UpdatesCorrectly)
{
  SensorInterface sensor_interface{getDefaultSensorInterface()};

  {
    const types::Status result{sensor_interface.open()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
    EXPECT_EQ(types::Measurement{}, sensor_interface.read());
  }

  {
    const types::Measurement measurement{ getDefaultMeasurement()};
    const types::Status result{sensor_interface.write(measurement)};
    ASSERT_EQ(types::Status::OKAY, result) << result;
    EXPECT_EQ(measurement, sensor_interface.read());
  }

  {
    const types::Status result{sensor_interface.close()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
    EXPECT_EQ(types::Measurement{}, sensor_interface.read());
  }
}

TEST(SensorInterface, OpenFailsWhenAlreadyOpen)
{
  SensorInterface sensor_interface{getDefaultSensorInterface()};

  {
    const types::Status result{sensor_interface.open()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
  }

  {
    const types::Status result{sensor_interface.open()};
    EXPECT_EQ(types::Status::PRECONDITION_FAILED, result) << result;
  }
}

TEST(SensorInterface, CloseFailsWhenAlreadyClosed)
{
  SensorInterface sensor_interface{getDefaultSensorInterface()};

  {
    const types::Status result{sensor_interface.open()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
  }

  {
    const types::Status result{sensor_interface.close()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
  }

  {
    const types::Status result{sensor_interface.close()};
    EXPECT_EQ(types::Status::PRECONDITION_FAILED, result) << result;
  }
}

TEST(SensorInterface, WriteFailsWhenInactive)
{
  SensorInterface sensor_interface{getDefaultSensorInterface()};

  const types::Measurement measurement{ getDefaultMeasurement()};
  const types::Status result{sensor_interface.write(measurement)};
  EXPECT_EQ(types::Status::UNAVAILABLE, result) << result;
}

} // interfaces