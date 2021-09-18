::@echo off
:: This script is used by the CI\Build machine to build the Windows test
:: projects
::
:: usage: build_all_windoze.bat <buildType> <buildNumber>
::

set _TOPDIR=%~dp0

:: Set Build info (and force build number to zero for "non-official" builds)
set BUILD_TYPE=%1
set BUILD_NUMBER=%2
IF %BUILD_TYPE%=="pr" set BUILD_NUMBER=0
IF %BUILD_TYPE%=="unknown" set BUILD_NUMBER=0
echo:
echo:BUILD TYPE=%BUILD_TYPE%, BUILD_NUMBER=%BUILD_NUMBER%
echo:

:: Run Doxygen first 
cd %_TOPDIR%
run_doxygen.py %BUILD_TYPE% %BUILD_NUMBER%
IF ERRORLEVEL 1 EXIT /b 1

:: Create the outcast workspace
cd
dir ..\
set cmd=orc.py mkwrk --clean ..\
echo:%cmd%
%cmd%

:: Get dependent packages
cd
set cmd=orc.py -v getdeps --rmlocal . 
echo:%cmd%
%cmd%

:: Build linux projects (under WSL)
:: Note: Because of Windows/Linux/Git newline issues - we brute force the shell scripts to have the correct newline characters
FOR /F "tokens=*" %%g IN ('%_TOPDIR%win2wsl %_TOPDIR%') do (SET WSL_TOPDIR=%%g)
wsl cd %WSL_TOPDIR%; dos2unix wsl_build.sh; cd ..; dos2unix env.sh; top/wsl_build.sh %BUILD_NUMBER%
IF ERRORLEVEL 1 EXIT /b 1

:: Build Visual Studio 32-bit projects
echo on
call %_TOPDIR%..\env.bat 1

cd %_TOPDIR%..\tests
%_TOPDIR%..\..\xpkgs\nqbp\other\bob.py  -v vc12 -t --bld-all --bldnum %BUILD_NUMBER%
IF ERRORLEVEL 1 EXIT /b 1

:: Run unit tests
cd %_TOPDIR%\..\tests
%_TOPDIR%..\..\xpkgs\nqbp\other\chuck.py -v --match a.exe --dir vc12
IF ERRORLEVEL 1 EXIT /b 1
%_TOPDIR%..\..\xpkgs\nqbp\other\chuck.py -v --match aa.exe --dir vc12
IF ERRORLEVEL 1 EXIT /b 1
%_TOPDIR%..\..\xpkgs\nqbp\other\chuck.py -v --match a.py --dir vc12
IF ERRORLEVEL 1 EXIT /b 1
%_TOPDIR%..\..\xpkgs\nqbp\other\chuck.py -v --match aa.py --dir vc12
IF ERRORLEVEL 1 EXIT /b 1

:: Everything worked!
exit /b 0
