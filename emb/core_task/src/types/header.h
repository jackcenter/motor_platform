#ifndef TYPES_HEADER_H
#define TYPES_HEADER_H

#include "timestamp.h"

namespace types {
struct Header {
  unsigned int sequence;
  Timestamp timestamp;
};
}  // namespace types

#endif  // TYPES_HEADER_H
