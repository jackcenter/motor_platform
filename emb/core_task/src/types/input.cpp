#include "input.h"

#include <tuple>

namespace types {
bool operator==(const Input& lhs, const Input& rhs) {
  return std::tuple(lhs.header, lhs.voltage) == std::tuple(rhs.header, rhs.voltage);
}
}  // namespace types
// namespace types
