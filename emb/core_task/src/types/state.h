#ifndef TYPES_STATE_H
#define TYPES_STATE_H

#include "header.h"

namespace types {
struct State {
  Header header;
  double joint_1_position_rad;
  double joint_1_velocity_rps;
  double joint_2_position_rad;
  double joint_2_velocity_rps;
};
}  // namespace types

#endif  // TYPES_STATE_H
