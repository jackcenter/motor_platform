#ifndef TYPES_TIMESTAMP_H
#define TYPES_TIMESTAMP_H

namespace types {
struct Timestamp {
  unsigned long int microseconds = 0;

  unsigned long toMilliseconds() const;
  double toSec() const;
};

bool operator==(const Timestamp& lhs, const Timestamp& rhs);
}  // namespace types

#endif  // TYPES_TIMESTAMP_H
