#ifndef TYPES_TIMESTAMP_H
#define TYPES_TIMESTAMP_H

namespace types {
struct Timestamp {
  unsigned long int seconds;
  unsigned long int nano_seconds;
};
}  // namespace types

#endif  // TYPES_TIMESTAMP_H
