#include <QPixmap>
#include <QSlider>
#include <QDialog>
#include <QPushButton>
#include <QPixmap>
#include <QVBoxLayout>
#include <QLabel>
#include <QDesktopWidget>

#include <materialsystem/imesh.h>
#include <materialsystem/itexture.h>
#include <tier2/camerautils.h>
#include <istudiorender.h>
#include <KeyValues.h>

#include "ui.h"

#include "dxfm.h"

// Main Window

CViewportWindow::CViewportWindow(QWidget* pParent) : QWidget(pParent)
{
	setWindowTitle("Primary Viewport");
}

#include "viewportwindow.h.moc"