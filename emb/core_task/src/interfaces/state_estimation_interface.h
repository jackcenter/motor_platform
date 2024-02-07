#ifndef INTERFACES_STATE_ESTIMATION_INTERFACE_H
#define INTERFACES_STATE_ESTIMATION_INTERFACE_H

#include "../types/input.h"
#include "../types/measurement.h"
#include "../types/state.h"

namespace interfaces {
struct StateEstimationInterfaceOptions {};

class StateEstimationInterface {
 public:
  explicit StateEstimationInterface(const StateEstimationInterfaceOptions& options);
  types::State read() const;
  void write(const types::Input& input, const types::Measurement& measurement);

 private:
  types::State state_;
  StateEstimationInterfaceOptions options_;
};
}  // namespace interfaces

#endif  // INTERFACES_STATE_ESTIMATION_INTERFACE_H
