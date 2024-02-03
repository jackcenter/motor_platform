#ifndef INTERFACE_ACTUATOR_INTERFACE_H
#define INTERFACE_ACTUATOR_INTERFACE_H

#include <utility>

#include "../hardware/tb6612fng.h"
#include "../types/common.h"
#include "../types/input.h"
#include "../types/status.h"

namespace interfaces {
struct ActuatorInterfaceOptions {
  std::pair<double, double> voltage_range;
};

class ActuatorInterace {
 public:
  ActuatorInterace(const hardware::Tb6612fng& tb6612fng, const ActuatorInterfaceOptions& options);

  types::Status operator()(const types::Input& input) const;
  void activate() const;
  void deactivate() const;

 private:
  hardware::Tb6612fng tb6612fng_;
  ActuatorInterfaceOptions options_;
};
}  // namespace interfaces
#endif  // INTERFAC_ACTUATOR_INTERFACE_H
