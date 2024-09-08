@echo off
set qt_dir=.\tools\directorscut\qt
devtools\bin\vpc.exe /directorscut +tools /mksln tools.sln /define:VS2022
if not exist %qt_dir% goto qt_error
goto qt_success
:qt_error
echo [43;30mWarning:[0m [33mQt not detected, please run necessary batch files.[0m
goto end
:qt_success
echo [42;30mSuccess:[0m [32mQt detected, running MOC...[0m
.\qt_moc.bat
:end
