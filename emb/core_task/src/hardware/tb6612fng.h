#ifndef HARDWARE_TB6612FNG_H
#define HARDWARE_TB6612FNG_H

#include <stdint.h>
#include <utility>

#include "../types/common.h"
#include "../types/status.h"

namespace hardware
{
struct Tb6612fngOptions
{
  uint8_t PWMB;
  uint8_t BIN2;
  uint8_t BIN1;
  uint8_t STBY;
  uint8_t AIN1;
  uint8_t AIN2;
  uint8_t PWMA;
};

class Tb6612fng
{
public:
  explicit Tb6612fng(const Tb6612fngOptions& options);
  
  void open() const;
  void close() const;
  uint8_t read() const;
  types::Status write(const types::Channel channel, const bool input_1, const bool input_2, const int pwm_value) const;

private:
  Tb6612fngOptions options_;
  std::pair<uint8_t,uint8_t> pwm_range{ 0, 255 };
};
}

#endif  // HARDWARE_TB6612FNG_H