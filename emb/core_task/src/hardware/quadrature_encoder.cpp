#include "quadrature_encoder.h"

#include <Arduino.h>
#include <Encoder.h>

namespace hardware
{
QuadratureEncoder::QuadratureEncoder(const QuadratureEncoderOptions& options)
: options_{ options }
, encoder_{ Encoder(options_.CH_A, options_.CH_B) }
{
  pinMode(options_.CH_A, INPUT_PULLUP);
  pinMode(options_.CH_B, INPUT_PULLUP);
}

void QuadratureEncoder::open()
{
  write(0);
}

long int QuadratureEncoder::read()
{
  return encoder_.read();
}

void QuadratureEncoder::write(const long int val)
{
  encoder_.write(val);
}

const QuadratureEncoderOptions& QuadratureEncoder::getOptions() const
{
  return options_;
}
}