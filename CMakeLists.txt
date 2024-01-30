cmake_minimum_rqeuired(VERSION 4.3)
set(This Main)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)
add_subdirectory(WildBlueberrySensorSystem/tests)

set(Headers
    Sensors/Sensor.h)

set(Sources
    Sensors/Sensor.cpp)

add_library(${This} STATIC ${Sources} ${Headers})
add_subdirectory(tests)




