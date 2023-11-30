cmake_minimum_required(VERSION 3.27)
project(Pulsarion)
set(CMAKE_CXX_STANDARD 20)

set(PULSARION_SOURCES

)

add_library(Pulsarion ${PULSARION_LIBRARY_TYPE} ${PULSARION_SOURCES})

target_include_directories(Pulsarion PUBLIC include) # Public API, no internal use
target_include_directories(Pulsarion PUBLIC src)

target_link_libraries(Pulsarion PUBLIC Pulsarion::Core)
target_link_libraries(Pulsarion PUBLIC Pulsarion::Math)