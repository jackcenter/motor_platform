#include "actuator_interface.h"

#include <unordered_map>
#include <utility>

#include "hardware/tb6612fng.h"
#include "types/common.h"
#include "types/input.h"
#include "types/status.h"
#include "utilities/common.h"

ActuatorInterace::ActuatorInterace(const hardware::Tb6612fng& tb6612fng, const ActuatorInterfaceOptions& options)
  : tb6612fng_{ tb6612fng }
  , options_{ options }
  {}

types::Status ActuatorInterace::operator()(const types::Input& input) const
{
  // verify voltage is withing range

  static std::unordered_map<int,std::pair<bool,bool>> input_map
  {
    {-1, {true, false}},
    {0, {false, true}},
    {1, {false, true}}
  };

  const std::pair<bool,bool> input_pair{ input_map(utilities::getSign(input.voltage)) };
  
  // remap voltage to pwm range
  const int pwm_value{ (utilities::remap<double,int>(std::abs(input.voltage), 0.0, 5.0, 0, 255)) };

  tb6612fng_.write(types::Channel::B, input_pair.first, input_pair.second, pwm_value);  
  return types::Status::OKAY;
}

void ActuatorInterace::activate() const
{
  tb6612fng_.open();
}

void ActuatorInterace::deactivate() const
{
  tb6612fng_.close();
}
