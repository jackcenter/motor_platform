#ifndef TYPES_MEASUREMENT_H
#define TYPES_MEASUREMENT_H

#include "header.h"

namespace types {
struct Measurement {
  Header header{};
  long int encoder_1_pos = 0.0;
  long int encoder_2_pos = 0.0;
};

bool operator==(const Measurement& lhs, const Measurement& rhs);
}  // namespace types

#endif  // TYPES_MESSUREMENT_H
