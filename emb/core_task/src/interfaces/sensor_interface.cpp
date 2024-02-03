#include "sensor_interface.h"

#include <utility>

#include "../hardware/quadrature_encoder.h"
#include "../types/measurement.h"

namespace interfaces {
SensorInterface::SensorInterface(hardware::QuadratureEncoder&& encoder_1, hardware::QuadratureEncoder&& encoder_2,
                                 const SensorInterfaceOptions& options)
    : encoder_1_{std::move(encoder_1)}, encoder_2_{std::move(encoder_2)}, options_{options} {
  encoder_1_.open();
  encoder_2_.open();
}

SensorInterface::SensorInterface(SensorInterface& other)
    : encoder_1_{std::move(other.encoder_1_)}, encoder_2_{std::move(other.encoder_2_)}, options_{other.options_} {}

types::Measurement SensorInterface::operator()() {
  types::Measurement measurement;
  measurement.header = {};
  measurement.encoder_1_pos = encoder_1_.read();
  measurement.encoder_2_pos = encoder_2_.read();

  return measurement;
}
}  // namespace interfaces
