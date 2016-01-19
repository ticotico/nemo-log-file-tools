@echo off
set _system=4G
set _UE_num=3
set _strangh_upper=-93
set _noise_upper=15

setlocal enabledelayedexpansion

for %%a in (*.1.nmf) do (
	set _FileName=%%a
	for /F "tokens=1-4 delims=." %%A in ("!_FileName!") do (
		get_upper %%A %_UE_num% %_system% %_strangh_upper% %_noise_upper%
	)
	
)
