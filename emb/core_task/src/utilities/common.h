#ifndef UTILITIES_COMMON_H
#define UTILITIES_COMMON_H

namespace utilities
{
template <class Scalar>
Scalar remap(const Scalar value, const Scalar from_min, const Scalar from_max, const Scalar to_min, const Scalar to_max)
{
  // TODO: input validation
  return to_min + (to_max - to_min) * ((value - from_min) / (from_max - from_min));
}
}

#endif  // UTILITIES_COMMON_H