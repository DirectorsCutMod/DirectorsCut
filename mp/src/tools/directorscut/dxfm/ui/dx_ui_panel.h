#pragma once

#include "dxfm.h"
#include "dx_ui_menubar.h"
#include "tier1/utlobjectreference.h"
#include "vgui/IVGui.h"
#include "dx_vgui_controls/Panel.h"
#include "dx_vgui_controls/Frame.h"
#include "dx_vgui_controls/MenuBar.h"
#include "dx_vgui_controls/MenuButton.h"
#include "dx_vgui_controls/Label.h"
#include "dx_vgui_controls/FileOpenDialog.h"

using namespace vgui;

class DXUIPanel : public Panel
{
    DECLARE_CLASS_SIMPLE(DXUIPanel, Panel);
    DECLARE_REFERENCED_CLASS(DXUIPanel );
public:
    DXUIPanel(VPANEL pParent);
    static void DestroyEditor();
    static void SetEditorVisibility(bool bVisible);
    static void ToggleEditor();
    static bool HandleKeyChange(ButtonCode_t key, bool isDown, bool wasDown);
    static bool IsEditorVisible();
    static DXUIPanel* GetEditor();

    void PopulateEditor();
    void OpenDocumentFileDialog(bool bSave);
    void RecursiveSetChildAlpha(Panel* pPanel, int iAlpha);

    virtual void ApplySchemeSettings(IScheme *scheme);
    virtual void PaintBackground();
    virtual void Think();
    
    MESSAGE_FUNC_PARAMS(OnFileSelected, "FileSelected", pKV);
    static CUtlReference<DXUIPanel> m_refInstance;
    CUtlVector<EditablePanel*> m_vecPanels;
    bool bShowedWelcome;
protected:
    DHANDLE<FileOpenDialog> m_hFileOpenDialog;
    Frame* m_pBackground;
    DXUIMenuBar* m_pMenuBar;
};
