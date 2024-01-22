#ifndef CORE_TASK_CONFIG_HARDWARE_LIMITS_H
#define CORE_TASK_CONFIG_HARDWARE_LIMITS_H

#include <utility>

namespace config
{
struct HardwareLimits
{
   std::pair<int,int> motor_b_pwm_range;
};

HardwareLimits loadHardwareLimits();
}  // config
#endif  // CORE_TASK_CONFIG_HARDWARE_LIMITS_H