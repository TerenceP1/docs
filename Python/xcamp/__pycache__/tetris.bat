@echo off
cls
for /f "tokens=2 delims=:" %%a in ('mode con ^| findstr "Columns"') do set cols=%%a
for /f "tokens=2 delims=:" %%a in ('mode con ^| findstr "Lines"') do set rows=%%a

:: Trim spaces
set cols=%cols: =%
set rows=%rows: =%

echo Columns: %cols%
echo Rows: %rows%
timeout /t 1 > nul
:: draw border
cls
set "tb="
setlocal enabledelayedexpansion
for /l %%i in (1,1,%cols%) do (
    set "tb=!tb!#"
)
echo %tb%
set "bd=#"
set /a "rw2 = %rows% - 2"
set /a "cl2 = %cols% - 2"
for /l %%i in (1,1,%cl2%) do (
    set "bd=!bd! "
)
set "bd=%bd%#"
for /l %%i in (1,1,%rw2%) do (
    echo %bd%
)
<nul set /p=%tb%
timeout /t 1 > nul
::move stuff around
set "xpos=1"
set "ypos=1"
<nul set /p=[30m
for /l %%r in (1,1,%rows%) do (
    for /l %%c in (1,1,%cols%) do (
            <nul set /p "dump=`"
    )
    if NOT %%r==%rows% echo.
)
set /a "r1=%rows%-1"
set /a "c1=%cols%-1"
>tmp.ps1 (
    @echo off
    echo Add-Type -AssemblyName System.Windows.Forms
    echo.
    echo while (^$true^) {
    echo     [System.Windows.Forms.SendKeys]::SendWait("s"^)
    echo     Start-Sleep -Seconds 1
    echo }
)
start /b powershell -ExecutionPolicy Bypass -File tmp.ps1
:loop

:: powershell -Command "$Host.UI.RawUI.CursorPosition = @{X=0;Y=0}"


<nul set /p=[%ypos%;%xpos%H
<nul set /p=[44m
<nul set /p=[34m
<nul set /p=`
<nul set /p=[0m
<nul set /p=[30m
choice /c WASD /n >nul
set "key=%errorlevel%"
if %key%==1 (
    if %ypos% gtr 0 (<nul set /p=[%ypos%;%xpos%H
<nul set /p=`
        set /a "ypos=%ypos%-1")
)
if %key%==3 (
    if %ypos% LSS %r1% (<nul set /p=[%ypos%;%xpos%H
<nul set /p=`
        set /a "ypos=%ypos%+1")
)
if %key%==2 (
    if %xpos% gtr 0 (<nul set /p=[%ypos%;%xpos%H
<nul set /p=`
        set /a "xpos=%xpos%-1")
)
if %key%==4 (
    if %xpos% LSS %c1% (<nul set /p=[%ypos%;%xpos%H
<nul set /p=`
        set /a "xpos=%xpos%+1")
)
goto:loop