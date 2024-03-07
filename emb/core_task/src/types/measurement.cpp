#include "measurement.h"

#include <tuple>

namespace types {
bool operator==(const Measurement& lhs, const Measurement& rhs) {
  return std::tuple(lhs.header, lhs.encoder_1_pos, lhs.encoder_2_pos) ==
         std::tuple(rhs.header, rhs.encoder_1_pos, rhs.encoder_2_pos);
}
}  // namespace types