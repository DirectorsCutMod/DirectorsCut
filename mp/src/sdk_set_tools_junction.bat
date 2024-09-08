@echo off
set out_dir=C:\Program Files (x86)\Steam\steamapps\common\Source SDK Base 2013 Multiplayer
:: Check to see if the junction already exists
if exist "%out_dir%\bin\tools\dxfm" goto exists
set dxfm_dir=..\game\bin\tools\dxfm
if not exist %dxfm_dir% goto no_sdk
echo This script will create a junction from the default Source SDK Base 2013 Multiplayer installation directory:
echo %out_dir%
echo Proceed? (y/n)
set /p confirm=
if not %confirm%==y goto cancelled
@echo on
mklink /j "%out_dir%\bin\tools\dxfm" %dxfm_dir%
@echo off
echo [42;30mSuccess:[0m [32mJunction finished.[0m
goto end
:exists
echo [7;31mError:[0m [31mThe junction already exists.[0m
goto end
:cancelled
echo [43;30mWarning:[0m [33mJunction cancelled.[0m
goto end
:no_sdk
echo [7;31mError:[0m [31mSource SDK Base 2013 Multiplayer is not installed to the default directory.[0m
:end
pause
