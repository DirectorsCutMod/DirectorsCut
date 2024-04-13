//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window for Director's Cut
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include <KeyValues.h>

#include "../directorscut.h"
#include "dxeditorpanel.h"

#include "ienginevgui.h"
#include "collisionutils.h"
#include <vgui/IVGui.h>
#include <vgui/IInput.h>
#include <vgui/ISurface.h>
#include <vgui_controls/Panel.h>
#include <vgui_controls/ToolWindow.h>
#include <vgui_controls/Menu.h>
#include <vgui_controls/PropertySheet.h>

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

using namespace vgui;

CUtlReference< DXEditorPanel > DXEditorPanel::m_refInstance = CUtlReference< DXEditorPanel >();

void DXEditorPanel::DestroyEditor()
{
	DXEditorPanel *pPanel = DXEditorPanel::m_refInstance.m_pObject;

	if ( pPanel )
		pPanel->DeletePanel();
}

void DXEditorPanel::MakeReadyForUse()
{
	BaseClass::MakeReadyForUse();
}

void DXEditorPanel::ToggleEditor()
{
	DXEditorPanel *pPanel = DXEditorPanel::m_refInstance.m_pObject;

	if ( pPanel == NULL )
	{
		VPANEL editorParent = enginevgui->GetPanel( PANEL_TOOLS );

		pPanel = new DXEditorPanel( editorParent );
		pPanel->MakeReadyForUse();
		pPanel->SetVisible( true );

		DXEditorPanel::m_refInstance.Set( pPanel );

		Msg( "Created editor panel\n" );
	}
	else
	{
		pPanel->SetVisible( !pPanel->IsVisible() );
	}

	if ( pPanel->IsVisible() )
	{
		// Populate if we're visible
		pPanel->PopulateEditor();
	}

	Assert( pPanel != NULL );
}

bool DXEditorPanel::IsEditorVisible()
{
	DXEditorPanel *pPanel = DXEditorPanel::m_refInstance.m_pObject;

	return pPanel && pPanel->IsVisible();
}

void DXEditorPanel::PopulateEditor()
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
			EditablePanel* pPage = pagesToPopulate[i];
			m_pToolWindow->AddPage(pPage, pPage->GetName(), false);
			m_pToolWindow->Activate();
			toolWindows.AddToTail(m_pToolWindow);
		}
		// Set sizes of tool windows
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
			else if(page == m_vecPanels[2] || page == m_vecPanels[3]) // welcome + viewport
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
		// Tab groups
		for (int i = 0; i < toolWindows.Count(); i++)
		{
			if (i == 0)
				continue;
			// Combine with previous tool window if their sizes and positions are the same
			ToolWindow* pToolWindow = toolWindows[i];
			Assert(pToolWindow != NULL);
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
	
	// Bring all children to the front (tool windows, menubar, etc.)
	for ( int i = 0; i < GetChildCount(); i++ )
	{
		Panel* pChild = GetChild( i );
		if ( pChild )
			pChild->MoveToFront();
	}
}

void DXEditorPanel::OnMousePressed(MouseCode code)
{
	BaseClass::OnMousePressed(code);
}

void DXEditorPanel::Think()
{
	// Always bring the label to the front
	m_pLabel->SetZPos( 1000 );
}

DXEditorPanel::DXEditorPanel( VPANEL pParent )
	: BaseClass( NULL, "DXEditorPanel", false )
{
	int w,h;
	engine->GetScreenSize( w, h );
	SetBounds( 0, 0, w, h );

	vgui::HScheme scheme = vgui::scheme()->LoadSchemeFromFile( "resource/directorscut/dxscheme.res", "DXScheme" );
	SetScheme(scheme);
	SetPaintBackgroundEnabled( true );
	SetParent( pParent );

	// Create panel to hold everything
	m_pPanel = new Frame( this, "panel", false );
	m_pPanel->SetPaintBackgroundEnabled( true );
	m_pPanel->SetPaintBorderEnabled( false );
	m_pPanel->SetPaintEnabled( true );
	m_pPanel->SetDragEnabled( false );
	m_pPanel->SetCloseButtonVisible( false );
	m_pPanel->SetSizeable( false );
	m_pPanel->SetMoveable( false );
	m_pPanel->SetTitleBarVisible( false );
	m_pPanel->SetMouseInputEnabled( true );
	m_pPanel->SetKeyBoardInputEnabled( true );
	m_pPanel->Activate();
	m_pPanel->SetBounds( 0, -42, w, 16 );

	// Create menu bar
	m_pMenuBar = new MenuBar( m_pPanel, "menu_bar" );
	m_pMenuBar->SetBounds( 0, 42, w, 24 );
	m_pMBut_File = new MenuButton( m_pPanel, "mbut_file", "File" );
	Menu *pMenu_File = new Menu( m_pMBut_File, "" );
	pMenu_File->AddMenuItem( "New", "New", "newfile", this );
	pMenu_File->AddMenuItem( "Open", "Open", "openfile", this );
	pMenu_File->AddMenuItem( "Save", "Save", "savefile", this );
	pMenu_File->AddMenuItem( "Save As", "Save As", "savefileas", this );
	pMenu_File->AddMenuItem( "Close", "Close", "closefile", this );
	pMenu_File->AddSeparator();
	pMenu_File->AddMenuItem( "New (KeyValues)", "New (KeyValues)", "newfilekv", this );
	pMenu_File->AddMenuItem( "Open (KeyValues)", "Open (KeyValues)", "openfilekv", this );
	pMenu_File->AddMenuItem( "Save (KeyValues)", "Save (KeyValues)", "savefilekv", this );
	pMenu_File->AddMenuItem( "Save As (KeyValues)", "Save As (KeyValues)", "savefileaskv", this );
	pMenu_File->AddMenuItem( "Close (KeyValues)", "Close (KeyValues)", "closefilekv", this );
	pMenu_File->AddSeparator();
	pMenu_File->AddMenuItem( "Toggle Work Camera", "Toggle Work Camera", "toggleworkcamera", this );
	m_pMBut_File->SetMenu( pMenu_File );
	m_pMenuBar->AddButton( m_pMBut_File );

	// Create label in bottom left (after panel)
	m_pLabel = new Label( m_pMenuBar, "label", "Director's Cut by KiwifruitDev" );
	m_pLabel->SizeToContents();
	m_pLabel->SetPos( w - m_pLabel->GetWide() - 6, 6 );
	m_pLabel->SetZPos( 1000 );

	// Add windows
	m_vecPanels.AddToTail( new DXEditorElementViewer( this ) );
	m_vecPanels.AddToTail( new DXEditorAnimationSetEditor( this ) );
	m_vecPanels.AddToTail( new DXEditorViewport( this ) );
	m_vecPanels.AddToTail( new DXEditorWelcome( this ) );
	m_vecPanels.AddToTail( new DXEditorAssetBrowser( this ) );
	m_vecPanels.AddToTail( new DXEditorTimeline( this ) );
	m_vecPanels.AddToTail( new DXEditorProperties( this ) );

	PopulateEditor();
}

void DXEditorPanel::OpenDocumentFileDialog(bool bSave)
{
	if ( m_hFileOpenDialog.Get() )
		m_hFileOpenDialog.Get()->MarkForDeletion();

	m_hFileOpenDialog = new FileOpenDialog( this,
		bSave ? "Save session" : "Load session",
		bSave ? FOD_SAVE : FOD_OPEN,
		new KeyValues("FileOpenContext", "context",
		bSave ? "savec" : "openc" )
		);
	m_hFileOpenDialog->AddActionSignalTarget( this );

	if ( m_hFileOpenDialog.Get() )
	{
		m_hFileOpenDialog->AddFilter( "*.dmx", "Datamodel (*.dmx)", true );
		m_hFileOpenDialog->DoModal( true );
	}
}

void DXEditorPanel::OpenKeyValuesDocumentFileDialog(bool bSave)
{
	if ( m_hFileOpenDialog.Get() )
		m_hFileOpenDialog.Get()->MarkForDeletion();

	m_hFileOpenDialog = new FileOpenDialog( this,
		bSave ? "Save session (KeyValues)" : "Load session (KeyValues)",
		bSave ? FOD_SAVE : FOD_OPEN,
		new KeyValues("FileOpenContext", "context",
		bSave ? "saveckv" : "openckv" )
		);
	m_hFileOpenDialog->AddActionSignalTarget( this );

	if ( m_hFileOpenDialog.Get() )
	{
		m_hFileOpenDialog->AddFilter( "*.vdf", "KeyValues (*.vdf)", true );
		m_hFileOpenDialog->DoModal( true );
	}
}

void DXEditorPanel::OnCommand(char const *cmd )
{
	if ( !Q_stricmp( cmd, "newfile" ) )
	{
		DirectorsCutGameSystem().NewDocument();
	}
	else if ( !Q_stricmp( cmd, "openfile" ) )
	{
		OpenDocumentFileDialog(false);
	}
	else if ( !Q_stricmp( cmd, "savefile" ) )
	{
		if(DirectorsCutGameSystem().GetFileOpen() == false)
			return;
		if(DirectorsCutGameSystem().GetLoadedDocumentName() == NULL)
			OpenDocumentFileDialog(true);
		else
			DirectorsCutGameSystem().SaveDocument();
	}
	else if ( !Q_stricmp( cmd, "savefileas" ) )
	{
		if(DirectorsCutGameSystem().GetFileOpen() == false)
			return;
		OpenDocumentFileDialog(true);
	}
	else if ( !Q_stricmp( cmd, "closefile" ) )
	{
		DirectorsCutGameSystem().CloseDocument();
	}
	else if ( !Q_stricmp( cmd, "newfilekv" ) )
	{
		DirectorsCutGameSystem().NewKeyValuesDocument();
	}
	else if ( !Q_stricmp( cmd, "openfilekv" ) )
	{
		OpenKeyValuesDocumentFileDialog(false);
	}
	else if ( !Q_stricmp( cmd, "savefilekv" ) )
	{
		if(DirectorsCutGameSystem().GetFileOpen() == false)
			return;
		if(DirectorsCutGameSystem().GetLoadedDocumentName() == NULL)
			OpenKeyValuesDocumentFileDialog(true);
		else
			DirectorsCutGameSystem().SaveKeyValuesDocument();
	}
	else if ( !Q_stricmp( cmd, "savefileaskv" ) )
	{
		if(DirectorsCutGameSystem().GetFileOpen() == false)
			return;
		OpenKeyValuesDocumentFileDialog(true);
	}
	else if ( !Q_stricmp( cmd, "closefilekv" ) )
	{
		DirectorsCutGameSystem().CloseKeyValuesDocument();
	}
	else if ( !Q_stricmp( cmd, "toggleworkcamera" ) )
	{
		DirectorsCutGameSystem().SetWorkCameraActive(!DirectorsCutGameSystem().IsWorkCameraActive());
	}
	else
	{
		BaseClass::OnCommand( cmd );
	}
}

void DXEditorPanel::OnFileSelected(KeyValues* pKV)
{
	KeyValues* pContext = pKV->FindKey("FileOpenContext");
	if (!pContext)
		return;
	const char* __c = pContext->GetString("context");

	bool bKeyValues = false;
	if (!Q_stricmp(__c, "openckv") || !Q_stricmp(__c, "saveckv"))
		bKeyValues = true;

	bool bSaving = true;
	if (!Q_stricmp(__c, "openc") || !Q_stricmp(__c, "openckv"))
		bSaving = false;

	const char* pathIn = pKV->GetString("fullpath");
	if (Q_strlen(pathIn) <= 1)
		return;

	if(!bKeyValues)
	{
		if (!bSaving)
			DirectorsCutGameSystem().LoadDocument(pathIn);
		else
			DirectorsCutGameSystem().SaveDocument(pathIn);
	}
	else
	{
		if (!bSaving)
			DirectorsCutGameSystem().LoadKeyValuesDocument(pathIn);
		else
			DirectorsCutGameSystem().SaveKeyValuesDocument(pathIn);
	}
}

DXEditorPanel::~DXEditorPanel()
{
}

void DXEditorPanel::ApplySchemeSettings( IScheme *scheme )
{
	BaseClass::ApplySchemeSettings( scheme );

	SetPaintBackgroundEnabled(true);
	SetPaintBorderEnabled(false);
	SetPaintEnabled(true);
	MakeReadyForUse();

	for (int i = 0; i < m_vecPanels.Count(); i++)
	{
		EditablePanel* pPage = m_vecPanels[i];
		if (pPage)
		{
			pPage->SetBgColor(GetSchemeColor("DXEditorPanelPage.BgColor", scheme));
			pPage->SetFgColor(GetSchemeColor("DXEditorPanelPage.FgColor", scheme));
			pPage->SetPaintBackgroundType(2);
		}
	}
}

void DXEditorPanel::PerformLayout()
{
	BaseClass::PerformLayout();

	int w,h;
	engine->GetScreenSize( w, h );
	SetBounds( 0, 0, w, h );

	m_pPanel->SetWide( GetWide() );
	m_pMenuBar->SetWide( GetWide() );
	m_pLabel->SetPos( 8, GetTall() - m_pLabel->GetTall() - 8 );
}

void DXEditorPanel::PaintBackground()
{
	//BaseClass::PaintBackground();

	// First, paint the background
	surface()->DrawSetColor( 31, 31, 31, 240 );
	surface()->DrawFilledRect( 0, 0, GetWide(), GetTall() );

	// Paint a rudimentary dark grid
	int w,h;
	GetSize( w, h );

	surface()->DrawSetColor( 16, 16, 16, 64 );

	for (int i = 0; i < w; i += 10)
	{
		surface()->DrawLine( i, 0, i, h );
	}

	for (int i = 0; i < h; i += 10)
	{
		surface()->DrawLine( 0, i, w, i );
	}
}
