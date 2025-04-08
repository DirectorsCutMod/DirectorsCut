@echo off
echo Welcome to the [0m[1m[48;5;28m[38;5;192mDirector's Cut[0m Project Creator!
set s_notdetected=[0m[38;5;9mNot Detected[0m
set s_detected=[0m[38;5;10mDetected[0m
echo Checking dependencies...
set sdk_found=0
set qt_found=0
set sdk_path=..\sdk\src\devtools\bin\vpc.exe
set qt_path=C:\Qt\5.15.2\msvc2019_64\bin\Qt5Core.dll
set sdk_s=%s_notdetected%
set qt_s=%s_notdetected%
if exist %sdk_path% set sdk_found=1
if exist %qt_path% set qt_found=1
if %sdk_found% equ 1 set sdk_s=%s_detected%
if %qt_found% equ 1 set qt_s=%s_detected%
echo Source SDK: %sdk_s% (looking for %sdk_path%)
echo Qt: %qt_s% (looking for %qt_path%)
if %sdk_found% equ 0 echo [43;30mWarning:[0m [33mSource SDK was not detected, run "git submodule update --init" in the repository root.[0m
if %qt_found% equ 0 echo [43;30mWarning:[0m [33mQt 5.15.2 MSVC 2019 64-bit was not detected, install from Qt Community Edition.[0m
if %sdk_found% equ 0 goto :dep_fail
if %qt_found% equ 0 goto :dep_fail
goto :dep_success
:dep_fail
echo [7;31mError:[0m [31mOne or more dependencies were not met.[0m
goto :errored
:dep_success
echo [42;30mSuccess:[0m [32mDependencies were met.[0m
echo Checking junctions...
set j_qt_found=0
set j_devtools_found=0
set j_qt_src_path=C:\Qt\5.15.2\msvc2019_64
set j_devtools_src_path=..\sdk\src\devtools
set j_qt_dst_path=.\thirdparty\lgpl\qt\bin\Qt5Core.dll
set j_devtools_dst_path=.\devtools\bin\vpc.exe
set j_qt_s=%s_notdetected%
set j_devtools_s=%s_notdetected%
if exist %j_qt_dst_path% set j_qt_found=1
if exist %j_devtools_dst_path% set j_devtools_found=1
if %j_qt_found% equ 1 set j_qt_s=%s_detected%
if %j_devtools_found% equ 1 set j_devtools_s=%s_detected%
echo .\thirdparty\lgpl\qt: %j_qt_s%
echo .\devtools: %j_devtools_s%
if %j_qt_found% equ 0 echo [43;30mWarning:[0m [33m"qt" junction was not detected, it will be created.[0m
if %j_qt_found% equ 0 mkdir .\thirdparty\lgpl
if %j_qt_found% equ 0 mklink /j .\thirdparty\lgpl\qt %j_qt_src_path%
if not exist %j_qt_dst_path% goto :j_fail
if %j_devtools_found% equ 0 echo [43;30mWarning:[0m [33m"devtools" junction was not detected, it will be created.[0m
if %j_devtools_found% equ 0 mklink /j .\devtools %j_devtools_src_path%
if not exist %j_devtools_dst_path% goto :j_fail
goto :j_success
:j_fail
echo [7;31mError:[0m [31mCould not create a junction. Missing permissions?[0m
goto :errored
:j_success
echo [42;30mSuccess:[0m [32mJunctions are available.[0m
echo Creating project...
.\devtools\bin\vpc.exe /define:SOURCESDK +directorscut /mksln directorscut.sln
goto :finished
:errored
pause
:finished
