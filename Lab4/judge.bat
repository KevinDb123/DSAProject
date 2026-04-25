@echo off
powershell -ExecutionPolicy Bypass -File "%~dp0judge.ps1"
exit /b %ERRORLEVEL%
