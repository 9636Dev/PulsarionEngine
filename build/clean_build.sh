#!/bin/sh
# Clean up the build directory

PROJECT_CLEAN_COMMAND="make clean"

# Set the project directory to current directory and go to the upper level
cd "$(dirname "$0")"

# Clean up the build directory, ignore if it fails
$PROJECT_CLEAN_COMMAND > /dev/null 2>&1

rm -rf bin
rm -rf lib

rm -rf PulsarionCore
rm -rf PulsarionTests
rm -rf PulsarionExamples
rm -rf PulsarionMath
rm -rf PulsarionShaderLanguage
rm -rf PulsarionWindowing
rm -rf PulsarionBenchmarks
rm -rf PulsarionMedia

rm Makefile
rm CMakeCache.txt
rm cmake_install.cmake
rm -rf CMakeFiles
