#ifndef TYPES_MEASUREMENT_H
#define TYPES_MEASUREMENT_H

#include "header.h"

namespace types {
struct Measurement {
  Header header;
  long int encoder_1_pos;
  long int encoder_2_pos;
};
}  // namespace types

#endif  // TYPES_MESSUREMENT_H
