#include "quadrature_encoder.h"

#include <tuple>

#include <Arduino.h>
#include <Encoder.h>

namespace hardware {
bool operator==(const QuadratureEncoderOptions& lhs, const QuadratureEncoderOptions& rhs) {
  return std::tuple(lhs.CH_A, lhs.CH_B) == std::tuple(rhs.CH_A, rhs.CH_B);
}

QuadratureEncoder::QuadratureEncoder(const QuadratureEncoderOptions& options)
    : options_{options}, encoder_{Encoder(options_.CH_A, options_.CH_B)} {
  pinMode(options_.CH_A, INPUT_PULLUP);
  pinMode(options_.CH_B, INPUT_PULLUP);
}

QuadratureEncoder::QuadratureEncoder(QuadratureEncoder&& other)
    : options_{other.getOptions()}, encoder_{Encoder(options_.CH_A, options_.CH_B)} {}

void QuadratureEncoder::open() { write(0); }

long int QuadratureEncoder::read() { return encoder_.read(); }

void QuadratureEncoder::write(const long int val) { encoder_.write(val); }

const QuadratureEncoderOptions& QuadratureEncoder::getOptions() const { return options_; }
}  // namespace hardware
