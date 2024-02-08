#ifndef UTILITIES_COMMON_H
#define UTILITIES_COMMON_H

namespace utilities {
template <typename Scalar>
int getSign(Scalar val) {
  return (static_cast<Scalar>(0) < val) - (val < static_cast<Scalar>(0));
}

template <typename Scalar>
bool isInRange(Scalar val, Scalar min, Scalar max) {
  return min <= val && val <= max;
}

template <typename ScalarFrom, typename ScalarTo>
ScalarTo remap(const ScalarFrom val, const ScalarFrom from_min, const ScalarFrom from_max, const ScalarTo to_min,
               const ScalarTo to_max) {
  // TODO: input validation
  if (!isInRange(val, from_min, from_max)) {
    // throw error
  }

  if (!(from_min < from_max)) {
    // throw error
  }

  if (!(to_min < to_max)) {
    // throw error
  }

  const double to_range{static_cast<double>(to_max - to_min)};
  const double from_range{static_cast<double>(from_max - from_min)};
  const double val_position{static_cast<double>(val) - static_cast<double>(from_min)};

  return to_min + static_cast<ScalarTo>(to_range * ((val_position) / (from_range)));
}
}  // namespace utilities

#endif  // UTILITIES_COMMON_H
