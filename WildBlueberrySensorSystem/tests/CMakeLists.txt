include(FecthContent)

FrecthContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)
FecthContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

set(This sensor_tests)

set(Sources
    Sensor_Test.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PRIVATE
    GTest::GTest
    Sensors
)

add_test(Testss ${This})