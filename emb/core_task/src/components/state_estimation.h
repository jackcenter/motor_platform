#ifndef COMPONENTS_STATE_ESTIMATION_H
#define COMPONENTS_STATE_ESTIMATION_H

#include "../types/input.h"
#include "../types/measurement.h"
#include "../types/state.h"

namespace components {
struct StateEstimationOptions {};

bool operator==(const StateEstimationOptions& lhs, const StateEstimationOptions& rhs);

class StateEstimation {
 public:
  explicit StateEstimation(const StateEstimationOptions& options);
  types::State read() const;
  void write(const types::Input& input, const types::Measurement& measurement);

  const types::State& getState() const;
  const StateEstimationOptions& getOptions() const;

 private:
  types::State state_;
  StateEstimationOptions options_;
};

bool operator==(const StateEstimation& lhs, const StateEstimation& rhs);
}  // namespace components

#endif  // COMPONENTS_STATE_ESTIMATION_H
