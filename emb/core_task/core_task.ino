#include <cmath>
#include <string>
#include <utility>

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Encoder.h>

#include "src/applications/teleop.h"
#include "src/components/controller.h"
#include "src/components/controller_json_provider.h"
#include "src/components/platform.h"
#include "src/components/platform_json_provider.h"
#include "src/components/state_estimation.h"
#include "src/components/state_estimation_json_provider.h"
#include "src/config/hardware_config.h"
#include "src/config/teleop_config.h"
#include "src/hardware/tb6612fng.h"
#include "src/hardware/tb6612fng_json_provider.h"
#include "src/hardware/button.h"
#include "src/hardware/button_json_provider.h"
#include "src/types/common.h"
#include "src/types/status.h"
#include "src/types/timestamp.h"
#include "src/utilities/serialize.h"

volatile bool PRINT_FLAG{false};

int main() {
  const unsigned long control_cycle_period_ms{2};

  IntervalTimer print_timer;
  print_timer.begin(setPrintFlag, 1e5);

  Serial.begin(9600);

  const JsonDocument hardware_config{config::loadHardwareConfig()};

  Encoder encoder_1{hardware_config["encoder_1"]["channel_a"], hardware_config["encoder_1"]["channel_b"]};
  Encoder encoder_2{hardware_config["encoder_2"]["channel_a"], hardware_config["encoder_2"]["channel_b"]};

  hardware::Tb6612fngJsonProvider tb6612fng_json_provider{};
  hardware::Tb6612fng tb6612fng{tb6612fng_json_provider.provide(hardware_config["tb6612fng"])};
  tb6612fng.open();

  pinMode(hardware_config["led"]["pin"], OUTPUT);
  bool led_level = false;

  hardware::ButtonJsonProvider button_provider{};
  hardware::Button red_button{button_provider.provide(hardware_config["button_1"])};
  hardware::Button black_button{button_provider.provide(hardware_config["button_2"])};

  const JsonDocument teleop_config{config::loadTeleopConfig()};

  components::PlatformJsonProvider platform_json_provider{};
  components::Platform platform{platform_json_provider.provide(teleop_config["platform"])};

  components::ControllerJsonProvider controller_provider{};
  components::Controller controller{controller_provider.provide(teleop_config["controller"])};

  components::StateEstimationJsonProvider state_estimation_provider{};
  components::StateEstimation state_estimation{state_estimation_provider.provide(teleop_config["state_estimation"])};

  // TODO: application provider and config
  applications::TeleopOptions teleop_options{};
  applications::Teleop teleop_application{platform, controller, state_estimation, teleop_options};

  for (;;) {
    types::Timestamp cycle_start_timestamp{micros()};
    digitalWrite(hardware_config["led"]["pin"], led_level);
    led_level = led_level ? false : true;

    types::Measurement measurement_update;
    measurement_update.encoder_1_pos = encoder_1.read();
    measurement_update.encoder_2_pos = encoder_2.read();
    measurement_update.header.timestamp = cycle_start_timestamp;

    teleop_application.write(measurement_update);

    if (red_button() && teleop_application.isActive()) {
      teleop_application.close();
    }

    if (black_button() && !teleop_application.isActive()) {
      teleop_application.open();
    }

    teleop_application.cycle(cycle_start_timestamp);
    const types::Input input_update{teleop_application.read()};

    tb6612fng.write(types::Channel::B, input_update.voltage);

    if (PRINT_FLAG && teleop_application.isActive()) {
      const applications::TeleopState teleop_state{teleop_application.getState()};

      JsonDocument doc1{};
      doc1["input"] = utilities::serialize(teleop_state.input);
      serializeJson(doc1, Serial);
      Serial.println();

      JsonDocument doc2{};
      doc2["measurement"] = utilities::serialize(teleop_state.measurement);
      serializeJson(doc2, Serial);
      Serial.println();

      JsonDocument doc3{};
      doc3["state"] = utilities::serialize(teleop_state.state);
      serializeJson(doc3, Serial);
      Serial.println();

      PRINT_FLAG = false;
    }

    const unsigned long current_cycle_duration_ms{millis() - cycle_start_timestamp.toMilliseconds()};
    if ((current_cycle_duration_ms) < control_cycle_period_ms) {
      const unsigned long cycle_time_remaining_ms{control_cycle_period_ms - current_cycle_duration_ms};
      delay(cycle_time_remaining_ms);
    }

    yield();
  }

  return 0;
}

void setPrintFlag() { PRINT_FLAG = true; }
