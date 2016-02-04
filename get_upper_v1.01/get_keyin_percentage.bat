@echo off
set /p _system=input system(3G/4G): 
set /p _UE_num=input number of UE: 
set /p _strangh_upper=input power (dBm): 
set /p _noise_upper=input noise (dB): 
set /p _save_as_filename=input filename (.csv): 

setlocal enabledelayedexpansion

for %%a in (*.1.nmf) do (
	set _FileName=%%a
	for /F "tokens=1-4 delims=." %%A in ("!_FileName!") do (
		get_upper %%A %_UE_num% %_system% %_strangh_upper% %_noise_upper%
	)
	
)

rename Newfile.csv %_save_as_filename%.csv
