cmake_minimum_required(VERSION 3.0)

project(pmsm)

set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc")
set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++")
add_compile_options(-Wall -g)

file(GLOB SOURCES src/*.cpp)
# add_executable(PMSM ./example/test_PMSM_model.cpp current_controller.cpp PMSM.cpp system.cpp inverter.cpp)
# add_executable(bool_test ./example/bool_test.cpp)
add_executable(onestep_without_delay ./example/onestep_without_delay.cpp ${SOURCES})
