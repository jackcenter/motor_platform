#include "timestamp.h"

namespace types {
double Timestamp::toSec() const { return 1e-6 * static_cast<double>(microseconds); }

bool operator==(const Timestamp& lhs, const Timestamp& rhs) { return lhs.microseconds == rhs.microseconds; }
}  // namespace types
