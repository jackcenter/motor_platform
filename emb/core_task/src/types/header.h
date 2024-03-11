#ifndef TYPES_HEADER_H
#define TYPES_HEADER_H

#include "timestamp.h"

namespace types {
struct Header {
  unsigned int sequence = 0;
  Timestamp timestamp{};
};

bool operator==(const Header& lhs, const Header& rhs);
}  // namespace types

#endif  // TYPES_HEADER_H
