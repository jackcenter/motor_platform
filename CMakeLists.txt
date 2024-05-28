cmake_minimum_required(VERSION 3.22)
project(motor_platform)

add_compile_options(-std=c++14)

find_package(GTest REQUIRED)
include(CTest)

include(FetchContent)
FetchContent_Declare(ArduinoJson
    GIT_REPOSITORY https://github.com/bblanchon/ArduinoJson.git
    GIT_TAG        v7.0.4
)
FetchContent_MakeAvailable(ArduinoJson)

include_directories(emb/core_task/src)
add_library(${PROJECT_NAME}_lib 
  emb/core_task/src/actuators/brushed_motor.cpp
  emb/core_task/src/applications/teleop.cpp
  emb/core_task/src/components/controller.cpp
  emb/core_task/src/components/controller_json_provider.cpp
  emb/core_task/src/components/platform.cpp
  emb/core_task/src/components/platform_json_provider.cpp
  emb/core_task/src/components/state_estimation.cpp
  emb/core_task/src/components/state_estimation_json_provider.cpp
  emb/core_task/src/config/hardware_config.cpp
  emb/core_task/src/config/teleop_config.cpp
  emb/core_task/src/interfaces/actuator_interface.cpp
  emb/core_task/src/interfaces/sensor_interface.cpp
  emb/core_task/src/sensors/quadrature_encoder.cpp
  emb/core_task/src/types/header.cpp
  emb/core_task/src/types/input.cpp
  emb/core_task/src/types/measurement.cpp
  emb/core_task/src/types/state.cpp
  emb/core_task/src/types/timestamp.cpp
  emb/core_task/src/utilities/serialize.cpp
  emb/core_task/src/utilities/time.cpp
)
target_link_libraries(${PROJECT_NAME}_lib ArduinoJson)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Testing
# Function to create gtests easily and avoid duplicate names (e.g., test_utils) by prefixing the file path.
function(add_project_gtest test_file_path test_file_prefix)
  string(REPLACE "/" "_" test_file_path_underscore ${test_file_path})
  add_executable(${test_file_path_underscore}_${test_file_prefix} ${test_file_path}/${test_file_prefix}.cpp)
  target_link_libraries(${test_file_path_underscore}_${test_file_prefix}
    GTest::gtest_main
    ${PROJECT_NAME}_lib
  )
  add_test(NAME ${test_file_path_underscore}_${test_file_prefix} COMMAND ${test_file_path_underscore}_${test_file_prefix})
endfunction()

add_project_gtest(emb/core_task/test/actuators test_brushed_motor)
add_project_gtest(emb/core_task/test/applications test_teleop)
add_project_gtest(emb/core_task/test/components test_controller)
add_project_gtest(emb/core_task/test/components test_controller_json_provider)
add_project_gtest(emb/core_task/test/components test_platform)
add_project_gtest(emb/core_task/test/components test_platform_json_provider)
add_project_gtest(emb/core_task/test/components test_state_estimation)
add_project_gtest(emb/core_task/test/components test_state_estimation_json_provider)
add_project_gtest(emb/core_task/test/interfaces test_actuator_interface)
add_project_gtest(emb/core_task/test/interfaces test_sensor_interface)
add_project_gtest(emb/core_task/test/sensors test_quadrature_encoder)
add_project_gtest(emb/core_task/test/utilities test_common)
add_project_gtest(emb/core_task/test/utilities test_serialize)
add_project_gtest(emb/core_task/test/utilities test_time)
