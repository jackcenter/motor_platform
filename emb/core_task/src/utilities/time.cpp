#include "../types/timestamp.h"

#include <stdexcept>

namespace utilities {
types::Timestamp getDuration(const types::Timestamp& first, const types::Timestamp& second) {
  // if (second.microseconds < first.microseconds) {
  //   throw std::invalid_argument(
  //       "the 'first' timestamp is greater than the 'second' timestamp which would lead to a negative duration");
  // }

  types::Timestamp duration;
  duration.microseconds = second.microseconds - first.microseconds;

  return duration;
}
}  // namespace utilities
