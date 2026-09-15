@echo off
setlocal
set SCRIPT_DIR=%~dp0
powershell -Command "Start-Process '%SCRIPT_DIR%run.bat' -Verb RunAs"