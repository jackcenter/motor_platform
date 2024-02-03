#ifndef HARDWARE_QUADRATURE_ENCODER_H
#define HARDWARE_QUADRATURE_ENCODER_H

#include <stdint.h>

#include <Encoder.h>

namespace hardware {
struct QuadratureEncoderOptions {
  uint8_t CH_A;
  uint8_t CH_B;
};

class QuadratureEncoder {
 public:
  explicit QuadratureEncoder(const QuadratureEncoderOptions& options);

  // Not an actual copy constructor, moves the encoder to the new object. It is set up like this for convinience.
  QuadratureEncoder(QuadratureEncoder& other) = delete;
  QuadratureEncoder(QuadratureEncoder&& other);
  ~QuadratureEncoder() = default;

  void open();
  long int read();
  void write(const long int val);

  const QuadratureEncoderOptions& getOptions() const;

 private:
  QuadratureEncoderOptions options_;
  Encoder encoder_;
};
}  // namespace hardware

#endif  // HARDWARE_QUADRATURE_ENCODER_H
