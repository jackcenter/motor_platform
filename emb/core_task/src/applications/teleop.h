#ifndef APPLICATIONS_TELEOP_H
#define APPLICATIONS_TELEOP_H

#include "../interfaces/platform_interface.h"
#include "../types/input.h"
#include "../types/measurement.h"
#include "../types/status.h"

namespace applications {
struct TeleopState {
  types::Input input;
  types::Measurement measurement;
};

class Teleop {
 public:
  explicit Teleop(interfaces::PlatformInterface& platform_interface);
  types::Status cycle();
  const TeleopState& getState() const;

 private:
  interfaces::PlatformInterface platform_interface_;
  TeleopState state_{};
};
}  // namespace applications
#endif  // APPLICATIONS_TELEOP_H
