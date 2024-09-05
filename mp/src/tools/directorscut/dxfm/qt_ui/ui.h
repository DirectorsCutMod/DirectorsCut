#pragma once

#include <QMainWindow>
#include <QWindow>
#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QComboBox>

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

#include "matsyswindow.h"

class CMainWindow : public QMainWindow
{
	Q_OBJECT;
public:

	CMainWindow(QWidget* pParent);

	void positionUi();
    void actionsUi();
	void setMetaObjects();
	void retranslateUi();

    QWidget *centralwidget;
	
    QTabWidget *tabWidget;
    QTabWidget *tabWidget_2;
    QTabWidget *tabWidget_3;

    QWidget *animationSetEditor;
    QWidget *elementViewer;
    QWidget *primaryViewport;
    QWidget *console;
    QWidget *timeline;

    QMenuBar *menubar;

    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuWindows;
    QMenu *menuView;
    QMenu *menuScripts;
    QMenu *menuHelp;
    QMenu *menuEngine_Window;

    QStatusBar *statusbar;
	
    QAction *actionParticle_Editor_Tool;
    QAction *actionEnter_Game_Mode;
    QAction *actionAuto_Hide_Engine_Window;
};
