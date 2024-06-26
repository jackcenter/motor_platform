#include "timestamp.h"

namespace types {
unsigned long Timestamp::toMilliseconds() const {
  return static_cast<unsigned long>(1e-3 * static_cast<double>(microseconds));
}

double Timestamp::toSec() const { return 1e-6 * static_cast<double>(microseconds); }

bool operator==(const Timestamp& lhs, const Timestamp& rhs) { return lhs.microseconds == rhs.microseconds; }
}  // namespace types
