#include "sensor_interface.h"

#include <tuple>
#include <utility>

#include "../sensors/quadrature_encoder.h"
#include "../types/measurement.h"
#include "../types/status.h"
#include "../types/timestamp.h"

namespace interfaces {
bool operator==(const SensorInterfaceOptions& lhs, const SensorInterfaceOptions& rhs) { return true; }

SensorInterface::SensorInterface(const sensors::QuadratureEncoder& encoder_1,
                                 const sensors::QuadratureEncoder& encoder_2, const SensorInterfaceOptions& options)
    : encoder_1_{encoder_1}, encoder_2_{encoder_2}, options_{options}, active_{false}, timestamp_{} {}

types::Status SensorInterface::open() {
  if (isActive()) {
    encoder_1_.open();
    encoder_2_.open();
    return types::Status::PRECONDITION_FAILED;
  }

  active_ = true;
  const types::Status encoder_1_result{encoder_1_.open()};
  const types::Status encoder_2_result{encoder_2_.open()};
  write(types::Measurement{});

  if (types::Status::OKAY != encoder_1_result) {
    return encoder_1_result;
  }

  if (types::Status::OKAY != encoder_2_result) {
    return encoder_2_result;
  }

  return types::Status::OKAY;
}

types::Status SensorInterface::close() {
  if (!isActive()) {
    encoder_1_.close();
    encoder_2_.close();
    return types::Status::PRECONDITION_FAILED;
  }

  write(types::Measurement{});
  active_ = false;
  const types::Status encoder_1_result{encoder_1_.close()};
  const types::Status encoder_2_result{encoder_2_.close()};

  if (types::Status::OKAY != encoder_1_result) {
    return encoder_1_result;
  }

  if (types::Status::OKAY != encoder_2_result) {
    return encoder_2_result;
  }

  return types::Status::OKAY;
}

types::Status SensorInterface::write(const types::Measurement measurement) {
  if (!isActive()) {
    return types::Status::UNAVAILABLE;
  }

  const types::Status encoder_1_result{encoder_1_.write(measurement.encoder_1_pos)};
  const types::Status encoder_2_result{encoder_2_.write(measurement.encoder_2_pos)};
  timestamp_ = measurement.header.timestamp;

  if (types::Status::OKAY != encoder_1_result) {
    return encoder_1_result;
  }

  if (types::Status::OKAY != encoder_2_result) {
    return encoder_2_result;
  }

  return types::Status::OKAY;
}

const sensors::QuadratureEncoder& SensorInterface::getEncoder1() const { return encoder_1_; }

const sensors::QuadratureEncoder& SensorInterface::getEncoder2() const { return encoder_2_; }

const SensorInterfaceOptions& SensorInterface::getOptions() const { return options_; }

const types::Timestamp& SensorInterface::getTimestamp() const { return timestamp_; }

bool SensorInterface::isActive() const { return active_; }

types::Measurement SensorInterface::read() const {
  types::Measurement measurement;
  measurement.header.timestamp = timestamp_;
  measurement.encoder_1_pos = encoder_1_.read();
  measurement.encoder_2_pos = encoder_2_.read();

  return measurement;
}

bool operator==(const SensorInterface& lhs, const SensorInterface& rhs) {
  return std::make_tuple(lhs.getEncoder1(), lhs.getEncoder2(), lhs.getOptions()) ==
         std::make_tuple(rhs.getEncoder1(), rhs.getEncoder2(), rhs.getOptions());
}
}  // namespace interfaces
