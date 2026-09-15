@echo off
setlocal

REM ─────────────────────────────
REM 현재 스크립트 경로 기준으로 run.bat 찾기
REM ─────────────────────────────
set "APPDIR=%~dp0"
set "TARGET=%APPDIR%run.bat"

REM ─────────────────────────────
REM 관리자 권한 체크
REM ─────────────────────────────
net session >nul 2>&1
if %errorlevel% neq 0 (
    powershell -NoProfile -ExecutionPolicy Bypass -Command ^
        "Start-Process '%~f0' -Verb RunAs"
    exit /b
)

REM ─────────────────────────────
REM 관리자 권한으로 기본 텍스트 편집기로 run.bat 열기
REM - Verb Edit : 등록된 기본 텍스트 편집기 사용 (보통 메모장)
REM ─────────────────────────────
powershell -NoProfile -ExecutionPolicy Bypass -Command ^
    "Start-Process -Verb Edit -FilePath ('%TARGET%')"

endlocal
exit /b