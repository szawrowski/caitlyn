@echo off

setlocal enabledelayedexpansion

set root=%cd%

@REM Check if vcpkg is installed
if not exist "%USERPROFILE%\vcpkg" (
  echo vcpkg is not installed locally.
  echo Installing vcpkg...

  cd %USERPROFILE%
  @REM Download vcpkg using Git
  git clone https://github.com/microsoft/vcpkg.git

  @REM Run the vcpkg installation script
  cd vcpkg
  .\bootstrap-vcpkg.bat

  echo vcpkg was successfuly installed.
  echo Please rerun this script.
)

@REM Installing dependencies

@REM Change to the vcpkg directory
cd "%USERPROFILE%\vcpkg"

@REM Detecting architecture
set "platform=%PROCESSOR_ARCHITECTURE%"
echo Current architecture: %platform%

if "%platform%"=="AMD64" (
  set "triplet=x64-windows"
) else if "%platform%"=="x86" (
  set "triplet=x86-windows"
) else (
  echo Unsupported platform: %platform%
  exit /b 1
)

@REM Set config
set "config=%root%\depends.conf"

@REM Check if the config exists
if not exist %config% (
  echo Error: %config% does not exist.
  exit /b 1
)

@REM Read the config
set "libs="
for /f "tokens=*" %%a in (%config%) do (
  set "libs=!libs!%%a "
)
set libs=%libs:~0,-1%

@REM Installing dependencies
.\vcpkg.exe install %libs% --triplet=%triplet%

endlocal
