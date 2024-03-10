#include "sensor_interface.h"

#include <tuple>
#include <utility>

#include "../sensors/quadrature_encoder.h"
#include "../types/measurement.h"
#include "../types/status.h"

namespace interfaces {
bool operator==(const SensorInterfaceOptions& lhs, const SensorInterfaceOptions& rhs) { return true; }

SensorInterface::SensorInterface(const sensors::QuadratureEncoder& encoder_1,
                                 const sensors::QuadratureEncoder& encoder_2, const SensorInterfaceOptions& options)
    : encoder_1_{encoder_1}, encoder_2_{encoder_2}, options_{options} {
  encoder_1_.open();
  encoder_2_.open();
}

types::Measurement SensorInterface::read() const {
  types::Measurement measurement;
  measurement.header = {};
  measurement.encoder_1_pos = encoder_1_.read();
  measurement.encoder_2_pos = encoder_2_.read();

  return measurement;
}

types::Status SensorInterface::write(const types::Measurement measurement) {
  encoder_1_.write(measurement.encoder_1_pos);
  encoder_2_.write(measurement.encoder_2_pos);

  return types::Status::OKAY;
}

const sensors::QuadratureEncoder& SensorInterface::getEncoder1() const { return encoder_1_; }

const sensors::QuadratureEncoder& SensorInterface::getEncoder2() const { return encoder_2_; }

const SensorInterfaceOptions& SensorInterface::getOptions() const { return options_; }

bool operator==(const SensorInterface& lhs, const SensorInterface& rhs) {
  return std::make_tuple(lhs.getEncoder1(), lhs.getEncoder2(), lhs.getOptions()) ==
         std::make_tuple(rhs.getEncoder1(), rhs.getEncoder2(), rhs.getOptions());
}
}  // namespace interfaces
