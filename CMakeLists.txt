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
add_executable(test_Eigen3 ./example/test_Eigen3.cpp)







# add_executable(PMSM ./example/test_PMSM_model.cpp current_controller.cpp PMSM.cpp system.cpp inverter.cpp)
# add_executable(bool_test ./example/bool_test.cpp)
# add_executable(onestep_without_delay ./example/onestep_without_delay.cpp ${SOURCES})
