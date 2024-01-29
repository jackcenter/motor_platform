#ifndef SENSOR_INTERFACE_H
#define SENSOR_INTERFACE_H

#include "hardware/quadrature_encoder.h"
#include "types/measurement.h"

struct SensorInterfaceOptions {};

class SensorInterface {
 public:
  SensorInterface(const hardware::QuadratureEncoderOptions& encoder_1_options,
                  const hardware::QuadratureEncoderOptions& encoder_2_options, const SensorInterfaceOptions& options);

  types::Measurement operator()();

 private:
  hardware::QuadratureEncoder encoder_1_;
  hardware::QuadratureEncoder encoder_2_;
  SensorInterfaceOptions options_;
};

#endif  // SENSOR_INTERFACE_h
