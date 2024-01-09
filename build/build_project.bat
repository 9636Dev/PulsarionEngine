@echo off
@REM Set current directory to script dir
cd /d %~dp0

set GENERATOR="Visual Studio 17 2022"
set BUILD_TYPE=Debug
set LIBRARY_TYPE=SHARED
set BUILD_DIR=..
set GENERATE_COMPILE_COMMANDS=

@REM Check for 'compile_commands' argument
if "%~1" == "compile_commands" (
    set GENERATE_COMPILE_COMMANDS=-DCMAKE_EXPORT_COMPILE_COMMANDS=ON
)

@REM Build project
@echo on
cmake -G %GENERATOR% -DPULSARION_LIBRARY_TYPE=%LIBRARY_TYPE% -DCMAKE_BUILD_TYPE=%BUILD_TYPE% %GENERATE_COMPILE_COMMANDS% %BUILD_DIR%
@echo off

@REM Move compile_commands.json to project root, if it was generated
if "%~1" == "compile_commands" (
    if exist "%BUILD_DIR%\compile_commands.json" (
        move "%BUILD_DIR%\compile_commands.json" %BUILD_DIR%
    )
)

PAUSE
