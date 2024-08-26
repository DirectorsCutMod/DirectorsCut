//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Director's Cut system.
// Contributors:
// - KiwifruitDev
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
#include "datacache/imdlcache.h"
#include "networkstringtable_clientdll.h"
#include "materialsystem/imaterial.h"
#include "materialsystem/imaterialvar.h"
#include <string>
#include <regex>
#include <beamdraw.h>
#include <iviewrender_beams.h>
#include "engine/ivdebugoverlay.h"
#include <icommandline.h>
#include "datamodel/idatamodel.h"

#include "data/dxe_filmclip.h"
#include "data/dxe_track.h"
#include "data/dxe_bookmarkset.h"
#include "data/kvhelpers.h"
#include "data/dxe_dag.h"
#include "data/dxe_camera.h"
#include "data/dxe_animationset.h"
#include "data/dxe_gamemodel.h"

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

CON_COMMAND(dx_loaddocument, "Loads a session document")
{
	DirectorsCutGameSystem().LoadDocument(args[1]);
}

CON_COMMAND(dx_update, "Updates the session document")
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

// DXEditorHelper
DXEditorHelper g_DirectorsCutSystem;
DXEditorHelper &DirectorsCutGameSystem()
{
	return g_DirectorsCutSystem;
}

bool DXEditorHelper::Init()
{
	//SetDefLessFunc(m_pModels);
	SetViewportWidth(viewportWidth.GetInt());
	SetViewportHeight(viewportHeight.GetInt());
	// Launch option "-nodxeditor" to prevent the editor from opening immediately
	if (CommandLine()->FindParm("-nodxeditor"))
	{
		Msg("Director's Cut: Disabled editor\n");
		return true;
	}
	DXEditorPanel::ToggleEditor();
	return true;
}

model_t* DXEditorHelper::LoadModel(const char* modelName)
{
	model_t* model = (model_t*)engine->LoadModel(modelName);
	if (model != nullptr)
	{
		INetworkStringTable* precacheTable = networkstringtable->FindTable("modelprecache");
		if (precacheTable)
		{
			modelinfo->FindOrLoadModel(modelName);
			int idx = precacheTable->AddString(false, modelName);
			if (idx == INVALID_STRING_INDEX)
			{
				Msg("Director's Cut: Failed to precache model %s\n", modelName);
			}
			else
			{
				model = (model_t*)engine->LoadModel(modelName);
			}
		}
	}
	else
	{
		Msg("Director's Cut: Failed to load model %s\n", modelName);
	}
	return model;
}

void DXEditorHelper::LevelInitPostEntity()
{
	//AllocatePrimaryViewport();
	// Cache sprites
	LoadModel("materials/sprites/light_glow02_add_noz.vmt");
};

void DXEditorHelper::LevelShutdownPostEntity()
{
	DeallocatePrimaryViewport();
};

void DXEditorHelper::SetPlayhead( float fPlayhead )
{
	if(m_fPlayhead == fPlayhead)
		return;
	SetAllNeedsUpdate(true);
	m_fPlayhead = fPlayhead;
	CheckReleaseModel();
}

void DXEditorHelper::LoadDocument( const char* pszDocumentName )
{
	CloseDocument();
	SetAllNeedsUpdate(false);
	
	DxElement* document = new DxElement("session");

	// Mark timestamp so we can document how long it takes to load
	double flStartTime = Plat_FloatTime();

	if (document->LoadFromFile(g_pFullFileSystem, pszDocumentName, NULL, true))
	{
		SetDocument(document);
		SetFileOpen(true);
		m_pszLoadedDocumentName = pszDocumentName;
		SetAllNeedsUpdate(true);

		// Get timestamp and print how long it took to load
		double flEndTime = Plat_FloatTime();
		double flTimeTaken = flEndTime - flStartTime;
		Msg("Finished loading keyvalues session in %f seconds\n", flTimeTaken);
	}
	else
	{
		Warning("Could not read keyvalues file %s\n", pszDocumentName);
	}
}

void DXEditorHelper::NewDocument()
{
	CloseDocument();

	const char* currentMap = engine->GetLevelName();
	// remove maps/ prefix
	if (Q_strstr(currentMap, "maps/") == currentMap)
		currentMap += 5;
	
	DxElement* document = new DxElement("session");
	document->SetElementName("session");
	DxeFilmClip* movie = new DxeFilmClip("activeClip");
	movie->SetElementName("session1");
	movie->GetTimeFrame()->SetDuration(60.0f);
	DxeTrackGroup* soundTrackGroup = new DxeTrackGroup("Sound");
	soundTrackGroup->SetElementName("Sound");
	DxeTrack* dialogTrack = new DxeTrack("Dialog");
	dialogTrack->SetElementName("Dialog");
	dialogTrack->SetClipType(1);
	DxeTrack* musicTrack = new DxeTrack("Music");
	musicTrack->SetElementName("Music");
	musicTrack->SetClipType(1);
	DxeTrack* soundEffectsTrack = new DxeTrack("Effects");
	soundEffectsTrack->SetElementName("Effects");
	soundEffectsTrack->SetClipType(1);
	soundTrackGroup->GetTracks()->AddElement(dialogTrack);
	soundTrackGroup->GetTracks()->AddElement(musicTrack);
	soundTrackGroup->GetTracks()->AddElement(soundEffectsTrack);
	movie->GetTrackGroups()->AddElement(soundTrackGroup);
	movie->SetMapName(currentMap);
	DxeTrackGroup* overlayTrackGroup = new DxeTrackGroup("Overlay");
	overlayTrackGroup->SetElementName("Overlay");
	DxeTrack* overlayEffectsTrack = new DxeTrack("Effects");
	overlayEffectsTrack->SetElementName("Effects");
	overlayEffectsTrack->SetClipType(2);
	overlayTrackGroup->GetTracks()->AddElement(overlayEffectsTrack);
	movie->GetTrackGroups()->AddElement(overlayTrackGroup);
	DxeBookmarkSet* bookmarkSet = new DxeBookmarkSet("Default Set");
	bookmarkSet->SetElementName("Default Set");
	movie->GetBookmarkSets()->AddElement(bookmarkSet);
	DxeTrackGroup* subClipTrackGroup = new DxeTrackGroup("subClipTrackGroup");
	subClipTrackGroup->SetElementName("subClipTrackGroup");
	DxeTrack* filmTrack = new DxeTrack("Film");
	filmTrack->SetElementName("Film");
	filmTrack->SetClipType(3);
	DxeFilmClip* shot = new DxeFilmClip("shot1");
	shot->SetElementName("shot1");
	shot->GetTimeFrame()->SetDuration(60.0f);
	shot->SetActiveCamera("camera1");
	DxeDag* sceneDag = new DxeDag("scene");
	sceneDag->SetElementName("scene");
	DxeDag* camerasDag = new DxeDag("Cameras");
	camerasDag->SetElementName("Cameras");
	DxeCamera* cameraDag = new DxeCamera("camera1");
	cameraDag->SetElementName("camera1");
	DxeTransform* cameraTransform = cameraDag->GetTransform();
	cameraTransform->GetPosition()->SetVector(Vector(0, 0, 100));
	DxeDag* modelDag = new DxeDag("model1");
	modelDag->SetElementName("model1");
	DxeGameModel* gameModel = new DxeGameModel("model_GameModel");
	gameModel->SetElementName("model_GameModel");
	gameModel->SetModelName("models/alyx.mdl");
	DxeTransform* modelTransform = gameModel->GetTransform();
	modelTransform->GetPosition()->SetVector(Vector(10, 10, 10));
	modelTransform->GetOrientation()->SetQuaternion(Quaternion(0, 0, 0, 1));
	DxeTransform* bonePelvis = new DxeTransform("bone 0 (bip_pelvis)");
	bonePelvis->SetElementName("bone 0 (bip_pelvis)");
	bonePelvis->GetPosition()->SetVector(Vector(0, 0, 0));
	bonePelvis->GetOrientation()->SetQuaternion(Quaternion(0, 0, 0, 1));
	gameModel->GetBones()->AddElement(bonePelvis);
	DxeTransform* boneSpine = new DxeTransform("bone 1 (bip_spine)");
	boneSpine->SetElementName("bone 1 (bip_spine)");
	boneSpine->GetPosition()->SetVector(Vector(10, -5, 0));
	boneSpine->GetOrientation()->SetQuaternion(Quaternion(0, 0, 0, 1));
	gameModel->GetBones()->AddElement(boneSpine);
	modelDag->GetChildren()->AddElement(gameModel);
	sceneDag->GetChildren()->AddElement(modelDag);
	QAngle angOrientation = QAngle(15, 15, 15);
	Quaternion rOrientation;
	AngleQuaternion(angOrientation, rOrientation);
	cameraTransform->GetOrientation()->SetQuaternion(rOrientation);
	camerasDag->GetChildren()->AddElement(cameraDag);
	sceneDag->GetChildren()->AddElement(camerasDag);
	shot->AddSubKey(sceneDag);
	DxeAnimationSet* animationSet = new DxeAnimationSet("camera1");
	animationSet->SetElementName("camera1");
	// TODO: Populate controls
	animationSet->AddSubKey(new DxElement("camera")); // recursion doesn't exist, so add a dummy element
	shot->GetAnimationSets()->AddElement(animationSet);
	filmTrack->GetChildren()->AddElement(shot);
	subClipTrackGroup->GetTracks()->AddElement(filmTrack);
	movie->AddSubKey(subClipTrackGroup);
    document->AddSubKey(movie);
    document->AddSubKey(new KvDxElementArray("miscBin"));
    document->AddSubKey(new KvDxElementArray("clipBin"));
    document->AddSubKey(new DxElement("settings"));

	SetDocument(document);
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
	DxElement* document = GetDocument();
	if (!document)
		return;

	// Mark timestamp so we can document how long it takes to save
	double flStartTime = Plat_FloatTime();

	if(document->SaveToFile(g_pFullFileSystem, pszDocumentName, NULL))
	{
		// Get timestamp and print how long it took to save
		double flEndTime = Plat_FloatTime();
		double flTimeTaken = flEndTime - flStartTime;
		Msg("Finished saving keyvalues session in %f seconds\n", flTimeTaken);
	}
	else
		Warning("Could not write keyvalues file %s\n", pszDocumentName);
}

void DXEditorHelper::CloseDocument()
{
	DxElement* document = GetDocument();
	if(!document)
		return;
	DxeFilmClip* shot = GetShotAtCurrentTime();
	if(shot != NULL)
	{
		DxeDag* scene = (DxeDag*)shot->GetScene();
		if(scene != NULL)
		{
			RecursiveReleaseSceneHierarchy(scene);
		}
	}
	document->deleteThis();
	SetDocument(NULL);
	SetFileOpen(false);
	m_pszLoadedDocumentName = NULL;
	SetAllNeedsUpdate(true);
}

void DXEditorHelper::ConvertDMXToKV( const char* pszDocumentName )
{
	//DECLARE_DMX_CONTEXT_DECOMMIT();
	CloseDocument();

	CDmxElement* document = (CDmxElement*)DMXAlloc( 1000000000 );

	// Mark timestamp so we can document how long it takes to load
	//double flStartTime = Plat_FloatTime();

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
	Msg("Converting DMX session format: \"time\" -> \"float\", \"time_array\" -> \"float_array\"\n");
	if (!bBinary)
	{
		Msg("Text DMX session format detected, continuing...\n");
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
		Warning("Binary DMX session format detected, failed to convert!\nPlease run the following command in the origin mod's bin folder:\n");
		Warning("dmxconvert -i session.dmx -oe keyvalues2 -o session_kv2.dmx\n");
	}

	if (UnserializeDMX(buffer, &document, pszDocumentName))
	{
		/*
		// Populate document
		const char* rootName = document->GetName();
		DxElement* dxDocument = new DxElement(rootName);
		dxDocument->SetElementName(rootName);
		CDmxAttribute* dmxMovieAttribute = document->GetAttribute("activeClip");
		if (dmxMovieAttribute != NULL)
		{
			CDmxElement* dmxMovie = dmxMovieAttribute->GetValue();
			if (dmxMovie != NULL)
			{
				const char* sessionName = dmxMovie->GetName();
				DxeFilmClip* dxMovie = new DxeFilmClip("activeClip");
				dxMovie->SetElementName(sessionName);
				CDmxAttribute* dmxTimeFrame = dmxMovie->GetAttribute("timeFrame");
				if (dmxTimeFrame != NULL)
				{
					DxeTimeFrame* dxTimeFrame = dxMovie->GetTimeFrame();
					const char* timeFrameName = dmxTimeFrame->GetName();
					CDmxAttribute* start = dmxTimeFrame->GetAttribute("start");
					if (start != NULL)
						dxTimeFrame->SetStart(start->GetValue());
					CDmxAttribute* duration = dmxTimeFrame->GetAttribute("duration");
					if (duration != NULL)
						dxTimeFrame->SetDuration(duration->GetValue());
					CDmxAttribute* offset = dmxTimeFrame->GetAttribute("offset");
					if (offset != NULL)
						dxTimeFrame->SetOffset(offset->GetValue());
					CDmxAttribute* scale = dmxTimeFrame->GetAttribute("scale");
					if (scale != NULL)
						dxTimeFrame->SetScale(scale->GetValue());
				}
				CDmxAttribute* dmxColor = dmxMovie->GetAttribute("color");
				if (dmxColor != NULL)
					dxMovie->SetColor(dmxColor->GetValue());
				CDmxAttribute* dmxText = dmxMovie->GetAttribute("text");
				if (dmxText != NULL)
					dxMovie->SetText(dmxText->GetValue());
				CDmxAttribute* dmxMute = dmxMovie->GetAttribute("mute");
				if (dmxMute != NULL)
					dxMovie->SetMute(dmxMute->GetValue());
				CDmxAttribute* dmxTrackGroups = dmxMovie->GetAttribute("trackGroups");
				if (dmxTrackGroups != NULL)
				{
					CUtlVector<CDmxElement*> dmxtrackGroupsArray = dmxTrackGroups->GetArrayForEdit<CDmxElement*>();
					for (int i = 0; i < dmxtrackGroupsArray.Count(); i++)
					{
						CDmxElement* dmxTrackGroup = dmxtrackGroupsArray[i];
						const char* trackGroupName = dmxTrackGroup->GetName();
						DxeTrackGroup* dxTrackGroup = new DxeTrackGroup(trackGroupName);
						dxTrackGroup->SetElementName(trackGroupName);
						CDmxAttribute* dmxTracks = dmxTrackGroup->GetAttribute("tracks");
						if (dmxTracks != NULL)
						{
							CUtlVector<CDmxElement*> dmxTracksArray = dmxTracks->GetArrayForEdit<CDmxElement*>();
							for (int j = 0; j < dmxTracksArray.Count(); j++)
							{
								CDmxElement* dmxTrack = dmxTracksArray[j];
								const char* trackName = dmxTrack->GetName();
								DxeTrack* dxTrack = new DxeTrack(trackName);
								dxTrack->SetElementName(trackName);
								//CDmxAttribute* dmxChildren = dmxTrack->GetAttribute("children");
								CDmxAttribute* dmxCollapsed = dmxTrack->GetAttribute("collapsed");
								if (dmxCollapsed != NULL)
									dxTrack->SetCollapsed(dmxCollapsed->GetValue());
								CDmxAttribute* dmxMuteTrack = dmxTrack->GetAttribute("mute");
								if (dmxMuteTrack != NULL)
									dxTrack->SetMute(dmxMuteTrack->GetValue());
								CDmxAttribute* dmxSynched = dmxTrack->GetAttribute("synched");
								if (dmxSynched != NULL)
									dxTrack->SetSynched(dmxSynched->GetValue());
								CDmxAttribute* dmxClipType = dmxTrack->GetAttribute("clipType");
								if (dmxClipType != NULL)
									dxTrack->SetClipType(dmxClipType->GetValue());
								CDmxAttribute* dmxVolume = dmxTrack->GetAttribute("volume");
								if (dmxVolume != NULL)
									dxTrack->SetVolume(dmxVolume->GetValue());
								CDmxAttribute* dmxDisplayScale = dmxTrack->GetAttribute("displayScale");
								if (dmxDisplayScale != NULL)
									dxTrack->SetDisplayScale(dmxDisplayScale->GetValue());
								dxTrackGroup->GetTracks()->AddElement(dxTrack);
							}
						}
						CDmxAttribute* dmxMuteTrackGroup = dmxTrackGroup->GetAttribute("mute");
						if (dmxMuteTrackGroup != NULL)
							dxTrackGroup->SetMute(dmxMuteTrackGroup->GetBool());
						CDmxAttribute* dmxDisplayScale = dmxTrackGroup->GetAttribute("displayScale");
						if (dmxDisplayScale != NULL)
							dxTrackGroup->SetDisplayScale(dmxDisplayScale->GetValue());
						CDmxAttribute* dmxMinimized = dmxTrackGroup->GetAttribute("minimized");
						if (dmxMinimized != NULL)
							dxTrackGroup->SetMinimized(dmxMinimized->GetValue());
						CDmxAttribute* dmxVolume = dmxTrackGroup->GetAttribute("volume");
						if (dmxVolume != NULL)
							dxTrackGroup->SetVolume(dmxVolume->GetValue());
						CDmxAttribute* dmxForceMultiTrack = dmxTrackGroup->GetAttribute("forcemultitrack");
						if (dmxForceMultiTrack != NULL)
							dxTrackGroup->SetForceMultiTrack(dmxForceMultiTrack->GetBool());
						dxMovie->GetTrackGroups()->AddElement(dxTrackGroup);
					}		
				}
				CDmxAttribute* dmxDisplayScale = dmxMovie->GetAttribute("displayScale");
				if (dmxDisplayScale != NULL)
					dxMovie->SetDisplayScale(dmxDisplayScale->GetValue());
				//CDmxAtribute* dmxMaterialOverlay = dmxMovie->GetAttribute("materialOverlay");
				CDmxAttribute* dmxMapName = dmxMovie->GetAttribute("mapname");
				if (dmxMapName != NULL)
					dxMovie->SetMapName(dmxMapName->GetValue());
				CDmxAttribute* dmxCamera = dmxMovie->GetAttribute("camera");
				if (dmxCamera != NULL)
				{
					CDmxElement* dmxCameraElement = dmxCamera->GetValue("camera");
					if (dmxCameraElement != NULL)
					{
						dxMovie->SetActiveCamera(dmxCameraElement->GetName());
					}
				}
				//CDmxAttribute* dmxMonitorCameras = dmxMovie->GetAttribute("monitorCameras");
				//CDmxAttribute* dmxActiveMonitor = dmxMovie->GetAttribute("activeMonitor");
				//CDmxAttribute* dmxScene = dmxMovie->GetAttribute("scene");
				CDmxAttribute* dmxAviFile = dmxMovie->GetAttribute("aviFile");
				if (dmxAviFile != NULL)
					dxMovie->SetAviFile(dmxAviFile->GetValue());
				CDmxAttribute* dmxFadeIn = dmxMovie->GetAttribute("fadeIn");
				if (dmxFadeIn != NULL)
					dxMovie->SetFadeIn(dmxFadeIn->GetValue());
				CDmxAttribute* dmxFadeOut = dmxMovie->GetAttribute("fadeOut");
				if (dmxFadeOut != NULL)
					dxMovie->SetFadeOut(dmxFadeOut->GetValue());
				//CDmxAttribute* dmxInputs = dmxMovie->GetAttribute("inputs");
				//CDmxAttribute* dmxOperators = dmxMovie->GetAttribute("operators");
				CDmxAttribute* dmxUseAviFile = dmxMovie->GetAttribute("useAviFile");
				if (dmxUseAviFile != NULL)
					dxMovie->SetUseAviFile(dmxUseAviFile->GetValue());
				//CDmxAttribute* dmxAnimationSets = dmxMovie->GetAttribute("animationSets");
				CDmxAttribute* dmxBookmarkSets = dmxMovie->GetAttribute("bookmarkSets");
				if (dmxBookmarkSets != NULL)
				{
					CUtlVector<CDmxElement*> dmxBookmarkSetsArray = dmxBookmarkSets->GetArrayForEdit<CDmxElement*>();
					for (int i = 0; i < dmxBookmarkSetsArray.Count(); i++)
					{
						CDmxElement* dmxBookmarkSet = dmxBookmarkSetsArray[i];
						const char* bookmarkSetName = dmxBookmarkSet->GetName();
						DxeBookmarkSet* dxBookmarkSet = new DxeBookmarkSet(bookmarkSetName);
						dxBookmarkSet->SetElementName(bookmarkSetName);
						//CDmxAttribute* dmxBookmarks = dmxBookmarkSet->GetAttribute("bookmarks");
						dxMovie->GetBookmarkSets()->AddElement(dxBookmarkSet);
					}
				}
				CDmxAttribute* dmxActiveBookmarkSet = dmxMovie->GetAttribute("activeBookmarkSet");
				if (dmxActiveBookmarkSet != NULL)
					dxMovie->SetActiveBookmarkSet(dmxActiveBookmarkSet->GetValue());
				CDmxAttribute* dmxSubClipTrackGroup = dmxMovie->GetAttribute("subClipTrackGroup");
				if (dmxSubClipTrackGroup != NULL)
				{
					CDmxElement* dmxSubClipTrackGroupElement = dmxSubClipTrackGroup->GetValue();
					if (dmxSubClipTrackGroupElement != NULL)
					{
						const char* subClipTrackGroupName = dmxSubClipTrackGroupElement->GetName();
						DxeTrackGroup* dxSubClipTrackGroup = new DxeTrackGroup(subClipTrackGroupName);
						dxSubClipTrackGroup->SetElementName(subClipTrackGroupName);
						CDmxAttribute* dmxTracks = dmxSubClipTrackGroupElement->GetAttribute("tracks");
						if (dmxTracks != NULL)
						{
							CUtlVector<CDmxElement*> dmxTracksArray = dmxTracks->GetArrayForEdit<CDmxElement*>();
							for (int i = 0; i < dmxTracksArray.Count(); i++)
							{
								CDmxElement* dmxTrack = dmxTracksArray[i];
								const char* trackName = dmxTrack->GetName();
								DxeTrack* dxTrack = new DxeTrack(trackName);
								dxTrack->SetElementName(trackName);
								//CDmxAttribute* dmxChildren = dmxTrack->GetAttribute("children");
								CDmxAttribute* dmxCollapsed = dmxTrack->GetAttribute("collapsed");
								if (dmxCollapsed != NULL)
									dxTrack->SetCollapsed(dmxCollapsed->GetValue());
								CDmxAttribute* dmxMuteTrack = dmxTrack->GetAttribute("mute");
								if (dmxMuteTrack != NULL)
									dxTrack->SetMute(dmxMuteTrack->GetValue());
								CDmxAttribute* dmxSynched = dmxTrack->GetAttribute("synched");
								if (dmxSynched != NULL)
									dxTrack->SetSynched(dmxSynched->GetValue());
								CDmxAttribute* dmxClipType = dmxTrack->GetAttribute("clipType");
								if (dmxClipType != NULL)
									dxTrack->SetClipType(dmxClipType->GetValue());
								CDmxAttribute* dmxVolume = dmxTrack->GetAttribute("volume");
								if (dmxVolume != NULL)
									dxTrack->SetVolume(dmxVolume->GetValue());
								CDmxAttribute* dmxDisplayScale = dmxTrack->GetAttribute("displayScale");
								if (dmxDisplayScale != NULL)
									dxTrack->SetDisplayScale(dmxDisplayScale->GetValue());
								dxSubClipTrackGroup->GetTracks()->AddElement(dxTrack);
							}
						}
						CDmxAttribute* dmxVisible = dmxSubClipTrackGroupElement->GetAttribute("visible");
						if (dmxVisible != NULL)
							dxSubClipTrackGroup->SetVisible(dmxVisible->GetValue());
						CDmxAttribute* dmxMute = dmxSubClipTrackGroupElement->GetAttribute("mute");
						if (dmxMute != NULL)
							dxSubClipTrackGroup->SetMute(dmxMute->GetValue());
						CDmxAttribute* dmxDisplayScale = dmxSubClipTrackGroupElement->GetAttribute("displayScale");
						if (dmxDisplayScale != NULL)
							dxSubClipTrackGroup->SetDisplayScale(dmxDisplayScale->GetValue());
						CDmxAttribute* dmxMinimized = dmxSubClipTrackGroupElement->GetAttribute("minimized");
						if (dmxMinimized != NULL)
							dxSubClipTrackGroup->SetMinimized(dmxMinimized->GetValue());
						CDmxAttribute* dmxVolume = dmxSubClipTrackGroupElement->GetAttribute("volume");
						if (dmxVolume != NULL)
							dxSubClipTrackGroup->SetVolume(dmxVolume->GetValue());
						CDmxAttribute* dmxForceMultiTrack = dmxSubClipTrackGroupElement->GetAttribute("forcemultitrack");
						if (dmxForceMultiTrack != NULL)
							dxSubClipTrackGroup->SetForceMultiTrack(dmxForceMultiTrack->GetValue());
						dxMovie->AddSubKey(dxSubClipTrackGroup);
					}
				}
				CDmxAttribute* dmxVolume = dmxMovie->GetAttribute("volume");
				if (dmxVolume != NULL)
					dxMovie->SetVolume(dmxVolume->GetValue());
				//CDmxAttribute* dmxConcommands = dmxMovie->GetAttribute("concommands");
				//CDmxAttribute* dmxConvars = dmxMovie->GetAttribute("convars");
				dxDocument->AddSubKey(dxMovie);
			}
		}
		*/
	}
	else
		Warning("Could not read DMX file %s\n", pszDocumentName);
}

DxeFilmClip* DXEditorHelper::GetMovie()
{
	if(!GetFileOpen())
		return NULL;
	DxeFilmClip* movie = (DxeFilmClip*)GetDocument()->FindKey("activeClip");
	if(!movie)
		return NULL;
	return movie;
}

DxeFilmClip* DXEditorHelper::GetShotAtCurrentTime()
{
	DxeFilmClip* movie = GetMovie();
	if(!movie)
		return NULL;
	DxeTrackGroup* subClipTrackGroup = (DxeTrackGroup*)movie->GetSubClipTrackGroup();
	if(!subClipTrackGroup)
		return NULL;
	KvDxElementArray* subClipTrackGroupTracks = subClipTrackGroup->GetTracks();
	if (!subClipTrackGroupTracks)
		return NULL;
	for (int i = 0; i < subClipTrackGroupTracks->GetSize(); i++)
	{
		DxElement* currentTrackElem = subClipTrackGroupTracks->GetElement(i);
		if (currentTrackElem == NULL)
			continue;
		DxeTrack* currentTrack = (DxeTrack*)currentTrackElem;
		if (currentTrack != NULL)
		{
			for (int j = 0; j < subClipTrackGroupTracks->GetSize(); j++)
			{
				DxeFilmClip* currentShot = (DxeFilmClip*)currentTrack->GetChildren()->GetElement(j);
				if (currentShot != NULL)
				{
					DxeTimeFrame* timeFrame = currentShot->GetTimeFrame();
					if (timeFrame == NULL)
						continue;
					float flStart = timeFrame->GetStart();
					float flDuration = timeFrame->GetDuration();
					float flPlayhead = GetPlayhead();
					if (flPlayhead >= flStart && flPlayhead <= flStart + flDuration)
					{
						return currentShot;
					}
				}
			}
		}
	}
	return NULL;
}

DxeCamera* DXEditorHelper::GetCurrentCamera()
{
	DxeFilmClip* shot = GetShotAtCurrentTime();
	if(!shot)
		return NULL;
	const char* activeCamera = shot->GetActiveCamera();
	if(!activeCamera)
		return NULL;
	DxeDag* scene = (DxeDag*)shot->GetScene();
	if (!scene)
		return NULL;
	DxeCamera* camera = (DxeCamera*)RecursiveFindDag(scene, activeCamera);
	if (!camera)
		return NULL;
	return camera;
}

DxeDag* DXEditorHelper::RecursiveFindDag(DxeDag* parent, const char* name)
{
	if (parent == NULL)
		return NULL;
	if (Q_strcmp(parent->GetElementName(), name) == 0)
		return parent;
	for (int i = 0; i < parent->GetChildren()->GetSize(); i++)
	{
		DxeDag* child = (DxeDag*)parent->GetChildren()->GetElement(i);
		if (child == NULL)
			continue;
		DxeDag* found = RecursiveFindDag(child, name);
		if (found != NULL)
			return found;
	}
	return NULL;
}

void DXEditorHelper::RecursiveRenderCurrentScene(DxeDag* parent)
{
	if (parent == NULL)
		return;
	for (int i = 0; i < parent->GetChildren()->GetSize(); i++)
	{
		DxeDag* child = (DxeDag*)parent->GetChildren()->GetElement(i);
		if (child == NULL)
			continue;
		// Check type of child
		if (Q_strcmp(child->GetTypeName(), "DxeGameModel") == 0)
		{
			DxeGameModel* gameModel = (DxeGameModel*)child;
			gameModel->UpdatePuppet();
		}
		RecursiveRenderCurrentScene(child);
	}
}

void DXEditorHelper::RecursiveReleaseSceneHierarchy(DxeDag* parent)
{
	if (parent == NULL)
		return;
	for (int i = 0; i < parent->GetChildren()->GetSize(); i++)
	{
		DxeDag* child = (DxeDag*)parent->GetChildren()->GetElement(i);
		if (child == NULL)
			continue;
		// Check type of child
		if (Q_strcmp(child->GetTypeName(), "DxeGameModel") == 0)
		{
			DxeGameModel* gameModel = (DxeGameModel*)child;
			gameModel->ReleasePuppet();
		}
		RecursiveReleaseSceneHierarchy(child);
	}
}

void DXEditorHelper::CheckReleaseModel()
{
	// Check to see if models are still in use when the timeline is not at the shot
	// if not, release them
	// Get current time
	float flPlayhead = GetPlayhead();
	// Get movie
	DxeFilmClip* movie = GetMovie();
	if (movie == NULL)
		return;
	// Get subclip track group
	DxeTrackGroup* subClipTrackGroup = (DxeTrackGroup*)movie->GetSubClipTrackGroup();
	if (subClipTrackGroup == NULL)
		return;
	// Loop through each shot
	for (int i = 0; i < subClipTrackGroup->GetTracks()->GetSize(); i++)
	{
		DxeTrack* currentTrack = (DxeTrack*)subClipTrackGroup->GetTracks()->GetElement(i);
		if (currentTrack == NULL)
			continue;
		for (int j = 0; j < subClipTrackGroup->GetTracks()->GetSize(); j++)
		{
			DxeFilmClip* currentShot = (DxeFilmClip*)currentTrack->GetChildren()->GetElement(j);
			if (currentShot == NULL)
				continue;
			DxeTimeFrame* timeFrame = currentShot->GetTimeFrame();
			if (timeFrame == NULL)
				continue;
			float flStart = timeFrame->GetStart();
			float flDuration = timeFrame->GetDuration();
			if (flPlayhead < flStart || flPlayhead > flStart + flDuration)
			{
				// Get scene
				DxeDag* scene = (DxeDag*)currentShot->GetScene();
				if (scene == NULL)
					continue;
				// Release models
				RecursiveReleaseSceneHierarchy(scene);
			}
		}
	}
}

void DXEditorHelper::PostRender()
{
	if(!engine->IsInGame())
		return;
	CMatRenderContextPtr renderContext(g_pMaterialSystem);

	if(!GetFileOpen())
		return;

	if(IsWorkCameraActive())
	{
		DxeCamera* currentCamera = GetCurrentCamera();
		if (currentCamera != NULL)
		{
			DxeTransform* cameraTransform = currentCamera->GetTransform();
			if (cameraTransform != NULL)
			{
				Vector vecPosition = cameraTransform->GetPosition()->GetVector();
				Quaternion rOrientation = cameraTransform->GetOrientation()->GetQuaternion();
				QAngle angOrientation;
				QuaternionAngles(rOrientation, angOrientation);
				Vector vecForward, vecRight, vecUp;
				AngleVectors(angOrientation, &vecForward, &vecRight, &vecUp);
				float flFieldOfView = currentCamera->GetFieldOfView();
				float flZNear = currentCamera->GetNearClip();
				float flZFar = currentCamera->GetFarClip();

				if(!DXIsLayoff() || (DXIsLayoff() && !(GetLayoffFlags() & DX_LAYOFF_NO_FRUSTRUM)))
				{
					int nColRed = 255;
					int nColGreen = 255;
					int nColBlue = 255;
					bool bNoDepthTest = false;
					// TODO: delta time? time since last frame?
					float flDuration = 0.1f;
					// Draw frustum from znear to zfar using fov and the aspect ratio of the viewport
					// So it stretches from one corner of the viewport (near) to the other (far)
					float flAspectRatio = (float)DirectorsCutGameSystem().GetViewportWidth() / (float)DirectorsCutGameSystem().GetViewportHeight();
					// Rotate aspect ratio by 90 degrees (quick fix because it's sideways)
					flAspectRatio = 1 / flAspectRatio;
					// Apply aspect ratio
					Vector vecTopLeft = vecPosition + vecForward * flZNear + vecUp * tan(flFieldOfView * M_PI / 360) * flZNear * flAspectRatio - vecRight * tan(flFieldOfView * M_PI / 360) * flZNear;
					Vector vecTopRight = vecPosition + vecForward * flZNear + vecUp * tan(flFieldOfView * M_PI / 360) * flZNear * flAspectRatio + vecRight * tan(flFieldOfView * M_PI / 360) * flZNear;
					Vector vecBottomLeft = vecPosition + vecForward * flZNear - vecUp * tan(flFieldOfView * M_PI / 360) * flZNear * flAspectRatio - vecRight * tan(flFieldOfView * M_PI / 360) * flZNear;
					Vector vecBottomRight = vecPosition + vecForward * flZNear - vecUp * tan(flFieldOfView * M_PI / 360) * flZNear * flAspectRatio + vecRight * tan(flFieldOfView * M_PI / 360) * flZNear;
					Vector vecTopLeftFar = vecPosition + vecForward * flZFar + vecUp * tan(flFieldOfView * M_PI / 360) * flZFar * flAspectRatio - vecRight * tan(flFieldOfView * M_PI / 360) * flZFar;
					Vector vecTopRightFar = vecPosition + vecForward * flZFar + vecUp * tan(flFieldOfView * M_PI / 360) * flZFar * flAspectRatio + vecRight * tan(flFieldOfView * M_PI / 360) * flZFar;
					Vector vecBottomLeftFar = vecPosition + vecForward * flZFar - vecUp * tan(flFieldOfView * M_PI / 360) * flZFar * flAspectRatio - vecRight * tan(flFieldOfView * M_PI / 360) * flZFar;
					Vector vecBottomRightFar = vecPosition + vecForward * flZFar - vecUp * tan(flFieldOfView * M_PI / 360) * flZFar * flAspectRatio + vecRight * tan(flFieldOfView * M_PI / 360) * flZFar;
					debugoverlay->AddLineOverlay(vecTopLeft, vecTopRight, nColRed, nColGreen, nColBlue, bNoDepthTest, flDuration);
					debugoverlay->AddLineOverlay(vecTopRight, vecBottomRight, nColRed, nColGreen, nColBlue, bNoDepthTest, flDuration);
					debugoverlay->AddLineOverlay(vecBottomRight, vecBottomLeft, nColRed, nColGreen, nColBlue, bNoDepthTest, flDuration);
					debugoverlay->AddLineOverlay(vecBottomLeft, vecTopLeft, nColRed, nColGreen, nColBlue, bNoDepthTest, flDuration);
					debugoverlay->AddLineOverlay(vecTopLeftFar, vecTopRightFar, nColRed, nColGreen, nColBlue, bNoDepthTest, flDuration);
					debugoverlay->AddLineOverlay(vecTopRightFar, vecBottomRightFar, nColRed, nColGreen, nColBlue, bNoDepthTest, flDuration);
					debugoverlay->AddLineOverlay(vecBottomRightFar, vecBottomLeftFar, nColRed, nColGreen, nColBlue, bNoDepthTest, flDuration);
					debugoverlay->AddLineOverlay(vecBottomLeftFar, vecTopLeftFar, nColRed, nColGreen, nColBlue, bNoDepthTest, flDuration);
					debugoverlay->AddLineOverlay(vecTopLeft, vecTopLeftFar, nColRed, nColGreen, nColBlue, bNoDepthTest, flDuration);
					debugoverlay->AddLineOverlay(vecTopRight, vecTopRightFar, nColRed, nColGreen, nColBlue, bNoDepthTest, flDuration);
					debugoverlay->AddLineOverlay(vecBottomRight, vecBottomRightFar, nColRed, nColGreen, nColBlue, bNoDepthTest, flDuration);
					debugoverlay->AddLineOverlay(vecBottomLeft, vecBottomLeftFar, nColRed, nColGreen, nColBlue, bNoDepthTest, flDuration);
					// Draw lines from origin to near
					debugoverlay->AddLineOverlay(vecPosition, vecTopLeft, nColRed, nColGreen, nColBlue, bNoDepthTest, flDuration);
					debugoverlay->AddLineOverlay(vecPosition, vecTopRight, nColRed, nColGreen, nColBlue, bNoDepthTest, flDuration);
					debugoverlay->AddLineOverlay(vecPosition, vecBottomRight, nColRed, nColGreen, nColBlue, bNoDepthTest, flDuration);
					debugoverlay->AddLineOverlay(vecPosition, vecBottomLeft, nColRed, nColGreen, nColBlue, bNoDepthTest, flDuration);
				}

				if(!DXIsLayoff() || (DXIsLayoff() && !(GetLayoffFlags() & DX_LAYOFF_NO_SPRITES)))
				{
					// Draw a sprite at the camera's position
					const char* spriteName = "sprites/light_glow02_add_noz";
					IMaterial *pMat = materials->FindMaterial( spriteName, TEXTURE_GROUP_CLIENT_EFFECTS );
					color32 spriteColor = { 255, 255, 255, 255 };
					renderContext->Bind( pMat, NULL );
					DrawSprite( vecPosition, 64, 64, spriteColor );
				}
			}
		}
	}
	DxeFilmClip* shot = GetShotAtCurrentTime();
	if(shot != NULL)
	{
		DxeDag* scene = (DxeDag*)shot->GetScene();
		if(scene != NULL)
		{
			RecursiveRenderCurrentScene(scene);
		}
	}
}

void DXEditorHelper::Update( float ft )
{
	if(NeedsUpdate(DX_NEEDS_UPDATE_TIMELINE))
	{
		DxElement* pRoot = GetDocument();
		if( pRoot != NULL )
		{
			DxElement* pSettings = (DxElement*)pRoot->FindKey("settings");
			if( pSettings != NULL )
			{
				DxElement* pRenderSettings = (DxElement*)pSettings->FindKey("renderSettings");
				if( pRenderSettings != NULL )
				{
					float newFps = pRenderSettings->GetFloat("frameRate");
					if(newFps > 0)
						fps = newFps;
				}
			}
			if(!IsWorkCameraActive())
			{
				DxeCamera* pCamera = GetCurrentCamera();
				if(pCamera != NULL)
				{
					SetSceneCameraFOV(pCamera->GetFieldOfView());
					DxeTransform* transform = pCamera->GetTransform();
					if (transform != NULL)
					{
						Vector vecPosition = transform->GetPosition()->GetVector();
						Quaternion qOrientation = transform->GetOrientation()->GetQuaternion();
						QAngle angOrientation;
						QuaternionAngles(qOrientation, angOrientation);
						SetSceneCameraOrigin(vecPosition);
						SetSceneCameraAngles(angOrientation);
					}
				}
			}
		}
		SetNeedsUpdate(false, DX_NEEDS_UPDATE_TIMELINE);
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
			DxeFilmClip* shot = GetShotAtCurrentTime();
			if (shot != NULL)
			{
				DxeTimeFrame* timeFrame = shot->GetTimeFrame();
				if (timeFrame != NULL)
				{
					float flStart = timeFrame->GetStart();
					float flDuration = timeFrame->GetDuration();
					if (vgui::input()->IsKeyDown(KEY_UP))
						SetPlayhead(flStart);
					else
						SetPlayhead(flStart + flDuration);
				}
			}
			bDebounce = true;
		}
	} else {
		// TODO: better method of debounce
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
