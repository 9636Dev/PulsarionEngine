cmake_minimum_required(VERSION 3.27)
project(PulsarionProject)

# PulsarionCore Dependencies
add_subdirectory(PulsarionCore)
add_subdirectory(PulsarionMath)

add_subdirectory(PulsarionTests)
add_subdirectory(PulsarionExamples)

add_library(Pulsarion::Math ALIAS PulsarionMath)
add_library(Pulsarion::Core ALIAS PulsarionCore)
