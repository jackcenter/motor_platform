#ifndef COMPONENTS_CONTROLLER_H
#define COMPONENTS_CONTROLLER_H

#include <tuple>

#include "../types/input.h"
#include "../types/state.h"
#include "../types/status.h"
#include "../types/timestamp.h"

namespace components {
struct ControllerOptions {
  double proportional_gain = 0.0;
  double integral_gain = 0.0;
  double derivative_gain = 0.0;
  double cycle_period_ms = 0.0;
  std::pair<double, double> input_range{0.0, 0.0};
};

bool operator==(const ControllerOptions& lhs, const ControllerOptions& rhs);

class Controller {
 public:
  explicit Controller(const ControllerOptions& options);

  types::Status activate();
  types::Status deactivate();
  types::Status initialize();

  types::Input cycle(const double reference, const types::State& state, const types::Timestamp& timestamp);

  const ControllerOptions& getOptions() const;
  bool isActive() const;
  bool isInitialized() const;

 private:
  types::Input getInputToDisableControl(const types::Timestamp& timestamp) const;

  ControllerOptions options_;

  bool is_active_ = false;
  bool is_initialized = false;
  double error_rad_ = 0.0;
  double error_sum_rad_ = 0.0;
};

bool operator==(const Controller& lhs, const Controller& rhs);
}  // namespace components

#endif  // COMPONENTS_CONTROLLER_H
