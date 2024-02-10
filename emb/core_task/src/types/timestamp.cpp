#include "timestamp.h"

#include <tuple>

namespace types {
double Timestamp::toSeconds() const { return static_cast<double>(seconds) + 1e-9 * static_cast<double>(nanoseconds); }

bool operator==(const Timestamp& lhs, const Timestamp& rhs) {
  return std::tuple(lhs.seconds, lhs.nanoseconds) == std::tuple(rhs.seconds, rhs.nanoseconds);
}
}  // namespace types
