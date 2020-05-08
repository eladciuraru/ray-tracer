:: Helper script to auto setup environment variable for the build tools
:: using vswhere.exe
@echo off

setlocal EnableDelayedExpansion


set "_VsWhereExe=.\vendors\microsoft\vswhere.exe"
set "_FindToolsCmd=%_VsWhereExe% -latest -legacy -property installationPath"

for /f "usebackq delims=" %%i in (`%_FindToolsCmd%`) do (
    set "_VsDevCmd=%%i\common7\tools\vsdevcmd.bat"
    if not exist "!_VsDevCmd!" (
        echo [!] Failed to locate build tools
    )
)

%comspec% /k "%_VsDevCmd%" -arch=x64
