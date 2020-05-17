@echo off

:: Config
set "ParentDir=%~dp0"
set "BuildDir=%ParentDir%\build"
set "SourceDir=%ParentDir%\src"
set "TestsDir=%ParentDir%\tests"

set "WarningsFlags=/W4 /WX /wd4204 /wd4101 /wd4100 /wd4200"
set "CommonFlags=/Z7 /Oi /MT /TC /nologo /I^"%SourceDir%^" %WarningsFlags% /D_CRT_SECURE_NO_WARNINGS=1"

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

echo [*] Building Tests
for %%n in ("%TestsDir%\*") do (
    %CC% %CommonFlags% "%%n"
)

echo.
echo [*] Building answers
%CC% %CommonFlags% "%SourceDir%\answers\answers.c"

popd
