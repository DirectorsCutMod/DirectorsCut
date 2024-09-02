#pragma once

#include "dxfm.h"
#include "dx_vgui_controls/Frame.h"
#include "dx_vgui_controls/PropertyPage.h"
#include "dx_vgui_controls/ToolWindow.h"
#include "dx_vgui_controls/TreeView.h"
#include "dx_vgui_controls/ListPanel.h"
#include "dx_vgui_controls/Menu.h"
#include "dx_vgui_controls/MenuBar.h"

using namespace vgui;

class DXUIMenuBar : public MenuBar
{
    DECLARE_CLASS_SIMPLE(DXUIMenuBar, MenuBar);
public:
    DXUIMenuBar(Panel* pParent);
    virtual void ApplySchemeSettings(IScheme* scheme);
    virtual void OnThink();
    virtual void PerformLayout();
    virtual void OnCommand(char const *cmd);
protected:
    MenuButton* m_pMBut_File;
    Menu *pMenu_File;
    MenuButton* m_pMBut_Tools;
    Menu *pMenu_Tools;
    Label* m_pLabel;
};
