#ifndef SENSORS_QUADRATURE_ENCODER_H
#define SENSORS_QUADRATURE_ENCODER_H

#include "../types/status.h"

namespace sensors {
struct QuadratureEncoderOptions {};

bool operator==(const QuadratureEncoderOptions& lhs, const QuadratureEncoderOptions& rhs);

class QuadratureEncoder {
 public:
  explicit QuadratureEncoder(const QuadratureEncoderOptions& options);

  types::Status close();
  types::Status open();
  types::Status write(const long int val);

  const QuadratureEncoderOptions& getOptions() const;
  bool isActive() const;
  long int read() const;

 private:
  QuadratureEncoderOptions options_;
  long int position_;
  bool active_;
};

bool operator==(const QuadratureEncoder& lhs, const QuadratureEncoder& rhs);
}  // namespace sensors

#endif  // SENSORS_QUADRATURE_ENCODER_H
