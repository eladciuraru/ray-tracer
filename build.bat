@echo off

:: Config
set "ParentDir=%~dp0"
set "BuildDir=%ParentDir%\build"
set "SourceDir=%ParentDir%\src"
set "TestsDir=%ParentDir%\tests"

set "WarningsFlags=/W4 /WX /wd4204 /wd4101 /wd4100 /wd4200 /wd4201"
set "CommonCompilerFlags=/Z7 /Oi /MT /TC /nologo /I^"%SourceDir%^" ^
                         %WarningsFlags% /D_CRT_SECURE_NO_WARNINGS=1"
set "CommonLinkerFlags=/link renderer.obj"

:: Tools
set "CC=cl.exe"
set "LD=link.exe"

:: TODO: This doesn't work, try to solve this shit
:: Check and setup build tools if needed
:: where %CC% 2>&1 1>NUL || call shell.bat

if not exist "%BuildDir%" (
    echo [*] Creating %BuildDir%
    mkdir "%BuildDir%"
)

pushd %BuildDir%

echo.
echo [*] Building Renderer Code
%CC% %CommonCompilerFlags% /c "%SourceDir%\renderer\renderer.c"

echo.
echo [*] Building Tests
%CC% %CommonCompilerFlags% "%TestsDir%\tests.c" %CommonLinkerFlags%

echo.
echo [*] Building answers
%CC% %CommonCompilerFlags% "%SourceDir%\answers\answers.c" %CommonLinkerFlags%

popd
