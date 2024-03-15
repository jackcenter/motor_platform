#ifndef APPLICATIONS_TELEOP_H
#define APPLICATIONS_TELEOP_H

#include "../components/platform.h"
#include "../components/state_estimation.h"
#include "../types/input.h"
#include "../types/measurement.h"
#include "../types/state.h"
#include "../types/status.h"
#include "../types/timestamp.h"

namespace applications {
struct TeleopState {
  types::Input input;
  types::Measurement measurement;
  types::State state;
};

bool operator==(const TeleopState& lhs, const TeleopState& rhs);

bool operator!=(const TeleopState& lhs, const TeleopState& rhs);

struct TeleopOptions {
  double gain = 0.0;
};

bool operator==(const TeleopOptions& lhs, const TeleopOptions& rhs);

class Teleop {
 public:
  explicit Teleop(const components::Platform& platform_interface, const components::StateEstimation& state_estimation,
                  const TeleopOptions& options);

  types::Status close();
  types::Status cycle(const types::Timestamp& timestamp);
  types::Status open();
  types::Status write(const types::Measurement& measurement);

  const TeleopOptions& getOptions() const;
  const components::Platform& getPlatform() const;
  const TeleopState& getState() const;
  const components::StateEstimation& getStateEstimation() const;
  const types::Input read() const;

 private:
  components::Platform platform_;
  components::StateEstimation state_estimation_;
  TeleopState state_;
  TeleopOptions options_;
};

bool operator==(const Teleop& lhs, const Teleop& rhs);
}  // namespace applications
#endif  // APPLICATIONS_TELEOP_H
