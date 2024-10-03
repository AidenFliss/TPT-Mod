@echo off
set folder="build-debug-vs"

:: Check if the folder exists
if not exist %folder% (
    echo Folder %folder% does not exist, skipping deletion...
    goto skip_deletion
)

cd /d %folder% || exit /b 1

:: Delete everything inside the folder, including the .vs folder
for /F "delims=" %%i in ('dir /b /a') do (
    rmdir "%%i" /s /q 2>nul || del "%%i" /s /q 2>nul
)

:: Move back to the parent directory and delete the main folder
cd ..
rmdir %folder% /s /q 2>nul

:skip_deletion
:: Setup the new build target
meson setup --backend=vs -Dbackend_startup_project=powder build-debug-vs

@echo Press Enter to exit... & pause >nul
