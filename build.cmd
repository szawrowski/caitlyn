@echo off

setlocal enabledelayedexpansion

@REM Check if an argument is provided and validate it
if "%~1"=="" (
  @REM If no arguments are provided, set build type to Debug
  set "build_type=Debug"
  set "install=false"
) else (
  @REM Convert the argument to lowercase
  set "build_type=%~1"
  set "build_type=!build_type:~0,1!!build_type:~1!"

  @REM Check if the provided argument is either Release or Debug
  if /I "!build_type!"=="release" (
    set "build_type=Release"
  ) else if /I "!build_type!"=="debug" (
    set "build_type=Debug"
  ) else if /I "!build_type!"=="install" (
    set "install=true"
  ) else (
    echo Error: Invalid build type '%~1'.
    echo Please specify either 'Release' or 'Debug'.
    exit /b 1
  )
)

@REM Set build directory
set "build_dir=build\%build_type%"

if /I "!install!"=="true" (
  @REM Build type message
  echo Installation...

  cmake -S . -B %build_dir% -DLIB_INSTALL=ON
  cmake --install %build_dir%
) else (
  @REM Build type message
  echo Build type: %build_type%

  @REM Run cmake with the appropriate build type
  cmake -S . -B %build_dir% -G "Ninja" -DCMAKE_BUILD_TYPE=%build_type% -DDEVELOPMENT=ON

  @REM Build the targets
  cmake --build %build_dir% --parallel 16

  @REM Run tests
  ctest --test-dir "%build_dir%\test" --build-config Debug --output-on-failure --parallel 16
)

endlocal
