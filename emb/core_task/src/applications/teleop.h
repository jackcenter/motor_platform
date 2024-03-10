#ifndef APPLICATIONS_TELEOP_H
#define APPLICATIONS_TELEOP_H

#include "../components/platform.h"
#include "../components/state_estimation.h"
#include "../types/input.h"
#include "../types/measurement.h"
#include "../types/state.h"
#include "../types/status.h"

namespace applications {
struct TeleopState {
  types::Input input;
  types::Measurement measurement;
  types::State state;
};

class Teleop {
 public:
  explicit Teleop(components::Platform& platform_interface,
                  const components::StateEstimation& state_estimation_interface);
  types::Status cycle();
  const types::Input read() const;
  types::Status write(const types::Measurement& measurement);
  const TeleopState& getState() const;

 private:
  components::Platform platform_;
  components::StateEstimation state_estimation_;
  TeleopState state_{};
};
}  // namespace applications
#endif  // APPLICATIONS_TELEOP_H
