@if \%1 == \ echo you must give a version number like MKZIP 010
@if \%1 == \ goto end

set _flistv=readme.txt mKEYB.C mKEYBR.C mKEYBA.ASM mKEYB.H prf.c portab.h makefile build.bat mkzip.bat
set _flistv2=keyb.exe history.txt mkeyb.lsm license.txt mkeyb.htm
set _flistx=keydef*.h


for %%i in (%_flistv%) do if not exist %%i echo %%i is missing && goto error_missing_file
for %%i in (%_flistv2%) do if not exist %%i echo %%i is missing && goto error_missing_file

                    pkzip MKEYB%1 %_flistv%
if not errorlevel 1 pkzip MKEYB%1 %_flistv2%
if not errorlevel 1 pkzip MKEYB%1 %_flistx%
if not errorlevel 1 ren MKEYB%1.zip mkeyb%1.zip
if not errorlevel 1 copy mkeyb%1.zip \ntsource\snapshot\help\freedos\mkeyb.zip /y
if not errorlevel 1 copy mkeyb%1.zip mkeyb.zip /y
if not errorlevel 1 goto end   




@echo error: while zipping
@goto end

:error_missing_file
@echo error: at least one file was missing
:end
@set _flistv=
@set _flistv2=
@set _flistx=
