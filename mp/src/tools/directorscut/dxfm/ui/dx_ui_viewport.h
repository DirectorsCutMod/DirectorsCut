#pragma once

#include <dx_vgui_controls/EditablePanel.h>

using namespace vgui;

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

class DXUIViewport : public EditablePanel
{
    DECLARE_CLASS_SIMPLE(DXUIViewport, EditablePanel);

public:
    DXUIViewport(Panel* pParent, int index = 0);

    ~DXUIViewport();
    virtual void Paint();
    virtual void OnThink();

    virtual void OnMousePressed(MouseCode code);
    virtual void OnMouseReleased(MouseCode code);
    virtual void OnCursorMoved(int x, int y);
    virtual void OnMouseWheeled(int delta);
    virtual bool RequestInfo(KeyValues* data);
    virtual void OnCommand(const char *pcCommand);

    void SetViewport(int index);

    bool CreateContextMenu();
    void OpenContextMenu();
    
    bool HandleKeyChange(ButtonCode_t key, bool isDown, bool wasDown);

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
    MESSAGE_FUNC_PARAMS(OnOpenContextMenu, "OpenContextMenu", data);
    
    HFont m_hFont;
    Menu* m_pContextMenu;
    bool m_bViewportIsDirty = true;

    // Viewport pointer
    int m_iIndex = 0;
    DXViewport* m_pViewport = NULL;

    // Work camera
    bool m_bWorkCameraActive =  true;
    Vector m_vecWorkCameraOrigin = Vector(0, 0, 0);
    QAngle m_angWorkCameraAngles = QAngle(0, 0, 0);
    float m_flWorkCameraFOV = 90.0f;

    // Camera movement
    float m_flCameraMovementSpeed = 100.0f;

    // Overlay text
    CUtlVector<OverlayText*> m_vecOverlayText;
    int m_iWorkCameraOverlayText = -1;
    int m_iSceneCameraOverlayText = -1;
    int m_iNoSessionOverlayText = -1;
    int m_iNoMapOverlayText = -1;

    // Keyboard and mouse input, mimics SFM camera movement
    // https://developer.valvesoftware.com/wiki/SFM/Navigating_with_the_camera
    bool m_bMouseInRange = false; // if mouse is in range of viewport
    bool m_bMouseCaptured = false; // if mouse is swallowed, used to enable movement keys, depends on source 1/2 style
    bool m_bDebounce = false;

    // Define bindings
    ButtonCode_t m_iMouseButtonPrimary      = MOUSE_LEFT;   // nonstatic, changes if source 2 style is used
    ButtonCode_t m_iMouseButtonSecondary    = MOUSE_RIGHT;  // nonstatic, changes if source 2 style is used
    ButtonCode_t m_iMouseButtonMiddleButton = MOUSE_MIDDLE;
    ButtonCode_t m_iMouseButtonX1Button     = MOUSE_4;
    ButtonCode_t m_iMouseButtonX2Button     = MOUSE_5;
    ButtonCode_t m_iKeySpeed                = KEY_LSHIFT;
    ButtonCode_t m_iKeySlow                 = KEY_LCONTROL;
    ButtonCode_t m_iKeyRotate               = KEY_R;
    ButtonCode_t m_iKeyOrbit                = KEY_LALT;
    ButtonCode_t m_iKeyForward              = KEY_W;
    ButtonCode_t m_iKeyBackward             = KEY_S;
    ButtonCode_t m_iKeyLeft                 = KEY_A;
    ButtonCode_t m_iKeyRight                = KEY_D;
    ButtonCode_t m_iKeyUp                   = KEY_Z;
    ButtonCode_t m_iKeyDown                 = KEY_X;

    // Button states
    bool m_bMouseButtonHeldPrimary      = false; // source 1 style: left, source 2 style: right
    bool m_bMouseButtonHeldSecondary    = false; // source 1 style: right, source 2 style: left
    bool m_bMouseButtonHeldMiddle       = false; // used for panning when alt is held
    bool m_bMouseButtonHeldX1           = false; // unused, refers to mouse button 4
    bool m_bMouseButtonHeldX2           = false; // unused, refers to mouse button 5
    bool m_bKeyHeldSpeed                = false; // SHIFT (held), speeds up movement if m_bMouseCaptured
    bool m_bKeyHeldSlow                 = false; // ctrl (held), slows down movement if m_bMouseCaptured
    bool m_bKeyHeldRotate               = false; // R (held), rotate camera with mouse movement if m_bMouseCaptured
    bool m_bKeyHeldOrbit                = false; // ALT (held), orbit camera with mouse movement if m_bMouseCaptured
    bool m_bKeyHeldForward              = false; // W, move forward if m_bMouseCaptured
    bool m_bKeyHeldBackward             = false; // S, move backward if m_bMouseCaptured
    bool m_bKeyHeldLeft                 = false; // A, move left if m_bMouseCaptured
    bool m_bKeyHeldRight                = false; // D, move right if m_bMouseCaptured
    bool m_bKeyHeldUp                   = false; // Z, move up if m_bMouseCaptured
    bool m_bKeyHeldDown                 = false; // X, move down if m_bMouseCaptured

    // Quick zoom
    float m_flQuickZoomLerpSpeed = 0.5f; // how fast the zoom lerp is
    float m_flQuickZoomLerp = 0.0f; // current lerp value
    float m_flQuickZoomTarget = 10.0f; // target zoom value
};
