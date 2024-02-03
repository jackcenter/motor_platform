#ifndef INTERFACES_SENSOR_INTERFACE_H
#define INTERFACES_SENSOR_INTERFACE_H

#include "../hardware/quadrature_encoder.h"
#include "../types/measurement.h"

namespace interfaces {
struct SensorInterfaceOptions {};

class SensorInterface {
 public:
  SensorInterface(hardware::QuadratureEncoder&& encoder_1, hardware::QuadratureEncoder&& encoder_2,
                  const SensorInterfaceOptions& options);

  SensorInterface(SensorInterface& other);
  SensorInterface(SensorInterface&& other) = default;
  ~SensorInterface() = default;

  types::Measurement operator()();

 private:
  hardware::QuadratureEncoder encoder_1_;
  hardware::QuadratureEncoder encoder_2_;
  SensorInterfaceOptions options_;
};
}  // namespace interfaces
#endif  // INTERFACES_SENSOR_INTERFACE_h
