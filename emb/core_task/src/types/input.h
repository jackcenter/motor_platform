#ifndef TYPES_INPUT_H
#define TYPES_INPUT_H

#include "header.h"

namespace types {
struct Input {
  Header header;
  double voltage;
};

bool operator==(const Input& lhs, const Input& rhs);
}  // namespace types

#endif  // TYPES_INPUT_H
