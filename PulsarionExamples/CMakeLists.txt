cmake_minimum_required(VERSION 3.27)
project(PulsarionExamples)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PULSARION_EXAMPLE_SOURCES
        src/Application.cpp
)

add_executable(PulsarionExamples ${PULSARION_EXAMPLE_SOURCES})

if (MSVC)
    set_property(TARGET PulsarionExamples PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
endif()

target_include_directories(PulsarionExamples PUBLIC src)

add_dependencies(PulsarionExamples Pulsarion::Windowing Pulsarion::ShaderLanguage)
target_link_libraries(PulsarionExamples PUBLIC Pulsarion::Core)
#target_link_libraries(PulsarionExamples PUBLIC Pulsarion::Math)
target_link_libraries(PulsarionExamples PUBLIC Pulsarion::Windowing)
target_link_libraries(PulsarionExamples PUBLIC Pulsarion::ShaderLanguage)
