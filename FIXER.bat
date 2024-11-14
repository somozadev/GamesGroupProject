@echo off
setlocal

REM Set the working directory to the location of the script
set "WORK_DIR=%~dp0"

REM Change to the working directory
cd /d "%WORK_DIR%"

REM Delete folders and their contents
if exist "Binaries" (
    rmdir /s /q "Binaries"
)

if exist "Intermediate" (
    rmdir /s /q "Intermediate"
)

if exist "Saved" (
    rmdir /s /q "Saved"
)

REM Delete any .sln file
for %%f in (*.sln) do (
    del /q "%%f"
)
REM Set the project file name
set "PROJECT_FILE=GamesGroupProject.uproject"

REM Check if the project file exists
if exist "%PROJECT_FILE%" (
    REM Open the .uproject file with the default associated application (Unreal Engine)
    start "" "%PROJECT_FILE%"
) else (
    echo The file %PROJECT_FILE% was not found in this folder.
)
endlocal