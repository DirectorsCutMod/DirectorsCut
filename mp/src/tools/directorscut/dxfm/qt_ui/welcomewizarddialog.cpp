#include "welcomewizarddialog.h"

#include "dxfm.h"

CWelcomeWizardDialog::CWelcomeWizardDialog(QWidget* pParent) : QDialog(pParent)
{
    setFixedSize(800, 430);
    setWindowTitle(" ");
    setModal(true);
    // disable what's this, window title, and minimize/maximize
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint & ~Qt::WindowMinMaxButtonsHint & ~Qt::WindowTitleHint);
}

#include "welcomewizarddialog.h.moc"
