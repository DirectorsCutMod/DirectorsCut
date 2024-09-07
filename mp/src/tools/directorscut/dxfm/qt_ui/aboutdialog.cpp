#include <QPixmap>
#include <QSlider>
#include <QDialog>
#include <QPushButton>
#include <QPixmap>
#include <QVBoxLayout>
#include <QLabel>
#include <QDesktopWidget>

#include "aboutdialog.h"

#include "dxfm.h"

CAboutDialog::CAboutDialog(QWidget* pParent) : QDialog(pParent)
{
    // will be autosized on x later
    setFixedSize(500, 115);
    setWindowTitle("About " DXFM_PRODUCT_NAME_FULL);
    setModal(true);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // icon 64x64 at 11, 11
    // tools:/images/dxfm/dxfm_app.png
    QPixmap icon = QPixmap("tools:/images/dxfm/dxfm_app.png").scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QLabel* label = new QLabel(this);
    label->setPixmap(icon);
    label->setGeometry(11, 11, 64, 64);

    // button 73x21 at (center horizontally), 82
    QPushButton* button = new QPushButton("OK", this);
    button->setGeometry(0, 82, 73, 21);
    button->setDefault(true);
    connect(button, &QPushButton::clicked, this, &QDialog::close);

    // label (stretch to end with 11px padding)x64 at 89, 11
    // <b>Version: DXFM_VERSION_STRING</b>
    // <br><br>
    // Copyright by DXFM_AUTHOR. All rights reserved.
    QLabel* label2 = new QLabel(this);
    label2->setText("<br><b>Version: " DXFM_VERSION_STRING "</b><br><br>Copyright by " DXFM_AUTHOR ". All rights reserved.");
    // fit label width to content
    int label2X = 92;
    int label2Width = 500 - label2X - 11;
    label2->setGeometry(label2X, 10, label2Width, 63);
    label2->adjustSize();
    label2->setFixedHeight(64);
    
    // set new dialog width
    setFixedSize(label2->x() + label2->width() + 11, height());
    button->move((width() - button->width()) / 2, button->y());
}

#include "aboutdialog.h.moc"