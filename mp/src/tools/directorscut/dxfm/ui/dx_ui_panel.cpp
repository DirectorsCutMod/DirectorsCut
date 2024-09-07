#include "dx_ui_panel.h"
//#include "dx_ui_viewport.h"
//#include "dx_ui_welcome.h"
#include "tier1/KeyValues.h"
#include "ienginevgui.h"
#include "collisionutils.h"
#include "vgui/IVGui.h"
#include "vgui/IInput.h"
#include "vgui/ISurface.h"
#include "dx_vgui_controls/Panel.h"
#include "dx_vgui_controls/Frame.h"
#include "dx_vgui_controls/ToolWindow.h"
#include "dx_vgui_controls/PropertySheet.h"
#include "tier0/memdbgon.h"

using namespace vgui;

CUtlReference<DXUIPanel> DXUIPanel::m_refInstance = CUtlReference<DXUIPanel>();

void DXUIPanel::DestroyEditor()
{
    DXUIPanel* pPanel = DXUIPanel::m_refInstance.m_pObject;
    if ( pPanel )
        pPanel->DeletePanel();
}

void DXUIPanel::SetEditorVisibility(bool bVisible)
{
    DXUIPanel* pPanel = DXUIPanel::m_refInstance.m_pObject;
    if (pPanel == NULL && bVisible)
    {
		// Create the editor panel if it doesn't exist and needs to be visible
        VPANEL editorParent = enginevgui->GetPanel(PANEL_TOOLS);
        pPanel = new DXUIPanel(editorParent);
        DXUIPanel::m_refInstance.Set(pPanel);
        Msg("Created editor panel\n");
    }
	// If the panel isn't created but doesn't need to be visible, don't do anything
    if (pPanel != NULL)
        pPanel->SetVisible(bVisible);
	// Report an error if the panel couldn't be created and needs to be visible
	if(pPanel == NULL && bVisible)
	{
		Msg("Failed to create editor panel\n");
#ifdef _DEBUG
		Assert( pPanel != NULL );
#endif
	}
}

void DXUIPanel::ToggleEditor()
{
	// Toggle the visibility of the editor using these two helper functions
	SetEditorVisibility(!IsEditorVisible());
}

bool DXUIPanel::HandleKeyChange(ButtonCode_t key, bool isDown, bool wasDown)
{
	// Message all panels in the editor to trap the key
	DXUIPanel* pPanel = DXUIPanel::m_refInstance.m_pObject;
	if (pPanel)
	{
		for (int i = 0; i < pPanel->m_vecPanels.Count(); i++)
		{
			Panel* pPage = pPanel->m_vecPanels[i];
			if (pPage)
			{
				if (pPage->IsVisible())
				{
					KeyValues* data = new KeyValues("HandleKeyChange");
					data->SetInt("key", key);
					data->SetBool("isDown", isDown);
					data->SetBool("wasDown", wasDown);
					bool bHandled = pPage->RequestInfo(data);
					data->deleteThis();
					if (bHandled)
						return true;
				}
			}
		}
	}
	// pass through to global key handler
	return false;
}

bool DXUIPanel::IsEditorVisible()
{
	// Needs to be created and visible, otherwise it's not visible
    DXUIPanel *pPanel = DXUIPanel::m_refInstance.m_pObject;
    return pPanel && pPanel->IsVisible();
}


DXUIPanel* DXUIPanel::GetEditor()
{
	return DXUIPanel::m_refInstance.m_pObject;
}

void DXUIPanel::PopulateEditor()
{
	// Check each page to see if they're parented to a ToolWindow
	// If they aren't, create a new ToolWindow and add them to it
	CUtlVector< EditablePanel* > pagesToPopulate;

	// If page or its parent is NULL, add it to the list of pages to populate
	for ( int i = 0; i < m_vecPanels.Count(); i++ )
	{
		EditablePanel* pPage = m_vecPanels[i];
		if ( pPage == NULL || pPage->GetParent() == NULL )
		{
			pagesToPopulate.AddToTail( pPage );
		}
		else if ( pPage != NULL && pPage->GetParent() != NULL )
		{
			// Name of a ToolWindow parent would be "ToolWindowSheet"
			if ( Q_strcmp( pPage->GetParent()->GetName(), "ToolWindowSheet" ) != 0 )
			{
				// Log to console what the parent is
				Msg( "Page %s is parented to %s\n", pPage->GetName(), pPage->GetParent()->GetName() );
				pagesToPopulate.AddToTail( pPage );
			}
		}
	}

	CUtlVector< ToolWindow* > toolWindows;

	if (pagesToPopulate.Count() != 0)
	{
		// TODO: Welcome window isn't guaranteed to be the last page
		for (int i = 0; i < pagesToPopulate.Count(); i++)
		{
			// We can assume the tool window is kept track of elsewhere
			// It doesn't need to be stored as a member variable
			ToolWindow* m_pToolWindow = new ToolWindow(this, true, 0, NULL, "ToolWindow", true, true);
			m_pToolWindow->SetScheme("DXScheme");
			m_pToolWindow->Activate();
			m_pToolWindow->SetVisible(true);
			m_pToolWindow->SetAlpha(255);
			EditablePanel* pPage = pagesToPopulate[i];
			// Ask if the page has a context menu
			bool bContextMenu = false;
			KeyValues* data = new KeyValues("PageHasContextMenu");
			bContextMenu = pPage->RequestInfo(data);
			data->deleteThis();
			// Add the page to the tool window
			m_pToolWindow->AddPage(pPage, pPage->GetName(), bContextMenu);
			m_pToolWindow->Activate();
			toolWindows.AddToTail(m_pToolWindow);
		}
		// Set sizes of tool windows
		/*
		int padding = 4; // Padding between tool windows
		int w, h;
		GetSize(w, h);
		// Tab layouts
		for (int i = 0; i < toolWindows.Count(); i++)
		{
			ToolWindow* pToolWindow = toolWindows[i];
			Panel* page = pToolWindow->GetActivePage();
			if (page == m_vecPanels[0] || page == m_vecPanels[1]) // Animation set editor + element viewer
			{
				pToolWindow->SetBounds(0, 24, w / 3, (h / 2) + (h / 8) - 24);
			}
			else if(page == m_vecPanels[3] || page == m_vecPanels[4]) // welcome + viewport
			{
				pToolWindow->SetBounds((w / 3) - padding, 24, w - (w / 3) + padding, (h / 2) + (h / 8) - 24);
			}
			else if(page == m_vecPanels[4] || page == m_vecPanels[5]) // timeline + asset browser
			{
				pToolWindow->SetBounds((w / 3) - padding, (h / 2) + (h / 8) - (24 / 2) + (padding*2), w - (w / 3) + padding, (h / 2) - (h / 8) + padding);
			}
			else if(page == m_vecPanels[6]) // properties
			{
				pToolWindow->SetBounds(0, (h / 2) + (h / 8) - (24/2) + (padding * 2), w / 3, (h / 2) - (h / 8) + padding);
			}
			// Apply padding to all sides
			int x, y, wide, tall;
			pToolWindow->GetBounds(x, y, wide, tall);
			pToolWindow->SetBounds(x + padding, y + padding, wide - (padding * 2), tall - (padding * 2));
		}
		*/
		// Tab groups
		for (int i = 0; i < toolWindows.Count(); i++)
		{
			ToolWindow* pToolWindow = toolWindows[i];
			Assert(pToolWindow != NULL);
			if (i == 0)
				continue;
			// Combine with previous tool window if their sizes and positions are the same
			ToolWindow* pPrevToolWindow = toolWindows[i - 1];
			Assert(pPrevToolWindow != NULL);
			int x, y, wide, tall;
			pToolWindow->GetBounds(x, y, wide, tall);
			int prevX, prevY, prevWide, prevTall;
			pPrevToolWindow->GetBounds(prevX, prevY, prevWide, prevTall);
			if (x == prevX && y == prevY && wide == prevWide && tall == prevTall)
			{
				// Add all pages from the previous tool window to the current one
				PropertySheet* sheet = pPrevToolWindow->GetPropertySheet();
				for (int j = 0; j < sheet->GetNumPages(); j++)
				{
					Panel* page = sheet->GetPage(j);
					sheet->RemovePage(page);
					pToolWindow->AddPage(page, page->GetName(), false);
				}
				pPrevToolWindow->MarkForDeletion();
			}
		}
	}
}

void DXUIPanel::Think()
{
	int w, h;
	engine->GetScreenSize(w, h);
	SetBounds(0, 0, w, h);

	// TODO: this shouldn't be here
	m_pBackground->SetBounds(0, -42, w, 16);
	m_pMenuBar->SetBounds(0, 42, w, 24);

	// FIXME: Please make this not required, what on earth is setting the alpha to 0?
	RecursiveSetChildAlpha(this, 255);
}

DXUIPanel::DXUIPanel(VPANEL pParent) : BaseClass(NULL, "DXFM", false)
{
	SetParent(pParent);

	// Set the scheme
	vgui::HScheme scheme = vgui::scheme()->LoadSchemeFromFile("resource/dxscheme.res", "DXScheme");
	SetScheme(scheme);

	// Create window tabs
	//m_vecPanels.AddToTail(new DXUIWelcome(this));
    //m_vecPanels.AddToTail(new DXUIViewport(this));

	// Set properties
	int w, h;
	engine->GetScreenSize(w, h);
	SetBounds(0, 0, w, h);
	SetPaintBackgroundEnabled(true);
	SetPaintBorderEnabled(false);
	SetPaintEnabled(true);
	SetMouseInputEnabled(true);
	SetKeyBoardInputEnabled(false);
	RequestFocus();

	// Create menu bar
	m_pBackground = new Frame(this, "MenuBarBackground", false);
	m_pBackground->SetPaintBackgroundEnabled(true);
	m_pBackground->SetPaintBorderEnabled(false);
	m_pBackground->SetPaintEnabled(true);
	m_pBackground->SetDragEnabled(false);
	m_pBackground->SetCloseButtonVisible(false);
	m_pBackground->SetSizeable(false);
	m_pBackground->SetMoveable(false);
	m_pBackground->SetTitleBarVisible(false);
	m_pBackground->SetMouseInputEnabled(true);
	m_pBackground->SetKeyBoardInputEnabled(true);
	m_pBackground->SetBounds(0, -42, w, 16);
	m_pBackground->Activate();
	m_pBackground->SetVisible(true);
	m_pMenuBar = new DXUIMenuBar(m_pBackground);
}

void DXUIPanel::OpenDocumentFileDialog(bool bSave)
{
    if (m_hFileOpenDialog.Get())
        m_hFileOpenDialog.Get()->MarkForDeletion();
    m_hFileOpenDialog = new FileOpenDialog(this,
        bSave ? "Save session" : "Load session",
        bSave ? FOD_SAVE : FOD_OPEN,
        new KeyValues("FileOpenContext", "context",
        bSave ? "savec" : "openc"));
    m_hFileOpenDialog->AddActionSignalTarget(this);
    if (m_hFileOpenDialog.Get())
    {
        m_hFileOpenDialog->AddFilter("*.vdf", "KeyValues (*.vdf)", true);
        m_hFileOpenDialog->DoModal(true);
    }
}

void DXUIPanel::RecursiveSetChildAlpha(Panel* pPanel, int iAlpha)
{
	if (!pPanel)
		return;
	pPanel->SetAlpha(iAlpha);
	for (int i = 0; i < pPanel->GetChildCount(); i++)
	{
		Panel* pChild = pPanel->GetChild(i);
		if (pChild)
			RecursiveSetChildAlpha(pChild, iAlpha);
	}
}

void DXUIPanel::OnFileSelected(KeyValues* pKV)
{
    KeyValues* pContext = pKV->FindKey("FileOpenContext");
    if (!pContext)
        return;
    const char* __c = pContext->GetString("context");
    bool bSaving = true;
    if (!Q_stricmp(__c, "openc"))
        bSaving = false;
    const char* pathIn = pKV->GetString("fullpath");
    if (Q_strlen(pathIn) <= 1)
        return;
}

void DXUIPanel::ApplySchemeSettings(IScheme *scheme)
{
    BaseClass::ApplySchemeSettings(scheme);
    for (int i = 0; i < m_vecPanels.Count(); i++)
    {
        EditablePanel* pPage = m_vecPanels[i];
        if (pPage)
        {
            pPage->SetBgColor(GetSchemeColor("DXUIPanelPage.BgColor", scheme));
            pPage->SetFgColor(GetSchemeColor("DXUIPanelPage.FgColor", scheme));
            pPage->SetPaintBackgroundType(2);
        }
    }
}

void DXUIPanel::PaintBackground()
{
	// Draw a grid background
    surface()->DrawSetColor(31, 31, 31, 240);
    surface()->DrawFilledRect(0, 0, GetWide(), GetTall());
    int w, h;
    GetSize(w, h);
    surface()->DrawSetColor(16, 16, 16, 64);
    for (int i = 0; i < w; i += 10)
    {
        surface()->DrawLine(i, 0, i, h);
    }
    for (int i = 0; i < h; i += 10)
    {
        surface()->DrawLine(0, i, w, i);
    }
}
