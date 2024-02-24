#include "header.h"

#include <tuple>

namespace types {
bool operator==(const Header& lhs, const Header& rhs) {
  return std::tuple(lhs.sequence, lhs.timestamp) == std::tuple(rhs.sequence, rhs.timestamp);
}
}  // namespace types
