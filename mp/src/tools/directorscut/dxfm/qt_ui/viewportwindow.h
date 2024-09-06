#pragma once

#include "matsyswindow.h"
#include "dx_viewport.h"

class CViewportWindow : public CMatSysWindow
{
	Q_OBJECT;
public:

	CViewportWindow(QWindow* pParent, int index = 0);
	~CViewportWindow();

	virtual void paint();
	virtual bool event(QEvent* ev);

    void SetViewport(int index);
protected:
    bool m_bViewportIsDirty = true;

    // Viewport pointer
    int m_iIndex = 0;
    DXViewport* m_pViewport = NULL;

    // Work camera
    bool m_bWorkCameraActive =  true;
    Vector m_vecWorkCameraOrigin = Vector(0, 0, 0);
    QAngle m_angWorkCameraAngles = QAngle(0, 0, 0);
    float m_flWorkCameraFOV = 90.0f;
};
