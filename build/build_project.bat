@echo off

@REM Save current directory
set CURR_DIR=%CD%

@REM Set current directory to script dir
cd /d %~dp0

set GENERATOR="Visual Studio 17 2022"
set BUILD_TYPE=Debug
set LIBRARY_TYPE=SHARED
set BUILD_DIR=..
set GENERATE_COMPILE_COMMANDS=0
set SIMD=SSE4.1

@REM Loop through each argument
for %%x in (%*) do (
   if "%%x" == "compile_commands" (
       set GENERATE_COMPILE_COMMANDS=1
       echo Generating compile_commands.json
   )
   if "%%x" == "release" (
       set BUILD_TYPE=Release
       echo Building release
   )

   if "%%x" == "static" (
       set LIBRARY_TYPE=STATIC
       echo Building static library
   )

   if "%%x" == "simd_sse4.1" (
       set SIMD=SSE4.1
   )

   if "%%x" == "simd_avx" (
         set SIMD=AVX
   )

   if "%%x" == "simd_none" (
         set SIMD=NONE
   )
)

@REM Build project
IF %GENERATE_COMPILE_COMMANDS% == 1 (
    @echo on
    cmake -G %GENERATOR% -DPULSARION_LIBRARY_TYPE=%LIBRARY_TYPE% -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DPULSARION_SIMD=%SIMD% -DCMAKE_EXPORT_COMPILE_COMMANDS=ON %BUILD_DIR%
    @echo off

    if exist "%BUILD_DIR%\compile_commands.json" (
        move "%BUILD_DIR%\compile_commands.json" %BUILD_DIR%
    )
) ELSE (
    @echo on
    cmake -G %GENERATOR% -DPULSARION_LIBRARY_TYPE=%LIBRARY_TYPE% -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DPULSARION_SIMD=%SIMD% %BUILD_DIR%
    @echo off
)

@REM Restore current directory
cd /d %CURR_DIR%
PAUSE
