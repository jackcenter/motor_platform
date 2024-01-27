#ifndef UTILITIES_COMMON_H
#define UTILITIES_COMMON_H

namespace utilities
{
template <typename Scalar> int sgn(Scalar value) {
  return (static_cast<Scalar>(0) < value) - (value < static_cast<Scalar>(0));
}

template <typename ScalarFrom, typename ScalarTo>
ScalarTo remap(const ScalarFrom value, const ScalarFrom from_min, const ScalarFrom from_max, const ScalarTo to_min, const ScalarTo to_max)
{
  // TODO: input validation
  return to_min + (to_max - to_min) * static_case<ScalarTo>((value - from_min) / (from_max - from_min));
}
}

#endif  // UTILITIES_COMMON_H