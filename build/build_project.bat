@echo off
@REM Set current directory to script dir
cd /d %~dp0

set GENERATOR="Visual Studio 17 2022"
set BUILD_TYPE="Debug"
set PULSARION_LIBRARY_TYPE="SHARED"
set BUILD_TARGET="x64"

@REM Build project
@echo on
cmake -A %BUILD_TARGET% -G %GENERATOR% -DPULSARION_LIBRARY_TYPE=%PULSARION_LIBRARY_TYPE% -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ..
PAUSE