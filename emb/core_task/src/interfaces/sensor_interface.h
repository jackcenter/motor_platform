#ifndef INTERFACES_SENSOR_INTERFACE_H
#define INTERFACES_SENSOR_INTERFACE_H

#include "../hardware/quadrature_encoder.h"
#include "../types/measurement.h"

namespace interfaces {
struct SensorInterfaceOptions {};

bool operator==(const SensorInterfaceOptions& lhs, const SensorInterfaceOptions& rhs);

class SensorInterface {
 public:
  SensorInterface(hardware::QuadratureEncoder&& encoder_1, hardware::QuadratureEncoder&& encoder_2,
                  const SensorInterfaceOptions& options);

  SensorInterface(SensorInterface& other);
  SensorInterface(SensorInterface&& other) = default;
  ~SensorInterface() = default;

  types::Measurement operator()();

  const hardware::QuadratureEncoder& getEncoder1() const;
  const hardware::QuadratureEncoder& getEncoder2() const;
  const SensorInterfaceOptions& getOptions() const;

 private:
  hardware::QuadratureEncoder encoder_1_;
  hardware::QuadratureEncoder encoder_2_;
  SensorInterfaceOptions options_;
};

bool operator==(const SensorInterface& lhs, const SensorInterface& rhs);

}  // namespace interfaces
#endif  // INTERFACES_SENSOR_INTERFACE_h
