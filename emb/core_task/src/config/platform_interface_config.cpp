#include "platform_interface_config.h"

#include <ArduinoJson.h>

namespace config {
// cppcheck-suppress unusedFunction
JsonDocument getPlatformInterfaceConfig() {
  JsonDocument config_json{};
  config_json["actuator_interface"]["tb6612fng"]["options"]["PWMB"] = 14;
  config_json["actuator_interface"]["tb6612fng"]["options"]["BIN2"] = 15;
  config_json["actuator_interface"]["tb6612fng"]["options"]["BIN1"] = 16;
  config_json["actuator_interface"]["tb6612fng"]["options"]["STBY"] = 17;
  config_json["actuator_interface"]["tb6612fng"]["options"]["AIN1"] = 0;
  config_json["actuator_interface"]["tb6612fng"]["options"]["AIN2"] = 0;
  config_json["actuator_interface"]["tb6612fng"]["options"]["PWMA"] = 0;
  config_json["actuator_interface"]["options"]["min_voltage"] = -5.0;
  config_json["actuator_interface"]["options"]["max_voltage"] = 5.0;
  config_json["sensor_interface"]["quadrature_encoder_1"]["options"]["CH_A"] = 9;
  config_json["sensor_interface"]["quadrature_encoder_1"]["options"]["CH_B"] = 10;
  config_json["sensor_interface"]["quadrature_encoder_2"]["options"]["CH_A"] = 11;
  config_json["sensor_interface"]["quadrature_encoder_2"]["options"]["CH_B"] = 12;

  return config_json;
}
}  // namespace config
