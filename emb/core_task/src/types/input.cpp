#include "input.h"

#include <tuple>

namespace types {
bool operator==(const Input& lhs, const Input& rhs) {
  return std::make_tuple(lhs.header, lhs.voltage) == std::make_tuple(rhs.header, rhs.voltage);
}
}  // namespace types
// namespace types
