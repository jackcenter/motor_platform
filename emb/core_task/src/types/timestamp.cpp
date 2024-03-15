#include "timestamp.h"

namespace types {
bool operator==(const Timestamp& lhs, const Timestamp& rhs) { return lhs.microseconds == rhs.microseconds; }
}  // namespace types
