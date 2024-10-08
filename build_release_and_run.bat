@echo off
set "orig_dir=%cd%"
call build_release.bat
cd /d "%orig_dir%"
cd build_release
start "" "powder.exe"
exit
