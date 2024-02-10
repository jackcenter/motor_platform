#include "../../src/utilities/common.h"

#include <gtest/gtest.h>

namespace utilities {
TEST(GetSign, ReturnsCorrectly) {
  EXPECT_EQ(1, getSign(2));
  EXPECT_EQ(0, getSign(0));
  EXPECT_EQ(-1, getSign(-2));
}

TEST(GetSign, FloatReturnsCorrectly) {
  EXPECT_EQ(1, getSign(static_cast<float>(2)));
  EXPECT_EQ(0, getSign(static_cast<float>(0)));
  EXPECT_EQ(-1, getSign(static_cast<float>(-2)));
}

TEST(IsInRange, IntReturnsCorrectly) {
  {
    const int min_value{1};
    const int max_value{10};
    const int test_value{5};

    EXPECT_FALSE(isInRange(min_value - 1, min_value, max_value));
    EXPECT_TRUE(isInRange(min_value, min_value, max_value));
    EXPECT_TRUE(isInRange(test_value, min_value, max_value));
    EXPECT_TRUE(isInRange(max_value, min_value, max_value));
    EXPECT_FALSE(isInRange(max_value + 1, min_value, max_value));
  }

  {
    const int min_value{-5};
    const int max_value{5};
    const int test_value{0};

    EXPECT_FALSE(isInRange(min_value - 1, min_value, max_value));
    EXPECT_TRUE(isInRange(min_value, min_value, max_value));
    EXPECT_TRUE(isInRange(test_value, min_value, max_value));
    EXPECT_TRUE(isInRange(max_value, min_value, max_value));
    EXPECT_FALSE(isInRange(max_value + 1, min_value, max_value));
  }

  {
    const int min_value{-10};
    const int max_value{-1};
    const int test_value{-5};

    EXPECT_FALSE(isInRange(min_value - 1, min_value, max_value));
    EXPECT_TRUE(isInRange(min_value, min_value, max_value));
    EXPECT_TRUE(isInRange(test_value, min_value, max_value));
    EXPECT_TRUE(isInRange(max_value, min_value, max_value));
    EXPECT_FALSE(isInRange(max_value + 1, min_value, max_value));
  }
}

TEST(IsInRange, FloatReturnsCorrectly) {
  {
    const float min_value{1.0};
    const float max_value{10.0};
    const float test_value{5.0};

    EXPECT_FALSE(isInRange(min_value - 1, min_value, max_value));
    EXPECT_TRUE(isInRange(min_value, min_value, max_value));
    EXPECT_TRUE(isInRange(test_value, min_value, max_value));
    EXPECT_TRUE(isInRange(max_value, min_value, max_value));
    EXPECT_FALSE(isInRange(max_value + 1, min_value, max_value));
  }

  {
    const float min_value{-5.0};
    const float max_value{5.0};
    const float test_value{0.0};

    EXPECT_FALSE(isInRange(min_value - 1, min_value, max_value));
    EXPECT_TRUE(isInRange(min_value, min_value, max_value));
    EXPECT_TRUE(isInRange(test_value, min_value, max_value));
    EXPECT_TRUE(isInRange(max_value, min_value, max_value));
    EXPECT_FALSE(isInRange(max_value + 1, min_value, max_value));
  }

  {
    const float min_value{-10.0};
    const float max_value{-1.0};
    const float test_value{-5.0};

    EXPECT_FALSE(isInRange(min_value - 1, min_value, max_value));
    EXPECT_TRUE(isInRange(min_value, min_value, max_value));
    EXPECT_TRUE(isInRange(test_value, min_value, max_value));
    EXPECT_TRUE(isInRange(max_value, min_value, max_value));
    EXPECT_FALSE(isInRange(max_value + 1, min_value, max_value));
  }
}

TEST(Remap, IntReturnsCorrectly) {
  {
    const int from_min{0};
    const int from_max{10};
    const int to_min{0};
    const int to_max{100};
    const int val{5};
    const int expected_result{50};
    const int result{remap<int, int>(val, from_min, from_max, to_min, to_max)};
    EXPECT_EQ(expected_result, result);
  }

  {
    const int from_min{-4};
    const int from_max{5};
    const int to_min{1};
    const int to_max{11};
    const int val{-3};
    const int expected_result{2};
    const int result{remap<int, int>(val, from_min, from_max, to_min, to_max)};
    EXPECT_EQ(expected_result, result);
  }

  {
    const int from_min{2};
    const int from_max{12};
    const int to_min{-6};
    const int to_max{3};
    const int val{11};
    const int expected_result{2};
    const int result{remap<int, int>(val, from_min, from_max, to_min, to_max)};
    EXPECT_EQ(expected_result, result);
  }

  {
    const int from_min{-13};
    const int from_max{-3};
    const int to_min{-600};
    const int to_max{-500};
    const int val{-6};
    const int expected_result{-530};
    const int result{remap<int, int>(val, from_min, from_max, to_min, to_max)};
    EXPECT_EQ(expected_result, result);
  }
}

TEST(Remap, FloatReturnsCorrectly) {
  {
    const float from_min{0.0};
    const float from_max{10.0};
    const float to_min{0.0};
    const float to_max{100.0};
    const float val{5.0};
    const float expected_result{50.0};
    const float result{remap<float, float>(val, from_min, from_max, to_min, to_max)};
    EXPECT_EQ(expected_result, result);
  }

  {
    const float from_min{-5.0};
    const float from_max{5.0};
    const float to_min{1.0};
    const float to_max{11.0};
    const float val{-3.0};
    const float expected_result{3.0};
    const float result{remap<float, float>(val, from_min, from_max, to_min, to_max)};
    EXPECT_EQ(expected_result, result);
  }

  {
    const float from_min{2.0};
    const float from_max{12.0};
    const float to_min{-6.0};
    const float to_max{4.0};
    const float val{11.0};
    const float expected_result{3.0};
    const float result{remap<float, float>(val, from_min, from_max, to_min, to_max)};
    EXPECT_EQ(expected_result, result);
  }

  {
    const float from_min{-13.0};
    const float from_max{-3.0};
    const float to_min{-600.0};
    const float to_max{-500.0};
    const float val{-6.0};
    const float expected_result{-530.0};
    const float result{remap<float, float>(val, from_min, from_max, to_min, to_max)};
    EXPECT_EQ(expected_result, result);
  }
}

TEST(Remap, FloatToIntReturnsCorrectly)
{
  const float from_min{0.0};
  const float from_max{5.0};
  const int to_min{0};
  const int to_max{255};
  const float val{2.5};
  const int expected_result{127};
  const int result{remap<float, int>(val, from_min, from_max, to_min, to_max)};
  EXPECT_EQ(expected_result, result);
}
}  // namespace utilities
