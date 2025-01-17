@echo off
:: This script is used to set compiler environment.
::
:: NOTE: The scripts in the top/compilers directory MUST be customized for PC.
::       (only the compilers that you use need to be customized)
::
:: Usage: env [<compiler>]

set _HERE=%~dp0

:: Set the NQBP_BIN path
set NQBP_PKG_ROOT=%_HERE%
set NQBP_WORK_ROOT=%_HERE%..\
set NQBP_XPKGS_ROOT=%_HERE%xsrc
set NQBP_BIN=%NQBP_XPKGS_ROOT%\nqbp

:: Make sure the Outcast environment is setup.  Assumes that the Outcast batch file is in command path
call outcast.bat

:: Set helper macros
doskey top=cd %_HERE%
doskey t=cd %_HERE%
doskey bob=%NQBP_XPKGS_ROOT%\nqbp\other\bob.py $*
doskey chuck=%NQBP_XPKGS_ROOT%\nqbp\other\chuck.py $*
doskey whatcc=echo:%PIM_ENV_COMPILER%
doskey killpy=taskkill /F /IM python.exe
doskey gitchmodx=git update-index --chmod=+x $*
doskey setexe=git update-index --chmod=+x $*
doskey ports=reg query HKLM\HARDWARE\DEVICEMAP\SERIALCOMM


:: No compiler option selected
IF "/%1"=="/" GOTO :displaycc


:: Set the compiler toolchain
pushd %_HERE%top
call compiler-list.bat %1
popd
exit /b 0

:: display compiler options
:displaycc
IF "/%PIM_ENV_COMPILER%"=="/"     echo:NO TOOLCHAIN SET
IF NOT "/%PIM_ENV_COMPILER%"=="/" echo:Current toolchain: %PIM_ENV_COMPILER%
echo:
pushd %_HERE%top
call compiler-list.bat
popd
exit /b 0
