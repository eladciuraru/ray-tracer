@echo off

:: Config
set "ParentDir=%~dp0"
set "BuildDir=%ParentDir%\build"
set "SourceDir=%ParentDir%\src"

set "CCFlags=/TC /Wall /WX /nologo /I^"%SourceDir%^" /wd4668 /wd4710"

:: Tools
set "CC=cl.exe"
set "LD=link.exe"

:: Check and setup build tools if needed
where %CC% >NUL
if not %ErrorLevel%==0 (
    call build.bat
)

if not exist "%BuildDir%" (
    echo [*] Creating %BuildDir%
    mkdir "%BuildDir%"
)

pushd %BuildDir%

%CC% %CCFlags% "%SourceDir%\renderer\renderer.c"

popd
