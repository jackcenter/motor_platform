cmake_minimum_required(VERSION 3.22)
project(motor_platform)

add_compile_options(-std=c++14)

find_package(GTest REQUIRED)
include(CTest)

include(FetchContent)
FetchContent_Declare(ArduinoJson
    GIT_REPOSITORY https://github.com/bblanchon/ArduinoJson.git
    GIT_TAG        v6.21.5
)
FetchContent_MakeAvailable(ArduinoJson)

include_directories(emb/core_task/src)
add_library(${PROJECT_NAME}_lib 
  emb/core_task/src/interfaces/state_estimation_interface.cpp
  emb/core_task/src/types/timestamp.cpp
  emb/core_task/src/utilities/serialize.cpp
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

add_project_gtest(emb/core_task/test/interfaces test_state_estimation_interface)
add_project_gtest(emb/core_task/test/types test_timestamp)
add_project_gtest(emb/core_task/test/utilities test_common)
add_project_gtest(emb/core_task/test/utilities test_serialize)
