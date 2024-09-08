@echo off
:: Check for symlink
if not exist tools\directorscut\qt goto no_symlink
echo Creating Qt meta object compiler files...
@echo on
tools\directorscut\qt\bin\moc.exe -o tools\directorscut\dxfm\qt_ui\aboutdialog.h.moc tools\directorscut\dxfm\qt_ui\aboutdialog.h
tools\directorscut\qt\bin\moc.exe -o tools\directorscut\dxfm\qt_ui\keyboardshortcutsdialog.h.moc tools\directorscut\dxfm\qt_ui\keyboardshortcutsdialog.h
tools\directorscut\qt\bin\moc.exe -o tools\directorscut\dxfm\qt_ui\matsyswindow.h.moc tools\directorscut\dxfm\qt_ui\matsyswindow.h
tools\directorscut\qt\bin\moc.exe -o tools\directorscut\dxfm\qt_ui\ui.h.moc tools\directorscut\dxfm\qt_ui\ui.h
tools\directorscut\qt\bin\moc.exe -o tools\directorscut\dxfm\qt_ui\viewportwindow.h.moc tools\directorscut\dxfm\qt_ui\viewportwindow.h
tools\directorscut\qt\bin\moc.exe -o tools\directorscut\dxfm\qt_ui\welcomewizarddialog.h.moc tools\directorscut\dxfm\qt_ui\welcomewizarddialog.h
@echo off
echo [42;30mSuccess:[0m [32mFinished creating Qt meta object compiler files.[0m
goto end
:no_symlink
echo [7;31mError:[0m [31mQt is not set up, run qt_set_junction.bat first.[0m
:end
pause
