cmake_minimum_required(VERSION 3.22)
project(motor_platform)

add_compile_options(-std=c++14)

find_package(GTest REQUIRED)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Testing
include(CTest)

# Function to create gtests easily and avoid duplicate names (e.g., test_utils) by prefixing the file path.
function(add_project_gtest test_file_path test_file_prefix)
  string(REPLACE "/" "_" test_file_path_underscore ${test_file_path})
  add_executable(${test_file_path_underscore}_${test_file_prefix} ${test_file_path}/${test_file_prefix}.cpp)
  target_link_libraries(${test_file_path_underscore}_${test_file_prefix}
    GTest::gtest_main
  )
  add_test(NAME ${test_file_path_underscore}_${test_file_prefix} COMMAND ${test_file_path_underscore}_${test_file_prefix})
endfunction()

add_project_gtest(emb/core_task/test/utilities test_common)
