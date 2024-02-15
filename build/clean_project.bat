@echo off
REM Save current directory
set CURR_DIR=%CD%

REM Set the project directory to script dir and go to the upper level
cd /d %~dp0

REM Remove build directories and files for Ninja and Visual Studio
echo Removing build directories and files...

REM Remove common build directories
if exist bin rmdir /s /q bin
if exist lib rmdir /s /q lib
if exist build rmdir /s /q build

REM Remove project-specific directories
if exist PulsarionCore rmdir /s /q PulsarionCore
if exist PulsarionTests rmdir /s /q PulsarionTests
if exist PulsarionExamples rmdir /s /q PulsarionExamples
if exist PulsarionMath rmdir /s /q PulsarionMath
if exist PulsarionShaderLanguage rmdir /s /q PulsarionShaderLanguage
if exist PulsarionWindowing rmdir /s /q PulsarionWindowing
if exist PulsarionBenchmarks rmdir /s /q PulsarionBenchmarks
if exist PulsarionMedia rmdir /s /q PulsarionMedia
if exist _deps rmdir /s /q _deps
if exist CMakeFiles rmdir /s /q CMakeFiles

REM Remove CMake and Visual Studio generated files
del /f /q CMakeCache.txt
del /f /q cmake_install.cmake
del /f /q *.vcxproj
del /f /q *.vcxproj.filters
del /f /q *.sln
del /f /q *.user
del /f /q *.userprefs
del /f /q *.suo

REM Restore current directory
cd /d %CURR_DIR%

echo Clean complete.
