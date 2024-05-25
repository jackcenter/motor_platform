#ifndef HARDWARE_BUTTON_H
#define HARDWARE_BUTTON_H

namespace hardware {
enum class SignalState { kLow, kHigh, kRising, kFalling };

struct ButtonMeasurement {
  unsigned long time_ms = 0;
  int reading = 0;
};

struct ButtonOptions {
  unsigned long debounce_delay_ms = 0;
  int pin = 0;
  SignalState trigger = SignalState::kFalling;
};

class Button {
 public:
  Button(const ButtonOptions& options);

  bool operator()();
  bool isTiggered() const;
  ButtonMeasurement read() const;

 private:
  void updateTransientState(const SignalState& state);
  SignalState determineState(const ButtonMeasurement&, const SignalState& state) const;

  ButtonMeasurement measurement_{};
  SignalState state_ = SignalState::kLow;
  unsigned long debounce_time_ms_ = 0;

  ButtonOptions options_;
};
}  // namespace hardware

#endif  // HARDWARE_BUTTON_H
