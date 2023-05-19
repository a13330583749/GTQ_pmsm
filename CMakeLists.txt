cmake_minimum_required(VERSION 3.0)

project(pmsm)
set(CMAKE_CXX_FLAGS "-Wall  -g")

add_executable(PMSM ./example/test_PMSM_model.cpp current_controller.cpp PMSM.cpp system.cpp inverter.cpp)
add_executable(bool_test ./example/bool_test.cpp)