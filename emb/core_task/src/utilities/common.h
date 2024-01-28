#ifndef UTILITIES_COMMON_H
#define UTILITIES_COMMON_H

namespace utilities
{
template <typename Scalar> int getSign(Scalar val) {
  return (static_cast<Scalar>(0) < val) - (val < static_cast<Scalar>(0));
}

template <typename Scalar> bool isInRange(Scalar val, Scalar min, Scalar max)
{
  return min <= val && val <= max;
}

template <typename ScalarFrom, typename ScalarTo>
ScalarTo remap(const ScalarFrom val, const ScalarFrom from_min, const ScalarFrom from_max, const ScalarTo to_min, const ScalarTo to_max)
{
  // TODO: input validation
  return to_min + static_cast<ScalarTo>(static_cast<ScalarFrom>(to_max - to_min) * ((val - from_min) / (from_max - from_min)));
}
}

#endif  // UTILITIES_COMMON_H