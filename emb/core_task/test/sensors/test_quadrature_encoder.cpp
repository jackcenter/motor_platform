#include "../../src/sensors/quadrature_encoder.h"

#include <gtest/gtest.h>

#include "../../src/types/status.h"

namespace sensors {
TEST(QuadratureEncoder, UpdatesCorrectly)
{
  const QuadratureEncoderOptions encoder_options{};
  QuadratureEncoder encoder{encoder_options};

  {
    const types::Status result{encoder.open()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
    EXPECT_EQ(0, encoder.read());
  }

  {
    const types::Status result{encoder.write(1)};
    ASSERT_EQ(types::Status::OKAY, result) << result;
    EXPECT_EQ(1, encoder.read());
  }

  {
    const types::Status result{encoder.close()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
    EXPECT_EQ(0, encoder.read());
  }
}

TEST(QuadratureEncoder, OpenFailsWhenAlreadyOpen)
{
  const QuadratureEncoderOptions encoder_options{};
  QuadratureEncoder encoder{encoder_options};

  {
    const types::Status result{encoder.open()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
  }

  {
    const types::Status result{encoder.open()};
    EXPECT_EQ(types::Status::PRECONDITION_FAILED, result) << result;
  }
}

TEST(QuadratureEncoder, CloseFailsWhenAlreadyClosed)
{
  const QuadratureEncoderOptions encoder_options{};
  QuadratureEncoder encoder{encoder_options};

  {
    const types::Status result{encoder.open()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
  }

  {
    const types::Status result{encoder.close()};
    ASSERT_EQ(types::Status::OKAY, result) << result;
  }

  {
    const types::Status result{encoder.close()};
    EXPECT_EQ(types::Status::PRECONDITION_FAILED, result) << result;
  }
}

TEST(QuadratureEncoder, WriteFailsWhenInactive)
{
  const QuadratureEncoderOptions encoder_options{};
  QuadratureEncoder encoder{encoder_options};

  const types::Status result{encoder.write(1)};
  EXPECT_EQ(types::Status::UNAVAILABLE, result) << result;
}
} // namespace sensors
