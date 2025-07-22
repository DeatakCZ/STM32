@echo off
echo Starting continuous compilation (Ctrl+C to stop)...
:loop
make -q
if errorlevel 1 (
    echo Changes detected, rebuilding...
    make
) else (
    echo No changes detected
)
timeout /t 2 /nobreak >nul
goto loop 