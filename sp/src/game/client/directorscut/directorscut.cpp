//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Director's Cut system.
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "directorscut.h"
#include "vgui/dxeditorpanel.h"
#include <vgui/IInput.h>
#include <vgui_controls/Controls.h>

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

// Camera movement speed
ConVar cameraMovementSpeedMin( "dx_cameramovementspeedmin", "100.0", 0, "Minimum speed of the camera when moving with WASD" );
ConVar cameraMovementSpeedMax( "dx_cameramovementspeedmax", "1000.0", 0, "Maximum speed of the camera when moving with WASD" );

// Mouse sensitivity
ConVar mouseSensitivity( "dx_mousesensitivity", "0.4", 0, "View mouse sensitivity" );

// Which mouse button to move the camera
ConVar mouseMoveButton( "dx_mousemovebutton", "1", 0, "1: Left mouse button, 2: Right mouse button, 3: Middle mouse button" );

// DMX
void IterateDmxElement(CDmxElement* pRoot)
{
	for (int i=0;i<pRoot->AttributeCount();i++)
	{
		CDmxAttribute* pCur = pRoot->GetAttribute(i);
		CDmxElement* subElem;
		
		Warning( "%s: ",pCur->GetName() );

		switch (pCur->GetType())
		{
		case AT_ELEMENT:
			subElem = pCur->GetValue<CDmxElement*>();
			if (subElem)
				IterateDmxElement(subElem);
			break;

		case AT_STRING:
			Msg( "STRING | %s\n",pCur->GetValue<CUtlString>().Get() );
			break;
		case AT_INT:
			Msg( "INT | %i\n",pCur->GetValue<int>() );
			break;
		case AT_FLOAT:
			Msg( "FLOAT | %f\n",pCur->GetValue<float>() );
			break;
		case AT_BOOL:
			Msg( "BOOL | %s\n",pCur->GetValue<bool>() ? "true" : "false" );
			break;
		
		default:
			Msg("Unknown type %i\n",pCur->GetType());
			break;
		}
	}
}

// DXEditorHelper
DXEditorHelper g_DirectorsCutSystem;
DXEditorHelper &DirectorsCutGameSystem()
{
	return g_DirectorsCutSystem;
}

void DXEditorHelper::LoadDocument( const char* pszDocumentName )
{
	//DECLARE_DMX_CONTEXT_NODECOMMIT();
	CloseDocument();
	
	CDmxElement* document = (CDmxElement*)DMXAlloc( 50000000 );

	if (UnserializeDMX(pszDocumentName, "MOD", true, &document))
	{
		//IterateDmxElement(document);
		SetDocument(document);
		SetFileOpen(true);
		SetDocumentFocusedRoot(NULL);
	}
	else
		Warning("Could not read DMX file %s\n", pszDocumentName);
	DirectorsCutGameSystem().SetNeedsUpdate(true);
}

void DXEditorHelper::NewDocument()
{
	//DECLARE_DMX_CONTEXT_NODECOMMIT();
	CloseDocument();
	
	CDmxElement* DMX = CreateDmxElement("DmElement");
	DMX->AddAttribute("name")->SetValue("session");
	DMX->AddAttribute("editorType")->SetValue("directorscut");
	CDmxElement* clip = CreateDmxElement("DmeFilmClip");
	clip->AddAttribute("name")->SetValue("sequence");
	DMX->AddAttribute("activeClip")->SetValue<CDmxElement*>(clip);
	DMX->AddAttribute("miscBin")->GetArrayForEdit<CDmxElement*>(); // empty array
	DMX->AddAttribute("cameraBin")->GetArrayForEdit<CDmxElement*>(); // empty array	
	DMX->AddAttribute("clipBin")->GetArrayForEdit<CDmxElement*>().AddToTail(clip);
	CDmxElement* settings = CreateDmxElement("DmSettings");
	settings->AddAttribute("name")->SetValue("sessionSettings");
	DMX->AddAttribute("settings")->SetValue<CDmxElement*>(settings);

	SetDocument(DMX);
	SetDocumentFocusedRoot(NULL);
	SetFileOpen(true);
	m_pszLoadedDocumentName = NULL;
	DirectorsCutGameSystem().SetNeedsUpdate(true);
}

void DXEditorHelper::SaveDocument()
{
	if(m_pszLoadedDocumentName)
		SaveDocument(m_pszLoadedDocumentName);
}

void DXEditorHelper::SaveDocument( const char* pszDocumentName )
{
	//DECLARE_DMX_CONTEXT_NODECOMMIT();
	CDmxElement* document = GetDocument();
	if (!document)
		return;
	CUtlBuffer buf;
	SerializeDMX(buf, document);

	FileHandle_t fh = filesystem->Open(pszDocumentName, "w", "DEFAULT_WRITE_PATH");
	filesystem->Write(buf.Base(), buf.TellPut(), fh);
	filesystem->Close(fh);
	m_pszLoadedDocumentName = pszDocumentName;
}

void DXEditorHelper::CloseDocument()
{
	//DECLARE_DMX_CONTEXT_NODECOMMIT();
	m_dmxContextHelper = new CDMXContextHelper( false );
	SetDocument(NULL);
	SetDocumentFocusedRoot(NULL);
	SetFileOpen(false);
	m_pszLoadedDocumentName = NULL;
	DirectorsCutGameSystem().SetNeedsUpdate(true);
}

CON_COMMAND(dx_loaddocument, "Loads a DMX document")
{
	DirectorsCutGameSystem().LoadDocument(args[1]);
}

CON_COMMAND(dx_update, "Updates the DMX document")
{
	DirectorsCutGameSystem().SetNeedsUpdate(true);
	Msg("Updated\n");
}

void DXEditorHelper::LevelShutdownPostEntity()
{
	DXEditorPanel::DestroyEditor();
};

void DXEditorHelper::Update( float ft )
{
	static bool bWasTabDown = false;
	bool bIsTabDown = vgui::input()->IsKeyDown( KEY_TAB );

	if ( bIsTabDown != bWasTabDown )
	{
		if ( bIsTabDown )
			DXEditorPanel::ToggleEditor();

		bWasTabDown = bIsTabDown;
	}

	// Movement keys (m_bMouseCaptured) will move the work camera
	if ( m_bMouseCaptured )
	{
		// If m_bHoldingMovementKey is false, set m_flCurrentCameraMovementSpeed to default
		if ( !m_bHoldingMovementKey )
		{
			m_flCurrentCameraMovementSpeed = cameraMovementSpeedMin.GetFloat();
		}
		else
		{
			// Increase m_flCurrentCameraMovementSpeed by multiplier until it reaches cameraMovementSpeedMax
			if ( m_flCurrentCameraMovementSpeed < cameraMovementSpeedMax.GetFloat() )
				m_flCurrentCameraMovementSpeed += ( cameraMovementSpeedMax.GetFloat() - cameraMovementSpeedMin.GetFloat() ) * 0.1f * ft;
			else
				m_flCurrentCameraMovementSpeed = cameraMovementSpeedMax.GetFloat();
		}

		// Get forward, right, up vectors
		Vector vecForward, vecRight, vecUp;
		AngleVectors( m_angWorkCameraAngles, &vecForward, &vecRight, &vecUp );

		// Get Shift or Ctrl movement to speed up or slow down
		float flSpeed = 1.0f;
		if ( vgui::input()->IsKeyDown( KEY_LSHIFT ) )
			flSpeed = 5.0f;
		if ( vgui::input()->IsKeyDown( KEY_LCONTROL ) )
			flSpeed = 0.2f;

		// Get W A S D movement
		if ( vgui::input()->IsKeyDown( KEY_W ) )
			m_vecWorkCameraOrigin += vecForward * m_flCurrentCameraMovementSpeed * flSpeed * ft;
		if ( vgui::input()->IsKeyDown( KEY_S ) )
			m_vecWorkCameraOrigin -= vecForward * m_flCurrentCameraMovementSpeed * flSpeed * ft;
		if ( vgui::input()->IsKeyDown( KEY_A ) )
			m_vecWorkCameraOrigin -= vecRight * m_flCurrentCameraMovementSpeed * flSpeed * ft;
		if ( vgui::input()->IsKeyDown( KEY_D ) )
			m_vecWorkCameraOrigin += vecRight * m_flCurrentCameraMovementSpeed * flSpeed * ft;
		
		// Get Z X movement
		if ( vgui::input()->IsKeyDown( KEY_Z ) )
			m_vecWorkCameraOrigin += Vector( 0, 0, m_flCurrentCameraMovementSpeed * flSpeed * ft );
		if ( vgui::input()->IsKeyDown( KEY_X ) )
			m_vecWorkCameraOrigin -= Vector( 0, 0, m_flCurrentCameraMovementSpeed * flSpeed * ft );

		// If holding any movement key, set m_bHoldingMovementKey
		if ( vgui::input()->IsKeyDown( KEY_W ) 
			|| vgui::input()->IsKeyDown( KEY_S )
			|| vgui::input()->IsKeyDown( KEY_A )
			|| vgui::input()->IsKeyDown( KEY_D )
			|| vgui::input()->IsKeyDown( KEY_Z )
			|| vgui::input()->IsKeyDown( KEY_X ) )
			m_bHoldingMovementKey = true;
		else
			m_bHoldingMovementKey = false;
	}
};

void DXEditorHelper::LevelInitPostEntity()
{
};
