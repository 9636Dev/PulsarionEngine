cmake_minimum_required(VERSION 3.27)
project(PulsarionWindowing)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PULSARION_WINDOWING_SOURCES
    src/PulsarionWindowing/Window.hpp
    src/PulsarionWindowing/Event/Event.hpp
    src/PulsarionWindowing/Event/Events.hpp
    src/PulsarionWindowing/Event/WindowEvent.hpp
    src/PulsarionWindowing/Event/KeyEvent.hpp
    src/PulsarionWindowing/Event/MouseEvent.hpp
    src/PulsarionWindowing/Event/KeyCodes.hpp
    src/PulsarionWindowing/Event/MouseCodes.hpp
)

if (PULSARION_RENDERER STREQUAL "Metal" OR PULSARION_RENDERER STREQUAL "OpenGL")
    set(PULSARION_WINDOWING_PLATFORM_SPECIFIC_SOURCES
        src/PulsarionWindowing/Glfw/GlfwWindow.cpp
        src/PulsarionWindowing/Glfw/GlfwWindow.hpp
    )
endif()

if (NOT DEFINED PULSARION_LIBRARY_TYPE)
    message(FATAL_ERROR "PULSARION_LIBRARY_TYPE is not defined, please include PulsarionCore first!")
    return()
endif()

if (NOT DEFINED PULSARION_RENDERER)
    message(FATAL_ERROR "PULSARION_RENDERER is not defined, please include PulsarionCore first!")
    return()
endif()

add_library(PulsarionWindowing ${PULSARION_LIBRARY_TYPE} ${PULSARION_WINDOWING_SOURCES} ${PULSARION_WINDOWING_PLATFORM_SPECIFIC_SOURCES})

target_include_directories(PulsarionWindowing PUBLIC src)

target_link_libraries(PulsarionWindowing PUBLIC Pulsarion::Core)
target_link_libraries(PulsarionWindowing PUBLIC Pulsarion::Math)

# Link GLFW if we are using Metal or OpenGL
if (PULSARION_RENDERER STREQUAL "Metal" OR PULSARION_RENDERER STREQUAL "OpenGL")
    add_subdirectory(vendor/glfw)
    # In the future make this PRIVATE
    target_link_libraries(PulsarionWindowing PUBLIC glfw) 
    target_compile_definitions(PulsarionWindowing PUBLIC PULSARION_WINDOWING_BACKEND_GLFW)
endif()