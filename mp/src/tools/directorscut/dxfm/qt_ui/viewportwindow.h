#pragma once

#include "matsyswindow.h"
#include "dx_viewport.h"

#include "Color.h"

enum OverlayAnchor
{
    OVERLAY_ANCHOR_TOP_LEFT = 0,
    OVERLAY_ANCHOR_TOP_CENTER,
    OVERLAY_ANCHOR_TOP_RIGHT,
    OVERLAY_ANCHOR_CENTER_LEFT,
    OVERLAY_ANCHOR_CENTER,
    OVERLAY_ANCHOR_CENTER_RIGHT,
    OVERLAY_ANCHOR_BOTTOM_LEFT,
    OVERLAY_ANCHOR_BOTTOM_CENTER,
    OVERLAY_ANCHOR_BOTTOM_RIGHT
};

class OverlayText
{
public:
    OverlayText(const wchar_t* text, OverlayAnchor anchor = OVERLAY_ANCHOR_TOP_LEFT, Color textColor = Color(255, 255, 255, 255), Vector2D textOffset = Vector2D(0, 0));
    OverlayText(const wchar_t* text, OverlayAnchor anchor = OVERLAY_ANCHOR_TOP_LEFT, Color textColor = Color(255, 255, 255, 255), int textOffsetX = 0, int textOffsetY = 0);

    const wchar_t* GetText();
    OverlayAnchor GetAnchor();
    Color GetTextColor();
    Vector2D GetTextOffset();
    int GetTextOffsetX();
    int GetTextOffsetY();

    void SetText(const wchar_t* text);
    void SetAnchor(OverlayAnchor anchor);
    void SetTextColor(Color textColor);
    void SetTextOffset(Vector2D textOffset);
    void SetTextOffsetX(int textOffsetX);
    void SetTextOffsetY(int textOffsetY);

private:
    const wchar_t* m_text;
    OverlayAnchor m_anchor;
    Color m_textColor;
    Vector2D m_textOffset;
};

class CViewportWindow : public CMatSysWindow
{
	Q_OBJECT;
public:
	CViewportWindow(QWindow* pParent, int index = 0);
	~CViewportWindow();
	
	virtual void paint();

    // qt overrides
	virtual bool event(QEvent* ev);
    virtual void mousePressEvent(QMouseEvent* ev);
	virtual void mouseReleaseEvent(QMouseEvent* ev);
	virtual void mouseMoveEvent(QMouseEvent* ev);
	virtual void wheelEvent(QWheelEvent* ev);
	virtual void keyPressEvent(QKeyEvent* ev);
	virtual void keyReleaseEvent(QKeyEvent* ev);

    void SetViewport(int index);

    OverlayText* GetOverlayText(int slot = 0);
    void SetOverlayText(OverlayText* overlayText, int slot = 0);
    void SetOverlayText(const wchar_t* text = L"", int slot = 0, OverlayAnchor anchor = OVERLAY_ANCHOR_TOP_LEFT, Color textColor = Color(255, 255, 255, 255), Vector2D textOffset = Vector2D(0, 0));
    void SetOverlayText(const wchar_t* text = L"", int slot = 0, OverlayAnchor anchor = OVERLAY_ANCHOR_TOP_LEFT, Color textColor = Color(255, 255, 255, 255), int textOffsetX = 0, int textOffsetY = 0);
    int AddOverlayText(OverlayText* overlayText);
    int AddOverlayText(const wchar_t* text = L"", OverlayAnchor anchor = OVERLAY_ANCHOR_TOP_LEFT, Color textColor = Color(255, 255, 255, 255), Vector2D textOffset = Vector2D(0, 0));
    int AddOverlayText(const wchar_t* text = L"", OverlayAnchor anchor = OVERLAY_ANCHOR_TOP_LEFT, Color textColor = Color(255, 255, 255, 255), int textOffsetX = 0, int textOffsetY = 0);
    void RemoveOverlayText(int slot);
    void ClearOverlayText();
    int GetOverlayTextCount();
protected:

    // Overlay text
    HFont m_hFont;
    CUtlVector<OverlayText*> m_vecOverlayText;
    int m_iWorkCameraOverlayText = -1;
    int m_iSceneCameraOverlayText = -1;
    int m_iNoSessionOverlayText = -1;
    int m_iNoMapOverlayText = -1;

    // Viewport pointer
    bool m_bViewportIsDirty = true;
    int m_iIndex = 0;
    DXViewport* m_pViewport = NULL;

	// Camera movement
    bool m_bMouseCaptured = false;
    float m_flCameraMovementSpeed = 100.0f;

    // Work camera
    bool m_bWorkCameraActive =  true;
    Vector m_vecWorkCameraOrigin = Vector(0, 0, 0);
    QAngle m_angWorkCameraAngles = QAngle(0, 0, 0);
    float m_flWorkCameraFOV = 80.0f;

    // Define bindings
    Qt::MouseButton m_iMouseButtonPrimary			= Qt::LeftButton;	// nonstatic, changes if source 2 style is used
	Qt::MouseButton m_iMouseButtonSecondary			= Qt::RightButton;	// nonstatic, changes if source 2 style is used
	Qt::MouseButton m_iMouseButtonMiddleButton		= Qt::MiddleButton;
	Qt::MouseButton m_iMouseButtonX1Button			= Qt::XButton1;
	Qt::MouseButton m_iMouseButtonX2Button			= Qt::XButton2;
	Qt::Key m_iKeySprint							= Qt::Key_Shift;
	Qt::Key m_iKeyWalk								= Qt::Key_Control;
	Qt::Key m_iKeyRotate							= Qt::Key_R;
	Qt::Key m_iKeyOrbit								= Qt::Key_Alt;
	Qt::Key m_iKeyForward							= Qt::Key_W;
	Qt::Key m_iKeyBackward							= Qt::Key_S;
	Qt::Key m_iKeyLeft								= Qt::Key_A;
	Qt::Key m_iKeyRight								= Qt::Key_D;
	Qt::Key m_iKeyUp								= Qt::Key_Z;
	Qt::Key m_iKeyDown								= Qt::Key_X;

    // Button states
    bool m_bMouseButtonHeldPrimary      = false; // source 1 style: left, source 2 style: right
    bool m_bMouseButtonHeldSecondary    = false; // source 1 style: right, source 2 style: left
    bool m_bMouseButtonHeldMiddle       = false; // used for panning when alt is held
    bool m_bMouseButtonHeldX1           = false; // unused, refers to mouse button 4
    bool m_bMouseButtonHeldX2           = false; // unused, refers to mouse button 5
    bool m_bKeyHeldSprint               = false; // SHIFT (held), speeds up movement if m_bMouseCaptured
    bool m_bKeyHeldWalk                 = false; // ctrl (held), slows down movement if m_bMouseCaptured
    bool m_bKeyHeldRotate               = false; // R (held), rotate camera with mouse movement if m_bMouseCaptured
    bool m_bKeyHeldOrbit                = false; // ALT (held), orbit camera with mouse movement if m_bMouseCaptured
    bool m_bKeyHeldForward              = false; // W, move forward if m_bMouseCaptured
    bool m_bKeyHeldBackward             = false; // S, move backward if m_bMouseCaptured
    bool m_bKeyHeldLeft                 = false; // A, move left if m_bMouseCaptured
    bool m_bKeyHeldRight                = false; // D, move right if m_bMouseCaptured
    bool m_bKeyHeldUp                   = false; // Z, move up if m_bMouseCaptured
    bool m_bKeyHeldDown                 = false; // X, move down if m_bMouseCaptured
};
