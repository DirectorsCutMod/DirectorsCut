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

CMainWindow::CMainWindow(QWidget* pParent) : QMainWindow(pParent)
{
	QIcon icon;
	icon.addFile("tools:/images/dxfm/dxfm_app.png", QSize(), QIcon::Normal, QIcon::Off);
	setWindowIcon(icon);

	menubar = new QMenuBar(this);

	menuFile = new QMenu(menubar);
	menuEdit = new QMenu(menubar);
	menuWindows = new QMenu(menubar);
	menuView = new QMenu(menubar);
	menuScripts = new QMenu(menubar);
	menuHelp = new QMenu(menubar);
	menuEngine_Window = new QMenu(menuWindows);

	centralwidget = new QWidget(this);

	tabWidget = new QTabWidget(centralwidget);
	tabWidget_2 = new QTabWidget(centralwidget);
	tabWidget_3 = new QTabWidget(centralwidget);

	animationSetEditor = new QWidget();
	elementViewer = new QWidget();
	primaryViewport = new QWidget();
	console = new QWidget();
	timeline = new QWidget();
	statusbar = new QStatusBar(this);

	actionParticle_Editor_Tool = new QAction(this);
	actionEnter_Game_Mode = new QAction(this);
    actionAuto_Hide_Engine_Window = new QAction(this);

	positionUi();
	setMetaObjects();
	actionsUi();
	retranslateUi();

}

void CMainWindow::positionUi()
{
	resize(1344, 801);

	menubar->setGeometry(QRect(0, 0, 1344, 27));

	tabWidget->setGeometry(QRect(0, 0, 323, 754));
	tabWidget_2->setGeometry(QRect(323, 0, 1021, 505));
	tabWidget_3->setGeometry(QRect(323, 505, 1021, 249));

	tabWidget->setCurrentIndex(0);
	tabWidget_3->setCurrentIndex(0);
	
	// center the window
	QRect screenGeometry = QApplication::desktop()->screenGeometry();
	int x = (screenGeometry.width() - width()) / 2;
	int y = (screenGeometry.height() - height()) / 2;
	move(x, y);
}

void CMainWindow::setMetaObjects()
{
	if (objectName().isEmpty())
		setObjectName("CMainWindow");

	menubar->setObjectName("menubar");

	menuFile->setObjectName("menuFile");
	menuEdit->setObjectName("menuEdit");
	menuWindows->setObjectName("menuWindows");
	menuView->setObjectName("menuView");
	menuScripts->setObjectName("menuScripts");
	menuHelp->setObjectName("menuHelp");
	menuEngine_Window->setObjectName("menuEngine_Window");

	centralwidget->setObjectName("centralwidget");

	tabWidget->setObjectName("tabWidget");
	tabWidget_2->setObjectName("tabWidget_2");
	tabWidget_3->setObjectName("tabWidget_3");
	
	animationSetEditor->setObjectName("animationSetEditor");
	elementViewer->setObjectName("elementViewer");
	primaryViewport->setObjectName("primaryViewport");
	console->setObjectName("console");
	timeline->setObjectName("timeline");

	statusbar->setObjectName("statusbar");
	
	actionParticle_Editor_Tool->setObjectName("actionParticle_Editor_Tool");
	actionEnter_Game_Mode->setObjectName("actionEnter_Game_Mode");
    actionAuto_Hide_Engine_Window->setObjectName("actionAuto_Hide_Engine_Window");
	
	QMetaObject::connectSlotsByName(this);
}

void CMainWindow::actionsUi()
{
	tabWidget->addTab(animationSetEditor, "");
	tabWidget->addTab(elementViewer, "");
	tabWidget_2->addTab(primaryViewport, "");
	tabWidget_2->addTab(console, "");
	tabWidget_3->addTab(timeline, "");

	menubar->addAction(menuFile->menuAction());
	menubar->addAction(menuEdit->menuAction());
	menubar->addAction(menuWindows->menuAction());
	menubar->addAction(menuView->menuAction());
	menubar->addAction(menuScripts->menuAction());
	menubar->addAction(menuHelp->menuAction());

	menuWindows->addAction(actionParticle_Editor_Tool);
	menuWindows->addAction(actionEnter_Game_Mode);
	menuWindows->addAction(menuEngine_Window->menuAction());
	menuEngine_Window->addAction(actionAuto_Hide_Engine_Window);

	connect(actionParticle_Editor_Tool, &QAction::triggered, this, [this]() {
		int toolCount = enginetools->GetToolCount();
		for (int i = 0; i < toolCount; i++)
		{
			if (!Q_stricmp("Particle Editor", enginetools->GetToolName(i)))
			{
				enginetools->SwitchToTool(i);
				return;
			}
		}
	});

	connect(actionEnter_Game_Mode, &QAction::triggered, this, [this]() {
		g_pDXFM->ToggleTool();
	});

	connect(actionAuto_Hide_Engine_Window, &QAction::triggered, this, [this]() {
		bool hide = actionAuto_Hide_Engine_Window->isChecked();
		g_pDXFM->SetShouldHideEngineWindow(hide);
		g_pDXFM->HideOrShowEngineWindow(hide);
	});
	
    actionEnter_Game_Mode->setShortcut(QCoreApplication::translate("CMainWindow", "F11", nullptr));

	actionAuto_Hide_Engine_Window->setCheckable(true);
	actionAuto_Hide_Engine_Window->setChecked(true);

	setMenuBar(menubar);
	setCentralWidget(centralwidget);
	setStatusBar(statusbar);
}

void CMainWindow::retranslateUi()
{
	setWindowTitle("Director's Cut");

	tabWidget->setTabText(tabWidget->indexOf(animationSetEditor), "Animation Set Editor");
	tabWidget->setTabText(tabWidget->indexOf(elementViewer), "Element Viewer");
	tabWidget_2->setTabText(tabWidget_2->indexOf(primaryViewport), "Primary Viewport");
	tabWidget_2->setTabText(tabWidget_2->indexOf(console), "Console");
	tabWidget_3->setTabText(tabWidget_3->indexOf(timeline), "Timeline");

	menuFile->setTitle("File");
	menuEdit->setTitle("Edit");
	menuWindows->setTitle("Windows");
	menuView->setTitle("View");
	menuScripts->setTitle("Scripts");
	menuHelp->setTitle("Help");
    menuEngine_Window->setTitle("Engine Window");

	actionParticle_Editor_Tool->setText("Particle Editor Tool");
	actionEnter_Game_Mode->setText("Enter Game Mode");
    actionAuto_Hide_Engine_Window->setText("Auto Hide Engine Window");
}

#include "ui.h.moc"