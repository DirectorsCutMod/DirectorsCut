@echo off
set out_dir=.\tools\directorscut\qt
:: Check to see if the junction already exists
if exist %out_dir% goto exists
set qt_dir=C:\Qt\5.15.2\msvc2019
if not exist %qt_dir% goto no_qt
echo This script will create a junction to the Qt directory:
echo %qt_dir%
echo Proceed? (y/n)
set /p confirm=
if not %confirm%==y goto cancelled
@echo on
mklink /j %out_dir% %qt_dir%
@echo off
echo [42;30mSuccess:[0m [32mJunction finished.[0m
goto end
:exists
echo [7;31mError:[0m [31mThe junction already exists.[0m
goto end
:cancelled
echo [43;30mWarning:[0m [33mJunction cancelled.[0m
goto end
:no_qt
echo [7;31mError:[0m [31mQt is not installed to the default directory.[0m
:end
pause
