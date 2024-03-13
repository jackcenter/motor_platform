#ifndef TYPES_TIMESTAMP_H
#define TYPES_TIMESTAMP_H

namespace types {
struct Timestamp {
  unsigned long int seconds = 0;
  unsigned long int nanoseconds = 0;
};

bool operator==(const Timestamp& lhs, const Timestamp& rhs);
}  // namespace types

#endif  // TYPES_TIMESTAMP_H
