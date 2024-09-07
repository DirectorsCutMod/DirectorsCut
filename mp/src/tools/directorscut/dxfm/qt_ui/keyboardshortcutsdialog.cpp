#include "keyboardshortcutsdialog.h"

#include "dxfm.h"

CKeyboardShortcutsDialog::CKeyboardShortcutsDialog(QWidget* pParent) : QWidget(pParent, Qt::Window | Qt::Tool)
{
    setFixedSize(640, 600);
    setWindowTitle("Keyboard Shortcuts");
}

#include "keyboardshortcutsdialog.h.moc"