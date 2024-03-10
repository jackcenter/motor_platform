#include "timestamp.h"

#include <tuple>

namespace types {
bool operator==(const Timestamp& lhs, const Timestamp& rhs) {
  return std::make_tuple(lhs.seconds, lhs.nanoseconds) == std::make_tuple(rhs.seconds, rhs.nanoseconds);
}
}  // namespace types
