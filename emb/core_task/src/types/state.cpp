#include "state.h"

#include <tuple>

namespace types {
bool operator==(const State& lhs, const State& rhs) {
  return std::tuple(lhs.header, lhs.joint_1_position_rad, lhs.joint_1_velocity_rps, lhs.joint_2_position_rad,
                    lhs.joint_2_velocity_rps) == std::tuple(rhs.header, rhs.joint_1_position_rad,
                                                            rhs.joint_1_velocity_rps, rhs.joint_2_position_rad,
                                                            rhs.joint_2_velocity_rps);
}
}  // namespace types