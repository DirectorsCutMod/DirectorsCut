@echo off
set out_dir=C:\Program Files (x86)\Steam
:: Check to see if the junction already exists
if exist "%out_dir%\steamapps\sourcemods\directorscut" goto exists
set dxfm_dir=..\game\directorscut
if not exist %dxfm_dir% goto no_steam
echo This script will create a junction from the default Steam sourcemods path:
echo %out_dir%\steamapps\sourcemods
echo Proceed? (y/n)
set /p confirm=
if not %confirm%==y goto cancelled
@echo on
mklink /j "%out_dir%\steamapps\sourcemods\directorscut" %dxfm_dir%
@echo off
echo [42;30mSuccess:[0m [32mJunction finished.[0m
goto end
:exists
echo [7;31mError:[0m [31mThe junction already exists.[0m
goto end
:cancelled
echo [43;30mWarning:[0m [33mJunction cancelled.[0m
goto end
:no_steam
echo [7;31mError:[0m [31mSteam is not installed to the default directory.[0m
:end
pause
