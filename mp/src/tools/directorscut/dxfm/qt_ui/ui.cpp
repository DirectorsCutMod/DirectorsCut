#include <QPixmap>
#include <QSlider>
#include <QDialog>
#include <QPushButton>
#include <QPixmap>
#include <QVBoxLayout>
#include <QLabel>

#include <materialsystem/imesh.h>
#include <materialsystem/itexture.h>
#include <tier2/camerautils.h>
#include <istudiorender.h>
#include <KeyValues.h>

#include "ui.h"

// Main Window
// Embeds two matsyswindows into the same window, using container widgers

CMainWindow::CMainWindow(QWidget* pParent) : QWidget(pParent)
{
	this->setWindowTitle(tr("the fun zone"));
	auto pViewerLayout = new QVBoxLayout(this);

	m_picker = new QComboBox();
	pViewerLayout->addWidget(m_picker);

	QPushButton* funny = new QPushButton();
	funny->setText("funny");
	pViewerLayout->addWidget(funny);
		
	auto label = new QLabel(this);
	label->setText("look at how much fun we're having!");
	pViewerLayout->addWidget(label);

	this->setLayout(pViewerLayout);
	
	// set size
	this->resize(400, 250);
}

void CMainWindow::init()
{
	// Populate the picker
	m_picker->clear();
	m_picker->addItem("bouncy castle");
	m_picker->addItem("clown car");
}

#include "ui.h.moc"