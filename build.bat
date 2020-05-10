@echo off

:: Config
set "ParentDir=%~dp0"
set "BuildDir=%ParentDir%\build"
set "SourceDir=%ParentDir%\src"
set "TestsDir=%ParentDir%\tests"

set "WarningsFlags=/W4 /WX /wd4204 /wd4101 /wd4100"
set "CommonFlags=/Z7 /Oi /MT /TC /nologo /I^"%SourceDir%^" %WarningsFlags%"

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

:: Unit tests
pushd %BuildDir%

%CC% %CommonFlags% "%TestsDir%\test_renderer_vector.c"

%CC% %CommonFlags% "%SourceDir%\answers\answers.c"

popd
