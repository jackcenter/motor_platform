#include "../../src/utilities/time.h"

#include <stdexcept>

#include <gtest/gtest.h>

#include "../../src/types/timestamp.h"

namespace utilities {
TEST(GetDuration, returnsCorrectly) {
  types::Timestamp first;
  first.microseconds = 1;

  types::Timestamp second;
  second.microseconds = 3;

  const types::Timestamp duration{getDuration(first, second)};

  types::Timestamp expected_duration;
  expected_duration.microseconds = 2;

  EXPECT_EQ(expected_duration, duration) << "Test: " << expected_duration.microseconds << " " << duration.microseconds;
}
}  // namespace utilities
