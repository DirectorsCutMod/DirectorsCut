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

	primaryViewport = new CViewportWindow(0);
	container = QWidget::createWindowContainer(primaryViewport, this);

	console = new QWidget();
	timeline = new QWidget();

	statusbar = new QStatusBar(this);
	
	actionQuit = new QAction(this);
	actionParticle_Editor_Tool = new QAction(this);
	actionEnter_Game_Mode = new QAction(this);
    actionAuto_Hide_Engine_Window = new QAction(this);
	actionAbout_Directors_Cut = new QAction(this);
	actionAbout_Qt = new QAction(this);

	positionUi();
	setMetaObjects();
	actionsUi();
	retranslateUi();

}

void CMainWindow::redraw()
{
	// Draw frames
	primaryViewport->redraw();
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
	// FIXME: hardcoded values from Windows 11
	int taskbarHeight = 48;
	int borderWidth = 1;
	int borderHeight = 31;
	int desktopWidth = screenGeometry.width();
	int desktopHeight = screenGeometry.height() - taskbarHeight;
	int x = (desktopWidth - width()) / 2;
	int y = (desktopHeight - height()) / 2;
	move(x - borderWidth, y - borderHeight);
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
	container->setObjectName("container");

	console->setObjectName("console");
	timeline->setObjectName("timeline");

	statusbar->setObjectName("statusbar");
	
	actionQuit->setObjectName("actionQuit");
	actionParticle_Editor_Tool->setObjectName("actionParticle_Editor_Tool");
	actionEnter_Game_Mode->setObjectName("actionEnter_Game_Mode");
    actionAuto_Hide_Engine_Window->setObjectName("actionAuto_Hide_Engine_Window");
	actionAbout_Directors_Cut->setObjectName("actionAbout_Directors_Cut");
	actionAbout_Qt->setObjectName("actionAbout_Qt");
	
	QMetaObject::connectSlotsByName(this);
}

void CMainWindow::actionsUi()
{
	tabWidget->addTab(animationSetEditor, "");
	tabWidget->addTab(elementViewer, "");

	container->setMinimumSize(256, 256);
	container->setFocusPolicy(Qt::TabFocus);
	tabWidget_2->addTab(container, "");

	tabWidget_2->addTab(console, "");
	tabWidget_3->addTab(timeline, "");

	menubar->addAction(menuFile->menuAction());
	menubar->addAction(menuEdit->menuAction());
	menubar->addAction(menuWindows->menuAction());
	menubar->addAction(menuView->menuAction());
	menubar->addAction(menuScripts->menuAction());
	menubar->addAction(menuHelp->menuAction());

    menuFile->addAction(actionQuit);
	menuWindows->addAction(actionParticle_Editor_Tool);
	menuWindows->addAction(actionEnter_Game_Mode);
	menuWindows->addAction(menuEngine_Window->menuAction());
	menuEngine_Window->addAction(actionAuto_Hide_Engine_Window);
	menuHelp->addAction(actionAbout_Directors_Cut);
	menuHelp->addAction(actionAbout_Qt);

	connect(actionQuit, &QAction::triggered, this, [this]() {
		// TODO: ask user to save document
		engine->ClientCmd_Unrestricted("quit prompt");
		g_pDXFM->SetToolActive(false);
	});

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

	connect(actionAbout_Directors_Cut, &QAction::triggered, this, [this]() {
		QDialog* dialog = new QDialog(this);
		// will be autosized on x later
		dialog->setFixedSize(500, 115);
		dialog->setWindowTitle("About " DXFM_PRODUCT_NAME_FULL);
		// icon 64x64 at 11, 11
		// tools:/images/dxfm/dxfm_app.png
		QPixmap icon = QPixmap("tools:/images/dxfm/dxfm_app.png").scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		QLabel* label = new QLabel(dialog);
		label->setPixmap(icon);
		label->setGeometry(11, 11, 64, 64);
		// button 73x21 at (center horizontally), 82
		QPushButton* button = new QPushButton("OK", dialog);
		button->setGeometry(0, 82, 73, 21);
		button->setDefault(true);
		connect(button, &QPushButton::clicked, dialog, &QDialog::close);
		// label (stretch to end with 11px padding)x64 at 89, 11
		// <b>Version: DXFM_VERSION_STRING</b>
		// <br><br>
		// Copyright by DXFM_AUTHOR. All rights reserved.
		QLabel* label2 = new QLabel(dialog);
		label2->setText("<br><b>Version: " DXFM_VERSION_STRING "</b><br><br>Copyright by " DXFM_AUTHOR ". All rights reserved.");
		// fit label width to content
		int label2X = 92;
		int label2Width = 500 - label2X - 11;
		label2->setGeometry(label2X, 10, label2Width, 63);
		label2->adjustSize();
		label2->setFixedHeight(64);
		// set new dialog width
		dialog->setFixedSize(label2->x() + label2->width() + 11, dialog->height());
		button->move((dialog->width() - button->width()) / 2, button->y());
		// don't allow user to interact with main window
		dialog->setModal(true);
		// show dialog
		dialog->show();
		// focus
		dialog->activateWindow();
	});

	connect(actionAbout_Qt, &QAction::triggered, this, [this]() {
		QApplication::aboutQt();
	});
	
    actionEnter_Game_Mode->setShortcut(QCoreApplication::translate("CMainWindow", "F11", nullptr));

	actionAuto_Hide_Engine_Window->setCheckable(true);
	actionAuto_Hide_Engine_Window->setChecked(true);

	setMenuBar(menubar);
	setCentralWidget(centralwidget);
	setStatusBar(statusbar);
}

void CMainWindow::closeEvent(QCloseEvent *event)
{
	// concommand "quit prompt"
	engine->ClientCmd_Unrestricted("quit prompt");
	g_pDXFM->SetToolActive(false);
	// don't close the window
	event->ignore();
}

void CMainWindow::retranslateUi()
{
	setWindowTitle(DXFM_PRODUCT_NAME_FULL);

	tabWidget->setTabText(tabWidget->indexOf(animationSetEditor), "Animation Set Editor");
	tabWidget->setTabText(tabWidget->indexOf(elementViewer), "Element Viewer");
	tabWidget_2->setTabText(tabWidget_2->indexOf(container), "Primary Viewport");
	tabWidget_2->setTabText(tabWidget_2->indexOf(console), "Console");
	tabWidget_3->setTabText(tabWidget_3->indexOf(timeline), "Timeline");

	menuFile->setTitle("File");
	menuEdit->setTitle("Edit");
	menuWindows->setTitle("Windows");
	menuView->setTitle("View");
	menuScripts->setTitle("Scripts");
	menuHelp->setTitle("Help");
    menuEngine_Window->setTitle("Engine Window");

    actionQuit->setText("Quit");
	actionParticle_Editor_Tool->setText("Particle Editor Tool");
	actionEnter_Game_Mode->setText("Enter Game Mode");
    actionAuto_Hide_Engine_Window->setText("Auto Hide Engine Window");
	actionAbout_Directors_Cut->setText("About " DXFM_PRODUCT_NAME_FULL);
	actionAbout_Qt->setText("About Qt");
}

#include "ui.h.moc"