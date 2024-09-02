#include "dx_ui_menubar.h"
#include "dx_vgui_controls/ScalableImagePanel.h"
#include "dx_vgui_controls/Button.h"
#include "dx_vgui_controls/Label.h"
#include "dx_vgui_controls/MenuButton.h"
#include "vgui/IInput.h"
#include "vgui/ISystem.h"
#include "tier0/memdbgon.h"

using namespace vgui;

DXUIMenuBar::DXUIMenuBar(Panel* pParent) : BaseClass(pParent, "MenuBar")
{
    m_pMBut_File = new MenuButton(this, "mbut_file", "File");
    pMenu_File = new Menu(m_pMBut_File, "");
    pMenu_File->AddMenuItem("New", "New", "newfile", this);
    pMenu_File->AddMenuItem("Open", "Open", "openfile", this);
    pMenu_File->AddMenuItem("Save", "Save", "savefile", this);
    pMenu_File->AddMenuItem("Save As", "Save As", "savefileas", this);
    pMenu_File->AddMenuItem("Close", "Close", "closefile", this);
    pMenu_File->AddSeparator();
    pMenu_File->AddMenuItem("Toggle Work Camera", "Toggle Work Camera", "toggleworkcamera", this);
    m_pMBut_File->SetMenu(pMenu_File);
    m_pMBut_Tools = new MenuButton(this, "mbut_tools", "Tools");
    pMenu_Tools = new Menu(m_pMBut_Tools, "");
    int toolCount = enginetools->GetToolCount();
    for (int i = 0; i < toolCount; i++)
    {
        const char* toolName = enginetools->GetToolName(i);
        char* toolNumber = new char[3];
        sprintf(toolNumber, "tool%d", i);
        int menuItem = pMenu_Tools->AddCheckableMenuItem(toolNumber, toolName, toolNumber, this);
        if(Q_strcmp(toolName, g_pDXFM->GetToolName()) == 0)
            pMenu_Tools->SetMenuItemChecked(menuItem, true);
    }
    m_pMBut_Tools->SetMenu(pMenu_Tools);
    AddButton(m_pMBut_File);
    AddButton(m_pMBut_Tools);
    m_pLabel = new Label(this, "label", "Director's Cut by KiwifruitDev");
}

void DXUIMenuBar::OnThink()
{
}

void DXUIMenuBar::ApplySchemeSettings(IScheme *pScheme)
{
    BaseClass::ApplySchemeSettings(pScheme);
}

void DXUIMenuBar::PerformLayout()
{
    BaseClass::PerformLayout();
    int w, h;
    engine->GetScreenSize(w, h);
    SetBounds(0, 42, w, 24);
    m_pLabel->SizeToContents();
    m_pLabel->SetPos(w - m_pLabel->GetWide() - 6, 6);
}

void DXUIMenuBar::OnCommand(char const *cmd )
{
    int toolCount = enginetools->GetToolCount();
    for (int i = 0; i < toolCount; i++)
    {
        char* toolNumber = new char[3];
        sprintf(toolNumber, "tool%d", i);
        if (!Q_stricmp(cmd, toolNumber))
        {
            enginetools->SwitchToTool(i);
            pMenu_Tools->SetMenuItemChecked(i, false);
            return;
        }
    }
	BaseClass::OnCommand( cmd );
}
