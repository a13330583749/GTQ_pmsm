cmake_minimum_required(VERSION 3.0)

project(pmsm)

add_executable(PMSM ./example/test_PMSM_model.cpp current_controller.cpp PMSM.cpp system.cpp inverter.cpp)
