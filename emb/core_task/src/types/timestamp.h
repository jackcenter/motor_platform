#ifndef TYPES_TIMESTAMP_H
#define TYPES_TIMESTAMP_H

namespace types {
struct Timestamp {
  unsigned long int seconds;
  unsigned long int nanoseconds;

  double toSeconds() const;
};

bool operator==(const Timestamp& lhs, const Timestamp& rhs);
}  // namespace types

#endif  // TYPES_TIMESTAMP_H
