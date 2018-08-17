@echo off

:: Validate appveyor's environment
if "%APPVEYOR_BUILD_FOLDER%"=="" (
  echo Please define 'APPVEYOR_BUILD_FOLDER' environment variable.
  exit /B 1
)

echo ============================================================================
echo Extracting French archive...
echo ============================================================================
cd /d %APPVEYOR_BUILD_FOLDER%\test\french
"C:\Program Files\7-Zip\7z" x french.zip
if %errorlevel% neq 0 exit /b %errorlevel%

::Return to launch folder
cd /d %~dp0
