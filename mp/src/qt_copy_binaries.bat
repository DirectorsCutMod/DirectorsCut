@echo off
:: Check for symlink
if not exist tools\directorscut\qt goto no_symlink
:: Ask for Debug or Release binaries
cls
goto noerror
:ask
cls
echo Invalid option, please try again.
echo.
:noerror
echo Select the type of Qt binaries to copy:
echo 1. Debug
echo 2. Release
set /p type=
if %type%==1 goto debug
if %type%==2 goto release
goto ask
:debug
@echo on
cp tools\directorscut\qt\bin\Qt53DAnimationd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DCored.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DExtrasd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DInputd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DLogicd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DQuickd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DQuickAnimationd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DQuickExtrasd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DQuickInputd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DQuickRenderd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DQuickScene2Dd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DRenderd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Bluetoothd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Concurrentd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Cored.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5DBusd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Designerd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5DesignerComponentsd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Gamepadd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Guid.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Helpd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Locationd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Multimediad.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5MultimediaQuickd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5MultimediaWidgetsd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Networkd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Nfcd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5OpenGLd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Positioningd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5PositioningQuickd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5PrintSupportd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Qmld.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Quickd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5QuickControls2d.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5QuickParticlesd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5QuickShapesd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5QuickTemplates2d.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5QuickTestd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5QuickWidgetsd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5RemoteObjectsd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Scxmld.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Sensorsd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5SerialBusd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5SerialPortd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Sqld.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Svgd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Testd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5TextToSpeechd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5WebChanneld.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5WebSocketsd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5WebViewd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Widgetsd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5WinExtrasd.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Xmld.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5XmlPatternsd.dll ..\game\bin\tools\dxfm
@echo off
echo [42;30mSuccess:[0m [32mDebug binaries finished copying.[0m
goto end
:release
@echo on
cp tools\directorscut\qt\bin\Qt53DAnimation.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DCore.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DExtras.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DInput.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DLogic.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DQuick.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DQuickAnimation.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DQuickExtras.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DQuickInput.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DQuickRender.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DQuickScene2D.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt53DRender.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Bluetooth.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Concurrent.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Core.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5DBus.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Designer.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5DesignerComponents.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Gamepad.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Gui.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Help.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Location.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Multimedia.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5MultimediaQuick.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5MultimediaWidgets.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Network.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Nfc.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5OpenGL.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Positioning.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5PositioningQuick.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5PrintSupport.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Qml.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Quick.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5QuickControls2.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5QuickParticles.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5QuickShapes.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5QuickTemplates2.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5QuickTest.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5QuickWidgets.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5RemoteObjects.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Scxml.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Sensors.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5SerialBus.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5SerialPort.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Sql.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Svg.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Test.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5TextToSpeech.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5WebChannel.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5WebSockets.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5WebView.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Widgets.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5WinExtras.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5Xml.dll ..\game\bin\tools\dxfm
cp tools\directorscut\qt\bin\Qt5XmlPatterns.dll ..\game\bin\tools\dxfm
@echo off
echo [42;30mSuccess:[0m [32mRelease binaries finished copying.[0m
goto end
:no_symlink
echo [7;31mError:[0m [31mQt is not set up, run qt_set_junction.bat first.[0m
:end
pause
