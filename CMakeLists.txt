cmake_minimum_required(VERSION 3.0)

project(pmsm)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-Wall  -g")
file(GLOB SOURCES src/*.cpp)

# add_executable(gtq_client ./example/gtq_client.cpp ${SOURCES})
# add_executable(gtq_server ./example/gtq_server.cpp ${SOURCES})
# add_executable(onestep_without_delay ./example/onestep_without_delay.cpp ${SOURCES})
# add_executable(pmsm_controller ./example/pmsm_controller.cpp ${SOURCES})
# add_executable(pmsm_plant ./example/pmsm_plant.cpp ${SOURCES})
# add_executable(test_Eigen ./example/test_Eigen.cpp)
# add_executable(test_Eigen2 ./example/test_Eigen2.cpp)
# add_executable(test_Eigen3 ./example/test_Eigen3.cpp ${SOURCES})

# add_executable(sda_pmsm ./example/sda_pmsm.cpp ${SOURCES})

# 最小二乘法辨识
add_executable(parameter_identification_IRLS ./example/parameter_identification_IRLS.cc ${SOURCES})
target_include_directories(parameter_identification_IRLS PRIVATE ./)

# SVPWM测试
add_executable(svpwm_test ./example/svpwm_test.cpp  ${SOURCES})
target_include_directories(svpwm_test PRIVATE ./)

# add_executable(PMSM ./example/test_PMSM_model.cpp current_controller.cpp PMSM.cpp system.cpp inverter.cpp)
# add_executable(bool_test ./example/bool_test.cpp)
# add_executable(onestep_without_delay ./example/onestep_without_delay.cpp ${SOURCES})