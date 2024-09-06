#pragma once

#include <QWidget>
#include <QWindow>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QComboBox>

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

class CMatSysWindow : public QWindow
{
	Q_OBJECT;
public:

	CMatSysWindow(QWindow* pParent = nullptr);

	// Sets everything up for painting and then paints
	virtual void redraw();

	// Paints to the window
	virtual void paint();

	// Dumps the window contents to a QImage
	QImage screenshot();

protected:
	virtual void resizeEvent(QResizeEvent* ev);
};
