@echo off
setlocal enabledelayedexpansion

md have_GPS
md no_GPS
md newlog
set CUR_DIR="%cd%"
echo.

for %%a in ("%CUR_DIR%\have_GPS\*.nmf") do set have_GPS_log="%%a"
cd no_GPS
for %%b in (*.nmf) do (
  set no_GPS_log="%%b"
  set new_log="%CUR_DIR%\newlog\%%b"
  "%CUR_DIR%\GPS_transfer.exe" !new_log! !no_GPS_log! !have_GPS_log!
)

pause
