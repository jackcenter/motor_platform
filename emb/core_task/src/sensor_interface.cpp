#include "sensor_interface.h"

#include <utility>

#include "hardware/quadrature_encoder.h"
#include "types/measurement.h"

SensorInterface::SensorInterface(const hardware::QuadratureEncoderOptions& encoder_1_options,
                                 const hardware::QuadratureEncoderOptions& encoder_2_options,
                                 const SensorInterfaceOptions& options)
    : encoder_1_{encoder_1_options}, encoder_2_{encoder_2_options}, options_{options} {
  encoder_1_.open();
  encoder_2_.open();
}

types::Measurement SensorInterface::operator()() {
  types::Measurement measurement;
  measurement.encoder_1_pos = encoder_1_.read();
  measurement.encoder_2_pos = encoder_2_.read();

  return measurement;
}
