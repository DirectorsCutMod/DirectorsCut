@echo off
echo Welcome to the [0m[1m[48;5;28m[38;5;192mDirector's Cut[0m Start Script!
set s_notdetected=[0m[38;5;9mNot Detected[0m
set s_detected=[0m[38;5;10mDetected[0m
echo Checking necessary files...
set junc_found=0
set sdkenginetools_found=0
set game_client_found=0
set game_server_found=0
set junc_path="C:\Program Files (x86)\Steam\steamapps\common\Source SDK Base 2013 Multiplayer\bin\directorscut\images\directorscut\directorscut_app.png"
set sdkenginetoolspath="C:\Program Files (x86)\Steam\steamapps\common\Source SDK Base 2013 Multiplayer\bin\x64\sdkenginetools.txt"
set game_client_path=..\sdk\game\mod_tf\bin\x64\client.dll
set game_server_path=..\sdk\game\mod_tf\bin\x64\server.dll
set junc_s=%s_notdetected%
set sdkenginetoolspath_s=%s_notdetected%
set game_client_s=%s_notdetected%
set game_server_s=%s_notdetected%
if exist %junc_path% set junc_found=1
if exist %sdkenginetoolspath% set sdkenginetools_found=1
if exist %game_client_path% set game_client_found=1
if exist %game_server_path% set game_server_found=1
if %junc_found% equ 1 set junc_s=%s_detected%
if %sdkenginetools_found% equ 1 set sdkenginetoolspath_s=%s_detected%
if %game_client_found% equ 1 set game_client_s=%s_detected%
if %game_server_found% equ 1 set game_server_s=%s_detected%
echo Director's Cut Junction: %junc_s% (looking for %junc_path%)
echo x64 sdkenginetools.txt: %sdkenginetoolspath_s% (looking for %sdkenginetoolspath%)
echo Frog Fortress 2 - Client: %game_client_s% (looking for %game_client_path%)
echo Frog Fortress 2 - Server: %game_server_s% (looking for %game_server_path%)
if %junc_found% equ 1 goto :next
set /p should_create=[43;30mWarning:[0m [33mThe Director's Cut Junction was not found, would you like to create it? (y/n)[0m 
if %should_create% equ y goto :junc_create
goto :next
:junc_create
echo Creating the Director's Cut Junction...
mklink /j "C:\Program Files (x86)\Steam\steamapps\common\Source SDK Base 2013 Multiplayer\bin\directorscut" ..\game\bin\directorscut
if errorlevel 1 (
    echo [7;31mError:[0m [31mCould not create junction. Missing permissions or invalid path? Did you install it?[0m
    goto :errored
)
echo Junction creation completed successfully.
:next
if %sdkenginetools_found% equ 1 goto :next2
set /p should_create_sdkenginetools=[43;30mWarning:[0m [33mThe x64 sdkenginetools.txt was not found, would you like to copy it? (y/n)[0m 
if %should_create_sdkenginetools% equ y goto :sdkenginetools_create
goto :next2
:sdkenginetools_create
echo Copying the x64 sdkenginetools.txt...
copy ..\game\bin\x64\sdkenginetools.txt "C:\Program Files (x86)\Steam\steamapps\common\Source SDK Base 2013 Multiplayer\bin\x64\sdkenginetools.txt"
if errorlevel 1 (
    echo [7;31mError:[0m [31mCould not copy sdkenginetools.txt. Missing permissions or invalid path? Did you install it?[0m
    goto :errored
)
echo x64 sdkenginetools.txt copied successfully.
:next2
if %game_client_found% equ 1 if %game_server_found% equ 1 goto :link_tf_bin
echo [7;31mError:[0m [31mCould not find binaries to Frog Fortress 2 (mod_tf). You must build the Client and Server projects.[0m
goto :errored
:link_tf_bin
set link_src_path=..\sdk\game\mod_tf\bin
set link_dst_path=..\game\directorscut\bin
set link_test_path=%link_dst_path%\x64\client.dll
if exist %link_test_path% goto :finished
set /p should_create_tf_bin=[43;30mWarning:[0m [33mWould you like to create a "bin" junction from mod_tf? This is required to run Director's Cut. (y/n) [0m
if %should_create_tf_bin% equ y goto :link_tf_bin_create
goto :finished
:link_tf_bin_create
echo Creating the Director's Cut "bin" folder junction...
mklink /j "%link_dst_path%" "%link_src_path%"
if errorlevel 1 (
    echo [7;31mError:[0m [31mCould not create junction for the mod_tf "bin" folder. Missing permissions or invalid path?[0m
    goto :errored
)
:errored
pause
:finished
echo Starting the game...
echo hl2_win64.exe -game "%cd%\..\game\directorscut" -novid -console -dev -allowdebug -sw -w 1280 -h 720 -windowed -tools -nop4
start "" "C:\Program Files (x86)\Steam\steamapps\common\Source SDK Base 2013 Multiplayer\hl2_win64.exe" -game "%cd%\..\game\directorscut" -novid -console -dev -allowdebug -sw -w 1280 -h 720 -windowed -tools -nop4
