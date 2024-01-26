#ifndef HARDWARE_TB6612FNG_H
#define HARDWARE_TB6612FNG_H

#include <optional>
#include <utility>

namespace hardware
{
enum Channel { A, B };

enum StatusTypes { 
  OKAY,
  RANGE,
  UNAVAILABLE,
  UNKNOWN
};

struct Tb6612fngOptions
{
  uint PWMB;
  uint BIN2;
  uint BIN1;
  uint STBY;
  uint AIN1;
  uint AIN2;
  uint PWMA;
};

class Tb6612fng
{
public:
  Tb6612fng(const Tb6612fngOptions& options);
  
  void open();
  void close();
  uint read() const;
  StatusTypes write(const Channel channel, const bool input_1, const bool input_2, const int pwm_value);

private:
  Tb6612fngOptions options_;
  std::pair<uint,uint> pwm_range{ 0, 255 };
};
}

#endif HARDWARE_TB6612FNG_H