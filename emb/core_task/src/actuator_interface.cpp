#include "actuator_interface.h"

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

  // map voltage sign to motor direction
  const double pwm_value{ static_cast<int>(utilities::remap<double>(input.voltage, 0.0, 5.0, 0.0, 255.0)) };

  // remap voltage to pwm range

  tb6612fng_.write(types::Channel::B, true, false, pwm_value);  
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
