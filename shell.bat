:: Helper script to auto setup environment variable for the build tools
:: using vswhere.exe
@echo off

setlocal EnableDelayedExpansion


set "_VsWhereExe=.\vendors\microsoft\vswhere.exe"
set "_FindToolsCmd=%_VsWhereExe% -latest -legacy -property installationPath"

for /f "usebackq delims=" %%i in (`%_FindToolsCmd%`) do (
    :: set "_VsDevCmd=%%i\common7\tools\vsdevcmd.bat"
    set "_VsDevCmd=%%i\VC\Auxiliary\Build\vcvars64.bat"
    if not exist "!_VsDevCmd!" (
        echo [^^!] Failed to locate script to setup build tools
        echo [^^!]   Should have been at: "%_VsDevCmd%"
    )
)

%comspec% /k "%_VsDevCmd%"
