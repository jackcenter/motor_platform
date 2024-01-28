#include "sensor_interface.h"

#include <utility>

#include "hardware/quadrature_encoder.h"
#include "types/measurement.h"

SensorInterface::SensorInterface(hardware::QuadratureEncoder& encoder_1, hardware::QuadratureEncoder& encoder_2,
                                 const SensorInterfaceOptions& options)
    : encoder_1_{std::move(encoder_1)}, encoder_2_{std::move(encoder_2)}, options_{options} {
  encoder_1_.open();
  encoder_2_.open();
}

types::Measurement SensorInterface::operator()()
{
  types::Measurement measurement;
  measurement.encoder_1_pos = encoder_1_.read();
  measurement.encoder_2_pos = encoder_2_.read();

  return measurement;
}
