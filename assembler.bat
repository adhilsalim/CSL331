@echo off

rem Compile and run pass_1.c
gcc pass_1.c -o pass_1.exe
if errorlevel 1 (
    echo Compilation of pass_1.c failed.
    pause
    exit /b 1
)
pass_1.exe

rem Compile and run pass_2.c
gcc pass_2.c -o pass_2.exe
if errorlevel 1 (
    echo Compilation of pass_2.c failed.
    pause
    exit /b 1
)
pass_2.exe

echo Assembly process completed successfully.
pause
exit /b 0