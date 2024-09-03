#pragma once
#include <QWindow>
#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QComboBox>

#include "matsyswindow.h"

class CMainWindow : public QWidget
{
	Q_OBJECT;
public:

	CMainWindow(QWidget* pParent);

	void init();

	QComboBox* m_picker;
};
