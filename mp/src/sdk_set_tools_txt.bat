@echo off
set root=C:\Program Files (x86)\Steam\steamapps\common\Source SDK Base 2013 Multiplayer\bin
set out=%root%\sdkenginetools.txt
:: Check to see if the file exists
if not exist "%out%" goto not_exists
set backup=%out%.bak
if exist "%backup%" goto already_backup
echo This script will add dxfm to sdkenginetools.txt in the default Source SDK Base 2013 Multiplayer installation directory:
echo %root%
echo Proceed? (y/n)
set /p confirm=
if not %confirm%==y goto cancelled
@echo on
:: Create a backup of the file
copy "%out%" "%backup%"
@echo off
(
echo "enginetools"
echo {
echo     "library"	"tools/commedit.dll"
echo     "library"	"tools/pet.dll"
echo     "library"	"tools/vmt.dll"
echo     "library"	"tools/dxfm/dxfm.dll"
echo }
) > "%out%"
echo [42;30mSuccess:[0m [32mWrite and backup finished.[0m
goto end
:cancelled
echo [43;30mWarning:[0m [33mWrite and backup cancelled.[0m
goto end
:already_backup
echo [7;31mError:[0m [31mThe backup file already exists, this script has already been run.[0m
goto end
:not_exists
echo [7;31mError:[0m [31mThe sdkenginetools.txt does not exist.[0m
goto end
:end
pause
