#include "quadrature_encoder.h"

#include <tuple>

#include "../types/status.h"

namespace sensors {
bool operator==(const QuadratureEncoderOptions& lhs, const QuadratureEncoderOptions& rhs) { return true; }

QuadratureEncoder::QuadratureEncoder(const QuadratureEncoderOptions& options)
    : options_{options}, position_{0}, active_{false} {}

types::Status QuadratureEncoder::close() {
  if (!isActive()) {
    return types::Status::PRECONDITION_FAILED;
  }

  const types::Status write_status{write(0)};
  active_ = false;
  return write_status;
}

types::Status QuadratureEncoder::open() {
  if (isActive()) {
    return types::Status::PRECONDITION_FAILED;
  }

  active_ = true;
  const types::Status write_status{write(0)};
  return write_status;
}

types::Status QuadratureEncoder::write(const long int val) {
  if (!isActive()) {
    return types::Status::UNAVAILABLE;
  }

  position_ = val;
  return types::Status::OKAY;
}

const QuadratureEncoderOptions& QuadratureEncoder::getOptions() const { return options_; }

bool QuadratureEncoder::isActive() const { return active_; }

long int QuadratureEncoder::read() const { return position_; }

bool operator==(const QuadratureEncoder& lhs, const QuadratureEncoder& rhs) {
  return std::make_tuple(lhs.getOptions(), lhs.read()) == std::make_tuple(rhs.getOptions(), lhs.read());
}
}  // namespace sensors
