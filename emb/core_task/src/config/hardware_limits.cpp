#include "hardware_limits.h"

namespace config
{
HardwareLimits loadHardwareLimits()
{
  HardwareLimits hardware_limits{};
  hardware_limits.motor_b_pwm_range ={ -255, 255 };
  
  return hardware_limits;
}
}