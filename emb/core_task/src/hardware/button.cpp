#include "button.h"

#include <Arduino.h>

namespace hardware {
Button::Button(const ButtonOptions& options) : options_{options} {
  pinMode(options_.pin, INPUT_PULLUP);
  measurement_ = read();
  state_ = measurement_.reading ? SignalState::kHigh : SignalState::kLow;
}

bool Button::operator()() {
  const ButtonMeasurement current_measurement = read();
  updateTransientState(state_);

  if (current_measurement.reading != measurement_.reading) {
    debounce_time_ms_ = current_measurement.time_ms;
    measurement_ = current_measurement;
  }

  if (options_.debounce_delay_ms < (current_measurement.time_ms - debounce_time_ms_)) {
    state_ = determineState(current_measurement, state_);
  }

  measurement_ = current_measurement;
  return isTiggered();
}

bool Button::isTiggered() const { return options_.trigger == state_; }

ButtonMeasurement Button::read() const {
  ButtonMeasurement measurement{};
  measurement.time_ms = millis();
  measurement.reading = digitalRead(options_.pin);

  return measurement;
}

void Button::updateTransientState(const SignalState& state) {
  if (state == SignalState::kRising) {
    state_ = SignalState::kHigh;
  }

  if (state == SignalState::kFalling) {
    state_ = SignalState::kLow;
  }
}

SignalState Button::determineState(const ButtonMeasurement& measurement, const SignalState& state) const {
  const bool isButtonPressed{measurement.reading == 1};
  switch (state) {
    case SignalState::kLow:
      return isButtonPressed ? SignalState::kRising : SignalState::kLow;
    case SignalState::kHigh:
      return isButtonPressed ? SignalState::kHigh : SignalState::kFalling;
    case SignalState::kRising:
      return isButtonPressed ? SignalState::kHigh : SignalState::kFalling;
    case SignalState::kFalling:
      return isButtonPressed ? SignalState::kRising : SignalState::kLow;
    default:
      return SignalState::kLow;
      // TODO: Throw an error, all GateStates should be handled above.
  }
}
}  // namespace hardware
