#ifndef INTERFACES_STATE_ESTIMATION_INTERFACE_H
#define INTERFACES_STATE_ESTIMATION_INTERFACE_H

#include "../types/input.h"
#include "../types/measurement.h"
#include "../types/state.h"

namespace interfaces {
struct StateEstimationInterfaceOptions {};

bool operator==(const StateEstimationInterfaceOptions& lhs, const StateEstimationInterfaceOptions& rhs);

class StateEstimationInterface {
 public:
  explicit StateEstimationInterface(const StateEstimationInterfaceOptions& options);
  types::State read() const;
  void write(const types::Input& input, const types::Measurement& measurement);

  const types::State& getState() const;
  const StateEstimationInterfaceOptions& getOptions() const;

 private:
  types::State state_;
  StateEstimationInterfaceOptions options_;
};

bool operator==(const StateEstimationInterface& lhs, const StateEstimationInterface& rhs);
}  // namespace interfaces

#endif  // INTERFACES_STATE_ESTIMATION_INTERFACE_H
