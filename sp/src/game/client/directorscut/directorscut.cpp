//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Director's Cut system.
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "directorscut.h"
#include "vgui/dxeditorpanel.h"
#include <vgui/ISurface.h>
#include <vgui/IInput.h>
#include "vguimatsurface/imatsystemsurface.h"
#include "iviewrender.h"
#include <vgui_controls/Controls.h>
#include <hl2_gamerules.h>

#include <string>
#include <regex>

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

// Camera movement speed
ConVar cameraMovementSpeedMin( "dx_cameramovementspeedmin", "100.0", 0, "Minimum speed of the camera when moving with WASD" );
ConVar cameraMovementSpeedMax( "dx_cameramovementspeedmax", "1000.0", 0, "Maximum speed of the camera when moving with WASD" );

// Mouse sensitivity
ConVar mouseSensitivity( "dx_mousesensitivity", "0.3", 0, "View mouse sensitivity" );

// Which mouse button to move the camera
ConVar mouseMoveButton( "dx_mousemovebutton", "1", 0, "1: Left mouse button, 2: Right mouse button, 3: Middle mouse button" );

// Viewport size
ConVar viewportWidth( "dx_viewportwidth", "1280", FCVAR_ARCHIVE, "Viewport width" );
ConVar viewportHeight( "dx_viewportheight", "720", FCVAR_ARCHIVE, "Viewport height" );

// Timeline zoom increment
ConVar timelineZoomIncrement( "dx_timelinezoomincrement", "10", 0, "Timeline zoom increment" );

CON_COMMAND(dx_loaddocument, "Loads a DMX document")
{
	DirectorsCutGameSystem().LoadDocument(args[1]);
}

CON_COMMAND(dx_update, "Updates the DMX document")
{
	DirectorsCutGameSystem().SetAllNeedsUpdate(true);
	Msg("Updated\n");
}

// Viewport RT
static IMaterial* pPrimaryScreenMaterial;
static KeyValues* pPrimaryScreenKV;
static CTextureReference nPrimaryScreenTextureRef;
static int nPrimaryScreenTextureID;

IMaterial* GetPrimaryScreenMaterial()
{
	if (pPrimaryScreenMaterial != NULL)
		return pPrimaryScreenMaterial;
	AllocatePrimaryViewport();
	Assert(pPrimaryScreenMaterial != NULL);
	return pPrimaryScreenMaterial;
}

KeyValues* GetPrimaryScreenKV()
{
	if (pPrimaryScreenKV != NULL)
		return pPrimaryScreenKV;
	AllocatePrimaryViewport();
	Assert(pPrimaryScreenKV != NULL);
	return pPrimaryScreenKV;
}

ITexture* GetPrimaryViewportTex()
{
	if (nPrimaryScreenTextureRef.IsValid())
		return nPrimaryScreenTextureRef;
	AllocatePrimaryViewport();
	Assert(nPrimaryScreenTextureRef.IsValid());
	return nPrimaryScreenTextureRef;
}

int GetPrimaryViewportTexID()
{
	if (nPrimaryScreenTextureID != -1)
		return nPrimaryScreenTextureID;
	AllocatePrimaryViewport();
	Assert(nPrimaryScreenTextureID != -1);
	return nPrimaryScreenTextureID;
}

void AllocatePrimaryViewport()
{
	// Create new RT
	DeallocatePrimaryViewport();

	int viewportWidth = DirectorsCutGameSystem().GetViewportWidth();
	int viewportHeight = DirectorsCutGameSystem().GetViewportHeight();

	g_pMaterialSystem->BeginRenderTargetAllocation();
	nPrimaryScreenTextureRef.Init(g_pMaterialSystem->CreateNamedRenderTargetTextureEx2(
		"_rt_DXPrimaryViewport",
		viewportWidth, viewportHeight, RT_SIZE_OFFSCREEN,
		g_pMaterialSystem->GetBackBufferFormat(),
		MATERIAL_RT_DEPTH_SHARED,
		0,
		CREATERENDERTARGETFLAGS_HDR));
	g_pMaterialSystem->EndRenderTargetAllocation();

	pPrimaryScreenKV = new KeyValues("UnlitGeneric");
	pPrimaryScreenKV->SetString("$basetexture", "_rt_DXPrimaryViewport");
	pPrimaryScreenKV->SetInt("$ignorez", 1);
	pPrimaryScreenKV->SetInt("$nofog", 1);

	pPrimaryScreenMaterial = materials->CreateMaterial("__DXPrimaryViewport", pPrimaryScreenKV);
	pPrimaryScreenMaterial->Refresh();
	nPrimaryScreenTextureID = surface()->CreateNewTextureID();
	g_pMatSystemSurface->DrawSetTextureMaterial(nPrimaryScreenTextureID, pPrimaryScreenMaterial);
}

void DeallocatePrimaryViewport()
{
	if (pPrimaryScreenMaterial != NULL)
	{
		pPrimaryScreenMaterial->Release();
		pPrimaryScreenMaterial = NULL;
	}

	if (pPrimaryScreenKV != NULL)
	{
		pPrimaryScreenKV->Clear();
		pPrimaryScreenKV = NULL;
	}

	if (nPrimaryScreenTextureRef.IsValid())
	{
		nPrimaryScreenTextureRef.Shutdown();
		nPrimaryScreenTextureRef.Init(NULL);
	}
}

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

bool DXEditorHelper::Init()
{
	SetViewportWidth(viewportWidth.GetInt());
	SetViewportHeight(viewportHeight.GetInt());
	DXEditorPanel::ToggleEditor();
	return true;
}

void DXEditorHelper::LevelInitPostEntity()
{
	AllocatePrimaryViewport();
};

void DXEditorHelper::LevelShutdownPostEntity()
{
	DeallocatePrimaryViewport();
};

void DXEditorHelper::LoadDocument( const char* pszDocumentName )
{
	//DECLARE_DMX_CONTEXT_NODECOMMIT();
	CloseDocument();
	CDmxElement* document = (CDmxElement*)DMXAlloc( 100000000 );

	// Mark timestamp so we can document how long it takes to load
	double flStartTime = Plat_FloatTime();

	// Read for a bit to find "keyvalues2" or "binary"
	FileHandle_t fh = filesystem->Open(pszDocumentName, "r", "DEFAULT_WRITE_PATH");
	char buf[64];
	filesystem->Read(buf, 64, fh);
	filesystem->Close(fh);

	bool bBinary = false;
	if (strstr(buf, "binary"))
	{
		bBinary = true;
	}

	fh = filesystem->Open(pszDocumentName, "r", "DEFAULT_WRITE_PATH");
	CUtlBuffer::BufferFlags_t flags = bBinary ? CUtlBuffer::READ_ONLY : CUtlBuffer::TEXT_BUFFER;
	CUtlBuffer buffer = CUtlBuffer(0, 0, flags);
	filesystem->ReadToBuffer(fh, buffer);
	filesystem->Close(fh);

	// If text, find all mentions of "time" and "time_array" and replace them with "float" and "float_array"
	Msg("Converting session format: \"time\" -> \"float\", \"time_array\" -> \"float_array\"\n");
	if (!bBinary)
	{
		Msg("Text session format detected, continuing...\n");
		// Replace all "time" with "float" and "time_array" with "float_array"
		// This is because the DMX parser doesn't support "time" and "time_array" types
		const char * pszBuffer = buffer.String();
		const char * pszTime = "\"time\"";
		const char * pszTimeArray = "\"time_array\"";
		const char * pszFloat = "\"float\"";
		const char * pszFloatArray = "\"float_array\"";
		std::string strBuffer = pszBuffer;
		std::regex rgxTime(pszTime);
		std::regex rgxTimeArray(pszTimeArray);
		std::regex rgxFloat(pszFloat);
		std::regex rgxFloatArray(pszFloatArray);
		std::string strReplaced = std::regex_replace(strBuffer, rgxTime, pszFloat);
		strReplaced = std::regex_replace(strReplaced, rgxTimeArray, pszFloatArray);
		buffer.Clear();
		buffer.PutString(strReplaced.c_str());
	}
	else
	{
		Warning("Binary session format detected, failed to convert!\nPlease run the following command in the origin mod's bin folder:\n");
		Warning("dmxconvert -i session.dmx -oe keyvalues2 -o session_kv2.dmx\n");
	}

	if (UnserializeDMX(buffer, &document, pszDocumentName))
	{
		//IterateDmxElement(document);
		SetDocument(document);
		SetFileOpen(true);
		SetDocumentFocusedRoot(NULL);
		m_pszLoadedDocumentName = pszDocumentName;

		// Get timestamp and print how long it took to load
		double flEndTime = Plat_FloatTime();
		double flTimeTaken = flEndTime - flStartTime;
		Msg("Finished loading session in %f seconds\n", flTimeTaken);
	}
	else
		Warning("Could not read DMX file %s\n", pszDocumentName);
	
	SetAllNeedsUpdate(true);
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
	SetAllNeedsUpdate(true);
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

	// Mark timestamp so we can document how long it takes to save
	double flStartTime = Plat_FloatTime();

	CUtlBuffer buf = CUtlBuffer(0, 0, CUtlBuffer::TEXT_BUFFER);
	SerializeDMX(buf, document);

	// Replace all "\"unknown\" \"\"" with "\"element_array\"\n[\n]\n"
	// This is because future mods do not support the "unknown" attribute type
	Msg("Converting session format: \"unknown\" -> \"element_array\"\n");
	const char * pszBuffer = buf.String();
	const char * pszUnknown = "\"unknown\"";
	const char * pszElementArray = "\"element_array\"";
	std::string strBuffer = pszBuffer;
	std::regex rgxUnknown(pszUnknown);
	std::string strReplaced = std::regex_replace(strBuffer, rgxUnknown, pszElementArray);
	buf.Clear();
	buf.PutString(strReplaced.c_str());

	FileHandle_t fh = filesystem->Open(pszDocumentName, "w", "DEFAULT_WRITE_PATH");
	filesystem->Write(buf.Base(), buf.TellPut(), fh);
	filesystem->Close(fh);
	m_pszLoadedDocumentName = pszDocumentName;

	// Get timestamp and print how long it took to save
	double flEndTime = Plat_FloatTime();
	double flTimeTaken = flEndTime - flStartTime;
	Msg("Finished saving session in %f seconds\n", flTimeTaken);
}

void DXEditorHelper::CloseDocument()
{
	//DECLARE_DMX_CONTEXT_NODECOMMIT();
	m_dmxContextHelper = new CDMXContextHelper( false );
	SetDocument(NULL);
	SetDocumentFocusedRoot(NULL);
	SetFileOpen(false);
	m_pszLoadedDocumentName = NULL;
	SetAllNeedsUpdate(true);
}

void DXEditorHelper::Update( float ft )
{
	float fps = 24;
	CDmxElement* pRoot = GetDocument();
	if( pRoot != NULL )
	{
		CDmxElement* pSettings = pRoot->GetValue<CDmxElement*>( "settings" );
		if( pSettings != NULL )
		{
			CDmxElement* pRenderSettings = pSettings->GetValue<CDmxElement*>( "renderSettings" );
			if( pRenderSettings != NULL )
			{
				float newFps = pRenderSettings->GetValue<float>( "frameRate" );
				if(newFps > 0)
					fps = newFps;
			}
		}
		if(!IsWorkCameraActive())
		{
			bool setupCamera = false;
			// Find clip in document at playhead position
			CDmxElement* pClip = pRoot->GetValue<CDmxElement*>( "activeClip" );
			if( pClip != NULL )
			{
				CDmxElement* pSubClipTrackGroup = pClip->GetValue<CDmxElement*>( "subClipTrackGroup" );
				if( pSubClipTrackGroup != NULL )
				{
					const CUtlVector<CDmxElement*>& pTracks = pSubClipTrackGroup->GetArray<CDmxElement*>( "tracks" );
					if( pTracks.Count() != 0 )
					{
						CDmxElement* pTrack = pTracks[0];
						if( pTrack != NULL )
						{
							const CUtlVector<CDmxElement*>& pChildren = pTrack->GetArray<CDmxElement*>( "children" );
							if( pChildren.Count() != 0)
							{
								// Find the shot that is currently playing (pChildren[i] -> timeFrame -> start, duration)
								CDmxElement* pChild = NULL;
								for (int i = 0; i < pChildren.Count(); i++)
								{
									CDmxElement* pTimeFrame = pChildren[i]->GetValue<CDmxElement*>( "timeFrame" );
									if (pTimeFrame == NULL)
										continue;
									float flStart = pTimeFrame->GetValue<float>( "start" );
									float flDuration = pTimeFrame->GetValue<float>( "duration" );
									float flPlayhead = GetPlayhead();
									if (flPlayhead >= flStart && flPlayhead <= flStart + flDuration)
									{
										pChild = pChildren[i];
										break;
									}
								}
								if (pChild != NULL)
								{
									// pChild -> camera -> transform -> position, orientation
									CDmxElement* pCamera = pChild->GetValue<CDmxElement*>( "camera" );
									if (pCamera != NULL)
									{
										CDmxElement* pTransform = pCamera->GetValue<CDmxElement*>( "transform" );
										if (pTransform != NULL)
										{
											Vector vecPosition = pTransform->GetValue<Vector>( "position" );
											Quaternion angOrientation = pTransform->GetValue<Quaternion>( "orientation" );
											float flFov = pCamera->GetValue<float>( "fieldOfView" );
											SetSceneCameraOrigin(vecPosition);
											// Convert quaternion to angles
											QAngle angOrientationEuler;
											QuaternionAngles(angOrientation, angOrientationEuler);
											SetSceneCameraAngles(angOrientationEuler);
											SetSceneCameraFOV(flFov);
											setupCamera = true;
										}
									}
								}
							}
						}
					}
				}
			}
			if(!setupCamera)
			{
				SetSceneCameraOrigin(Vector(0, 0, 0));
				SetSceneCameraAngles(QAngle(0, 0, 0));
			}
		}
	}

	// if playback speed is set, advance playhead
	if (GetPlaybackSpeed() != 0)
	{
		SetPlayhead(GetPlayhead() + GetPlaybackSpeed() * ft);
	}

	if (viewportWidth.GetInt() != GetViewportWidth())
	{
		SetViewportWidth(viewportWidth.GetInt());
		AllocatePrimaryViewport();
	}
	if (viewportHeight.GetInt() != GetViewportHeight())
	{
		SetViewportHeight(viewportHeight.GetInt());
		AllocatePrimaryViewport();
	}

	static bool bWasTabDown = false;
	bool bIsTabDown = vgui::input()->IsKeyDown( KEY_TAB );

	if ( bIsTabDown != bWasTabDown )
	{
		if ( bIsTabDown )
			DXEditorPanel::ToggleEditor();

		bWasTabDown = bIsTabDown;

		if(DXEditorPanel::IsEditorVisible())
			DXEditorPanel::m_refInstance->bShowedWelcome = true;
	}

	// Editor must be visible to use any other keys
	if ( !DXEditorPanel::IsEditorVisible() )
		return;

	// Movement keys (m_bMouseCaptured) will move the work camera
	static bool bDebounce = false;
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
	} else if(!bDebounce) {
		// Arrow keys advance one frame
		float frameToSeconds = 1.0f / fps;
		// clamp to nearest 0.000 place
		frameToSeconds = floorf(frameToSeconds * 1000.0f + 0.5f) / 1000.0f;
		if ( vgui::input()->IsKeyDown( KEY_LEFT ) )
		{
			SetPlayhead( GetPlayhead() - frameToSeconds );
			bDebounce = true;
		}
		if ( vgui::input()->IsKeyDown( KEY_RIGHT ) )
		{
			SetPlayhead( GetPlayhead() + frameToSeconds );
			bDebounce = true;
		}
		// space will play/pause
		if (vgui::input()->IsKeyDown(KEY_SPACE))
		{
			float multiplier = 1;
			// modifier key: shift (reverse)
			if (vgui::input()->IsKeyDown(KEY_LSHIFT))
				multiplier = -1;
			// modifier key: ctrl (*2)
			if (vgui::input()->IsKeyDown(KEY_LCONTROL))
				multiplier *= 2;
			// modiifer key: alt (stop)
			if (vgui::input()->IsKeyDown(KEY_LALT))
			{
				SetPlaybackSpeed(0);
				SetPlayhead(0);
				bDebounce = true;
				return;
			}
			if (GetPlaybackSpeed() == 0)
				SetPlaybackSpeed(multiplier);
			else
				SetPlaybackSpeed(0);
			bDebounce = true;
			SetLastTime(GetPlayhead());
		}
		// p will lock/unlock the playhead
		if (vgui::input()->IsKeyDown(KEY_P))
		{
			SetLockPlayhead(!GetLockPlayhead());
			bDebounce = true;
		}
		// plus/minus increase/decrease zoom level
		if (vgui::input()->IsKeyDown(KEY_MINUS) || vgui::input()->IsKeyDown(KEY_EQUAL))
		{
			int nZoomLevel = GetZoomLevel();
			int nIncrement = timelineZoomIncrement.GetInt();
			if (vgui::input()->IsKeyDown(KEY_MINUS))
				nZoomLevel -= nIncrement;
			else
				nZoomLevel += nIncrement;
			// max/min
			if (nZoomLevel > 200)
				nZoomLevel = 200;
			if (nZoomLevel < 30)
				nZoomLevel = 30;
			SetZoomLevel(nZoomLevel);
			bDebounce = true;
		}
		// up and down keys take you to the start time and start time + duration of the clip under the playhead
		if (vgui::input()->IsKeyDown(KEY_UP) || vgui::input()->IsKeyDown(KEY_DOWN))
		{
			bDebounce = true;
			CDmxElement* pRoot = GetDocument();
			if (pRoot != NULL)
			{
				// Find clip in document at playhead position
				CDmxElement* pClip = pRoot->GetValue<CDmxElement*>("activeClip");
				if (pClip != NULL)
				{
					CDmxElement* pSubClipTrackGroup = pClip->GetValue<CDmxElement*>("subClipTrackGroup");
					if (pSubClipTrackGroup != NULL)
					{
						const CUtlVector<CDmxElement*>& pTracks = pSubClipTrackGroup->GetArray<CDmxElement*>("tracks");
						if (pTracks.Count() != 0)
						{
							CDmxElement* pTrack = pTracks[0];
							if (pTrack != NULL)
							{
								const CUtlVector<CDmxElement*>& pChildren = pTrack->GetArray<CDmxElement*>("children");
								if (pChildren.Count() != 0)
								{
									// Find the shot that is currently playing (pChildren[i] -> timeFrame -> start, duration)
									for (int i = 0; i < pChildren.Count(); i++)
									{
										CDmxElement* pTimeFrame = pChildren[i]->GetValue<CDmxElement*>("timeFrame");
										if (pTimeFrame == NULL)
											continue;
										float flStart = pTimeFrame->GetValue<float>("start");
										float flDuration = pTimeFrame->GetValue<float>("duration");
										float flPlayhead = GetPlayhead();
										if (flPlayhead >= flStart && flPlayhead <= flStart + flDuration)
										{
											if (vgui::input()->IsKeyDown(KEY_UP))
												SetPlayhead(flStart);
											else
												SetPlayhead(flStart + flDuration);
											break;
										}
									}
								}
							}
						}
					}
				}
			}
			bDebounce = true;
		}
	} else {
		if (!vgui::input()->IsKeyDown( KEY_LEFT )
			&& !vgui::input()->IsKeyDown( KEY_RIGHT )
			&& !vgui::input()->IsKeyDown( KEY_SPACE )
			&& !vgui::input()->IsKeyDown( KEY_UP )
			&& !vgui::input()->IsKeyDown( KEY_DOWN )
			&& !vgui::input()->IsKeyDown( KEY_P )
			&& !vgui::input()->IsKeyDown( KEY_MINUS )
			&& !vgui::input()->IsKeyDown( KEY_EQUAL ))
			bDebounce = false;
	}
};
