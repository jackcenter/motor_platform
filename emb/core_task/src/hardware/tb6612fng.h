#ifndef HARDWARE_TB6612FNG_H
#define HARDWARE_TB6612FNG_H

#include <stdint.h>
#include <utility>

namespace hardware
{
enum Channel { A, B };

enum StatusTypes { 
  OKAY,
  OUT_OF_RANGE,
  UNAVAILABLE,
  UNKNOWN
};

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
  Tb6612fng(const Tb6612fngOptions& options);
  
  void open();
  void close();
  uint8_t read() const;
  StatusTypes write(const Channel channel, const bool input_1, const bool input_2, const int pwm_value) const;

private:
  Tb6612fngOptions options_;
  std::pair<uint8_t,uint8_t> pwm_range{ 0, 255 };
};
}

#endif  // HARDWARE_TB6612FNG_H