//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window for Director's Cut
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include <vgui/IVGui.h>
#include <KeyValues.h>

#include "dxeditorcontrols.h"

#include "ienginevgui.h"
#include "collisionutils.h"
#include <vgui/IVGui.h>
#include <vgui/IInput.h>
#include <vgui/ISurface.h>
#include <vgui_controls/ToolWindow.h>

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

using namespace vgui;

ConVar dx_editor_show( "dx_editor_show", "0", FCVAR_ARCHIVE, "Show the Director's Cut editor." );

class DXEditorPanel : public Panel
{
	DECLARE_CLASS_SIMPLE( DXEditorPanel, Panel );
	DECLARE_REFERENCED_CLASS( DXEditorPanel );

public:

	static void DestroyEditor();
	static void ToggleEditor();
	static bool IsEditorVisible();
	static VPANEL GetEditorPanel();

	~DXEditorPanel();

	static CUtlReference< DXEditorPanel > m_refInstance;
	DXEditorPage* m_pMainControls;
	DXEditorPage* m_pMainControls2;
	ToolWindow* m_pToolWindow;

protected:
	void ApplySchemeSettings( IScheme *scheme );
	void PerformLayout();
	void PaintBackground();

private:
	DXEditorPanel( VPANEL pParent );
};

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
		VPANEL editorParent = enginevgui->GetPanel( PANEL_INGAMESCREENS );

		pPanel = new DXEditorPanel( editorParent );
		pPanel->MakeReadyForUse();
		pPanel->SetVisible( true );

		DXEditorPanel::m_refInstance.Set( pPanel );
	}
	else
		pPanel->SetVisible( !pPanel->IsVisible() );

	Assert( pPanel != NULL );
}

bool DXEditorPanel::IsEditorVisible()
{
	DXEditorPanel *pPanel = DXEditorPanel::m_refInstance.m_pObject;

	return pPanel && pPanel->IsVisible();
}

VPANEL DXEditorPanel::GetEditorPanel()
{
	if ( !m_refInstance.m_pObject == NULL )
		return (VPANEL)0;

	return m_refInstance->GetVPanel();
}

DXEditorPanel::DXEditorPanel( VPANEL pParent )
	: BaseClass( NULL, "DXEditorPanel" )
{
	SetParent( pParent );
	SetConsoleStylePanel( true );

	m_pMainControls = new DXEditorPage( this );
	m_pMainControls2 = new DXEditorPage(this);
	m_pToolWindow = new ToolWindow(this, true, 0, m_pMainControls, "Director's Cut", true, true);
	m_pToolWindow->AddPage(m_pMainControls2, "Director's Cut 2", true);
	m_pToolWindow->SetScheme( vgui::scheme()->LoadSchemeFromFile( "resource/directorscut/dxscheme.res", "DXScheme" ) );
	m_pToolWindow->Activate();
}

DXEditorPanel::~DXEditorPanel()
{
}

void DXEditorPanel::ApplySchemeSettings( IScheme *scheme )
{
	BaseClass::ApplySchemeSettings( scheme );

	MakeReadyForUse();

	SetPaintBackgroundEnabled( true );

	SetMouseInputEnabled( true );
	SetKeyBoardInputEnabled( true );
}

void DXEditorPanel::PerformLayout()
{
	BaseClass::PerformLayout();

	int w,h;
	engine->GetScreenSize( w, h );
	SetBounds( 0, 0, w, h );
}

void DXEditorPanel::PaintBackground()
{
	BaseClass::PaintBackground();

	// First, paint the background
	surface()->DrawSetColor( 0, 0, 0, 255 );
	surface()->DrawFilledRect( 0, 0, GetWide(), GetTall() );

	// Paint a rudimentary dark grid
	int w,h;
	GetSize( w, h );

	surface()->DrawSetColor( 16, 16, 16, 255 );

	for (int i = 0; i < w; i += 10)
	{
		surface()->DrawLine( i, 0, i, h );
	}

	for (int i = 0; i < h; i += 10)
	{
		surface()->DrawLine( 0, i, w, i );
	}
}

static class DXEditorHelper : public CAutoGameSystemPerFrame
{
	void LevelShutdownPostEntity()
	{
		DXEditorPanel::DestroyEditor();
	};

	void Update( float ft )
	{
		/*
		if ( !engine->IsInGame() )
		{
			if ( DXEditorPanel::IsEditorVisible() )
				DXEditorPanel::ToggleEditor();

			return;
		}
		*/

		static bool bWasTabDown = false;
		bool bIsTabDown = vgui::input()->IsKeyDown( KEY_TAB );

		if ( bIsTabDown != bWasTabDown )
		{
			if ( bIsTabDown )
				DXEditorPanel::ToggleEditor();

			bWasTabDown = bIsTabDown;
		}

		/*
		if(dx_editor_show.GetBool())
		{
			if(!DXEditorPanel::IsEditorVisible())
				DXEditorPanel::ToggleEditor();
		}
		else
		{
			if(DXEditorPanel::IsEditorVisible())
				DXEditorPanel::ToggleEditor();
		}
		*/
	};
} __g_lightEditorHelper;
