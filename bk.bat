@echo off

if "%1" == "" (
    echo %%1 is empty
    exit /b 0
)

if exist "log\%1.json" (
    echo already exist
    exit /b 0
)

copy "build\data.json" "log\%1.json"
