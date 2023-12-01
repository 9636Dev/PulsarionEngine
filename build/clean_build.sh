#!/bin/sh
# Clean up the build directory

PROJECT_CLEAN_COMMAND="make clean"

# Set the project directory to current direcotory and go to the upper level
cd dirname $0
cd ..

# Clean up the build directory
$PROJECT_CLEAN_COMMAND

# Find and Clean the files recursively
find . -name "*.o" -exec rm -rf {} \;
find . -name "*.a" -exec rm -rf {} \;
find . -name "*.so" -exec rm -rf {} \;
find . -name "*.d" -exec rm -rf {} \;
find . -name "*.gch" -exec rm -rf {} \;
find . -name "*.elf" -exec rm -rf {} \;

# Clean up CMake Cache, and XCode project files
find . -name "CMakeCache.txt" -exec rm -rf {} \;
find . -name "CMakeFiles" -exec rm -rf {} \;
find . -name "cmake_install.cmake" -exec rm -rf {} \;
find . -name "CMakeScripts" -exec rm -rf {} \;
find . -name "Makefile" -exec rm -rf {} \;
find . -name "*.xcodeproj" -exec rm -rf {} \;
find . -name "*.xcworkspace" -exec rm -rf {} \;
