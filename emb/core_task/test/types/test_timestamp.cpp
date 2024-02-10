#include "../../src/types/timestamp.h"

#include <gtest/gtest.h>

namespace types {
TEST(Timestamp, ToSecondsReturnsCorrectly)
{
  types::Timestamp timestamp;
  timestamp.seconds = 1;
  timestamp.nanoseconds = 5e8;
  
  const double expected_result{ 1.5 };
  EXPECT_EQ(expected_result, timestamp.toSeconds());
}
}  // namespace types