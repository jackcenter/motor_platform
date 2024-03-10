#ifndef INTERFACES_SENSOR_INTERFACE_H
#define INTERFACES_SENSOR_INTERFACE_H

#include "../sensors/quadrature_encoder.h"
#include "../types/measurement.h"
#include "../types/status.h"

namespace interfaces {
struct SensorInterfaceOptions {};

bool operator==(const SensorInterfaceOptions& lhs, const SensorInterfaceOptions& rhs);

class SensorInterface {
 public:
  SensorInterface(const sensors::QuadratureEncoder& encoder_1, const sensors::QuadratureEncoder& encoder_2,
                  const SensorInterfaceOptions& options);

  types::Measurement read() const;
  types::Status write(const types::Measurement measurement);

  const sensors::QuadratureEncoder& getEncoder1() const;
  const sensors::QuadratureEncoder& getEncoder2() const;
  const SensorInterfaceOptions& getOptions() const;

 private:
  sensors::QuadratureEncoder encoder_1_;
  sensors::QuadratureEncoder encoder_2_;
  SensorInterfaceOptions options_;
};

bool operator==(const SensorInterface& lhs, const SensorInterface& rhs);

}  // namespace interfaces
#endif  // INTERFACES_SENSOR_INTERFACE_h
