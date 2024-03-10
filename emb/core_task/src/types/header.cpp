#include "header.h"

#include <tuple>

namespace types {
bool operator==(const Header& lhs, const Header& rhs) {
  return std::make_tuple(lhs.sequence, lhs.timestamp) == std::make_tuple(rhs.sequence, rhs.timestamp);
}
}  // namespace types
