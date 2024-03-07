#include "timestamp.h"

#include <tuple>

namespace types {
bool operator==(const Timestamp& lhs, const Timestamp& rhs) {
  return std::tuple(lhs.seconds, lhs.nanoseconds) == std::tuple(rhs.seconds, rhs.nanoseconds);
}
}  // namespace types
