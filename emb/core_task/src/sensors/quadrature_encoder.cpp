#include "quadrature_encoder.h"

#include <tuple>

namespace sensors {
bool operator==(const QuadratureEncoderOptions& lhs, const QuadratureEncoderOptions& rhs) { return true; }

QuadratureEncoder::QuadratureEncoder(const QuadratureEncoderOptions& options) : options_{options}, position_{0} {}

void QuadratureEncoder::open() { write(0); }

long int QuadratureEncoder::read() const { return position_; }

void QuadratureEncoder::write(const long int val) { position_ = val; }

const QuadratureEncoderOptions& QuadratureEncoder::getOptions() const { return options_; }

long int QuadratureEncoder::getPosition() const { return position_; }

bool operator==(const QuadratureEncoder& lhs, const QuadratureEncoder& rhs) {
  return std::make_tuple(lhs.getOptions(), lhs.getPosition()) == std::make_tuple(rhs.getOptions(), lhs.getPosition());
}
}  // namespace sensors
