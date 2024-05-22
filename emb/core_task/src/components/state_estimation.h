#ifndef COMPONENTS_STATE_ESTIMATION_H
#define COMPONENTS_STATE_ESTIMATION_H

#include "../types/input.h"
#include "../types/measurement.h"
#include "../types/state.h"
#include "../types/status.h"

namespace components {
struct StateEstimationOptions {
  double joint_1_rad_per_count;
  double joint_2_rad_per_count;
};

bool operator==(const StateEstimationOptions& lhs, const StateEstimationOptions& rhs);

class StateEstimation {
 public:
  explicit StateEstimation(const StateEstimationOptions& options);

  types::Status open();
  types::Status close();
  types::State read() const;
  types::Status write(const types::Measurement& measurement);

  const types::State& getState() const;
  const StateEstimationOptions& getOptions() const;

  const bool isActive() const;
  const bool isInitialized() const;

 private:
  double computeVelocity(const double current_position, const double previous_position,
                         const types::Timestamp& current_timestamp, const types::Timestamp& previous_timestamp);
  types::State initializeState(const types::Measurement& measurement) const;

  types::State state_;
  StateEstimationOptions options_;

  bool is_active_ = false;
  bool is_initialized_ = false;
};

bool operator==(const StateEstimation& lhs, const StateEstimation& rhs);
}  // namespace components

#endif  // COMPONENTS_STATE_ESTIMATION_H
