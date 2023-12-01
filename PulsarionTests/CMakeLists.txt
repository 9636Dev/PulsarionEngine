cmake_minimum_required(VERSION 3.27)
project(PulsarionTests)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

set(PULSARION_TEST_SOURCES
        src/VectorTests.cpp
        src/MatrixTests.cpp
        src/QuaternionTests.cpp
)
add_executable(PulsarionTests ${PULSARION_TEST_SOURCES})

target_link_libraries(PulsarionTests PRIVATE Pulsarion::Core)
target_link_libraries(PulsarionTests PRIVATE Pulsarion::Math)
target_link_libraries(PulsarionTests PRIVATE gtest_main)

gtest_discover_tests(PulsarionTests)
