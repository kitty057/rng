@echo off
setlocal EnableDelayedExpansion
set "newdir=%USERPROFILE%\bin\rng"
set "regkey=HKCU\Environment"
set "cpath="
for /f "tokens=2,*" %%a in ('C:\Windows\System32\reg.exe query "%regkey%" /v Path 2^>nul') do set "cpath=%%b"
if defined cpath (
    C:\Windows\System32\reg.exe add "%regkey%" /v Path_Backup /t REG_EXPAND_SZ /d "!cpath!" /f >nul
)
if defined cpath (
    echo !cpath! | C:\Windows\System32\findstr.exe /i /c:"%newdir%" >nul
    if not errorlevel 1 (
        echo already in path %newdir%
        goto :done
    )
    set "npath=!cpath!;%newdir%"
) else (
    set "npath=%newdir%"
)
C:\Windows\System32\reg.exe add "%regkey%" /v Path /t REG_EXPAND_SZ /d "!npath!" /f >nul
if errorlevel 1 (
    echo failed to update user path.
    exit /b 1
)
echo added to user path %newdir%
:done
echo.
echo close this command prompt and open a new command prompt for the new path to take effect
