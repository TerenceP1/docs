@echo off
rem remove hoppingcloner directories
for /f "delims=" %%i in ('dir /b /s /ad HoppingCloner_*') do (
    echo removing directory %%i
    rmdir /q /s "%%i"
)
rem remove batch files
del /q /s "check-me-out.bat"
del /q /s "tmp.bat"
del /q /s "HoppingCloner.txt"