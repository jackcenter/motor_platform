#ifndef SENSORS_QUADRATURE_ENCODER_H
#define SENSORS_QUADRATURE_ENCODER_H

namespace sensors {
struct QuadratureEncoderOptions {};

bool operator==(const QuadratureEncoderOptions& lhs, const QuadratureEncoderOptions& rhs);

class QuadratureEncoder {
 public:
  explicit QuadratureEncoder(const QuadratureEncoderOptions& options);

  void open();
  long int read() const;
  void write(const long int val);

  const QuadratureEncoderOptions& getOptions() const;
  long int getPosition() const;

 private:
  QuadratureEncoderOptions options_;
  long int position_;
};

bool operator==(const QuadratureEncoder& lhs, const QuadratureEncoder& rhs);
}  // namespace sensors

#endif  // SENSORS_QUADRATURE_ENCODER_H
