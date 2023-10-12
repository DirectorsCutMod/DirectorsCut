//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window for Director's Cut
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include <KeyValues.h>

#include "dxeditorpanel.h"

#include "ienginevgui.h"
#include "collisionutils.h"
#include <vgui/IVGui.h>
#include <vgui/IInput.h>
#include <vgui/ISurface.h>
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
		pPanel->SetVisible( !pPanel->IsVisible() );

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
		// Animation Set Editor: x 0, y 24, w 1/4 width, h 1/2 height + 1/4 height - 1/8 height
		// Element Viewer: Add page to Animation Set Editor
		// Viewport: x 1/2 width - 1/4 width, y 24, w 1/2 width + 1/4 width, h 1/2 height + 1/4 height - 1/8 height
		// Timeline: fill bottom under viewport and animation set editor
		int w, h;
		GetSize(w, h);
		int animationSetEditorX = 0;
		int animationSetEditorY = 24;
		int animationSetEditorW = w / 4;
		int animationSetEditorH = (h / 2 + h / 4) - h / 8;
		int viewportX = w / 2 - w / 4;
		int viewportY = 24;
		int viewportW = w / 2 + w / 4;
		int viewportH = (h / 2 + h / 4) - h / 8;
		int timelineX = 0;
		int timelineY = ((h / 2 + h / 4) - h / 8) + 24;
		int timelineW = w;
		int timelineH = h - timelineY;
		ToolWindow* animationSetEditor = NULL;
		for (int i = 0; i < toolWindows.Count(); i++)
		{
			ToolWindow* pToolWindow = toolWindows[i];
			Panel* page = pToolWindow->GetActivePage();
			if (page == m_vecPanels[0])
			{
				animationSetEditor = pToolWindow;
				pToolWindow->SetBounds(animationSetEditorX, animationSetEditorY, animationSetEditorW, animationSetEditorH);
			}
			else if (page == m_vecPanels[1])
			{
				if (animationSetEditor != NULL)
				{
					PropertySheet* sheet = pToolWindow->GetPropertySheet();
					sheet->RemovePage(page);
					if ( sheet->GetNumPages() == 0 )
					{
						pToolWindow->MarkForDeletion();
					}
					animationSetEditor->AddPage(page, page->GetName(), false);
				}
				else
				{
					animationSetEditor = pToolWindow;
					pToolWindow->SetBounds(animationSetEditorX, animationSetEditorY, animationSetEditorW, animationSetEditorH);
				}
			}
			else if (page == m_vecPanels[2])
			{
				pToolWindow->SetBounds(viewportX, viewportY, viewportW, viewportH);
			}
			else if (page == m_vecPanels[3])
			{
				pToolWindow->SetBounds(timelineX, timelineY, timelineW, timelineH);
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
	m_pMBut_File->AddActionSignalTarget( this );
	Menu *pMenu_File = new Menu( m_pMBut_File, "" );
	pMenu_File->AddMenuItem( "New", new KeyValues("onmenufile","entry",ER_FMENU_NEW), m_pPanel );
	pMenu_File->AddSeparator();
	pMenu_File->AddMenuItem( "Open", new KeyValues("onmenufile","entry",ER_FMENU_OPEN), m_pPanel );
	pMenu_File->AddSeparator();
	pMenu_File->AddMenuItem( "Save", new KeyValues("onmenufile","entry",ER_FMENU_SAVE), m_pPanel );
	pMenu_File->AddMenuItem( "Save as", new KeyValues("onmenufile","entry",ER_FMENU_SAVE_AS), m_pPanel );
	pMenu_File->AddMenuItem( "Save all", new KeyValues("onmenufile","entry",ER_FMENU_SAVE_ALL), m_pPanel );
	pMenu_File->AddSeparator();
	pMenu_File->AddMenuItem( "Undo", new KeyValues("onmenufile","entry",ER_FMENU_UNDO), m_pPanel );
	pMenu_File->AddMenuItem( "Redo", new KeyValues("onmenufile","entry",ER_FMENU_REDO), m_pPanel );
	pMenu_File->AddSeparator();
	pMenu_File->AddMenuItem( "Take screenshot", new KeyValues("onmenufile","entry",ER_FMENU_SCREENSHOT), m_pPanel );
	pMenu_File->AddMenuItem( "Editor config", new KeyValues("onmenufile","entry",ER_FMENU_ECONFIG), m_pPanel );
	m_pMBut_File->SetMenu( pMenu_File );
	m_pMenuBar->AddButton( m_pMBut_File );

	// Create label in bottom left (after panel)
	m_pLabel = new Label( m_pMenuBar, "label", "Director's Cut by KiwifruitDev" );
	m_pLabel->SizeToContents();
	m_pLabel->SetPos( w - m_pLabel->GetWide() - 6, 6 );
	m_pLabel->SetZPos( 1000 );

	// Add windows
	m_vecPanels.AddToTail( new DXEditorAnimationSetEditor( this ) );
	m_vecPanels.AddToTail( new DXEditorElementViewer( this ) );
	m_vecPanels.AddToTail( new DXEditorViewport( this ) );
	m_vecPanels.AddToTail( new DXEditorTimeline( this ) );

	PopulateEditor();
}

void DXEditorPanel::OnMenuFile( int entry )
{
	switch ( entry )
	{
	case ER_FMENU_NEW: // new
		Msg( "New\n" );
		break;
	case ER_FMENU_OPEN: // open
		Msg( "Open\n" );
		break;
	case ER_FMENU_SAVE: // save
		Msg( "Save\n" );
		break;
	case ER_FMENU_SAVE_AS: // save as
		Msg( "Save as\n" );
		break;
	case ER_FMENU_SAVE_ALL:
		Msg( "Save all\n" );
		break;
	case ER_FMENU_SCREENSHOT: // screenshot
		Msg( "Screenshot\n" );
		break;
	case ER_FMENU_ECONFIG: // editor config
		Msg( "Editor config\n" );
		break;
	case ER_FMENU_UNDO:
		Msg( "Undo\n" );
		break;
	case ER_FMENU_REDO:
		Msg( "Redo\n" );
		break;
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
