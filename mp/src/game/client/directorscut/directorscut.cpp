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
	SetDefLessFunc(m_pModels);
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

void DXEditorHelper::LoadDocument( const char* pszDocumentName )
{
	//DECLARE_DMX_CONTEXT_NODECOMMIT();
	CloseDocument();
	CDmxElement* document = (CDmxElement*)DMXAlloc( 1000000000 );

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

void DXEditorHelper::SetPlayhead( float fPlayhead )
{
	if(m_fPlayhead == fPlayhead)
		return;
	SetAllNeedsUpdate(true);
	m_fPlayhead = fPlayhead;
}

void DXEditorHelper::LoadKeyValuesDocument( const char* pszDocumentName )
{
	CloseKeyValuesDocument();
	DxElement* document = new DxElement("session");

	// Mark timestamp so we can document how long it takes to load
	double flStartTime = Plat_FloatTime();

	if (document->LoadFromFile(g_pFullFileSystem, pszDocumentName, NULL))
	{
		SetKeyValuesDocument(document);
		SetFileOpen(true);
		m_pszLoadedDocumentName = pszDocumentName;

		// Get timestamp and print how long it took to load
		double flEndTime = Plat_FloatTime();
		double flTimeTaken = flEndTime - flStartTime;
		Msg("Finished loading keyvalues session in %f seconds\n", flTimeTaken);
	}
	else
		Warning("Could not read keyvalues file %s\n", pszDocumentName);
	
	SetAllNeedsUpdate(true);
}

void DXEditorHelper::NewKeyValuesDocument()
{
	CloseKeyValuesDocument();

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
	shot->GetTimeFrame()->SetDuration(60.0f);
	filmTrack->GetChildren()->AddElement(shot);
	subClipTrackGroup->GetTracks()->AddElement(filmTrack);
	movie->AddSubKey(subClipTrackGroup);
    document->AddSubKey(movie);
    document->AddSubKey(new KvDxElementArray("miscBin"));
    document->AddSubKey(new KvDxElementArray("clipBin"));
    document->AddSubKey(new DxElement("settings"));

	SetKeyValuesDocument(document);
	SetFileOpen(true);
	m_pszLoadedDocumentName = NULL;
	SetAllNeedsUpdate(true);
}

void DXEditorHelper::SaveKeyValuesDocument()
{
	if(m_pszLoadedDocumentName)
		SaveKeyValuesDocument(m_pszLoadedDocumentName);
}

void DXEditorHelper::SaveKeyValuesDocument( const char* pszDocumentName )
{
	DxElement* document = GetKeyValuesDocument();
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

void DXEditorHelper::CloseKeyValuesDocument()
{
	DxElement* document = GetKeyValuesDocument();
	if(!document)
		return;
	document->deleteThis();
	SetKeyValuesDocument(NULL);
	SetFileOpen(false);
	m_pszLoadedDocumentName = NULL;
	SetAllNeedsUpdate(true);
}

DxeFilmClip* DXEditorHelper::GetMovie()
{
	if(!GetFileOpen())
		return NULL;
	DxeFilmClip* movie = (DxeFilmClip*)GetKeyValuesDocument()->FindKey("activeClip");
	if(!movie)
		return NULL;
	return movie;
}

DxeFilmClip* DXEditorHelper::GetShotAtCurrentTime()
{
	DxeFilmClip* movie = GetMovie();
	if(!movie)
		return NULL;
	return NULL;
	//return movie->GetShotAtTime(GetPlayhead());
}

DXDagType GetDagType( const char* pszDagType )
{
	if (Q_strcmp(pszDagType, "DmeCamera") == 0)
		return DXDagType::DX_DME_CAMERA;
	if (Q_strcmp(pszDagType, "DmeGameModel") == 0)
		return DXDagType::DX_DME_GAMEMODEL;
	if (Q_strcmp(pszDagType, "DmeGameParticleSystem") == 0)
		return DXDagType::DX_DME_GAMEPARTICLESYSTEM;
	if (Q_strcmp(pszDagType, "DmeGamePortal") == 0)
		return DXDagType::DX_DME_GAMEPORTAL;
	if (Q_strcmp(pszDagType, "DmeGameSprite") == 0)
		return DXDagType::DX_DME_GAMESPRITE;
	if (Q_strcmp(pszDagType, "DmeGameTempEnt") == 0)
		return DXDagType::DX_DME_GAMETEMPENT;
	if (Q_strcmp(pszDagType, "DmeJoint") == 0)
		return DXDagType::DX_DME_JOINT;
	if (Q_strcmp(pszDagType, "DmeLight") == 0)
		return DXDagType::DX_DME_LIGHT;
	if (Q_strcmp(pszDagType, "DmeAmbientLight") == 0)
		return DXDagType::DX_DME_AMBIENTLIGHT;
	if (Q_strcmp(pszDagType, "DmeDirectionalLight") == 0)
		return DXDagType::DX_DME_DIRECTIONALLIGHT;
	if (Q_strcmp(pszDagType, "DmePointLight") == 0)
		return DXDagType::DX_DME_POINTLIGHT;
	if (Q_strcmp(pszDagType, "DmeSpotLight") == 0)
		return DXDagType::DX_DME_SPOTLIGHT;
	if (Q_strcmp(pszDagType, "DmeProjectedLight") == 0)
		return DXDagType::DX_DME_PROJECTEDLIGHT;
	if (Q_strcmp(pszDagType, "DmeModel") == 0)
		return DXDagType::DX_DME_MODEL;
	if (Q_strcmp(pszDagType, "DmeParticleSystem") == 0)
		return DXDagType::DX_DME_PARTICLESYSTEM;
	if (Q_strcmp(pszDagType, "DmeRig") == 0)
		return DXDagType::DX_DME_RIG;
	if (Q_strcmp(pszDagType, "DmeRigHandle") == 0)
		return DXDagType::DX_DME_RIGHANDLE;
	return DXDagType::DX_DME_DAG;
}

void DXEditorHelper::RecursiveBuildScene(DXDag* dagParent, CDmxElement* pElementParent)
{
	if (!pElementParent)
		return;

	// Get children
	const CUtlVector<CDmxElement*>& pChildren = pElementParent->GetArray<CDmxElement*>("children");
	if (pChildren.Count() == 0)
		return;

	// Iterate through children
	for (int i = 0; i < pChildren.Count(); i++)
	{
		CDmxElement* pChild = pChildren[i];
		if (!pChild)
			continue;

		// Get dag type
		const char* pszDagType = pChild->GetTypeString();
		if (!pszDagType)
			continue;
		DXDagType dagType = GetDagType(pszDagType);

		// Get extra KV
		KeyValues* kvExtra = new KeyValues("data");

		// Set ID
		DmObjectId_t id = pChild->GetId();
		char pszId[64];
		Q_snprintf(pszId, sizeof(pszId), "%u", id.m_Value);
		kvExtra->SetString("_elementid", pszId);

		// Set name
		const char* pszName = pChild->GetValueString("name");
		if (pszName)
			kvExtra->SetString("name", pszName);

		switch(dagType)
		{
			case DX_DME_CAMERA:
			{
				// These KVs are used to draw the camera frustum
				float strFieldOfView = pChild->GetValue<float>("fieldOfView");
				kvExtra->SetFloat("fieldOfView", strFieldOfView);
				float strZNear = pChild->GetValue<float>("znear");
				kvExtra->SetFloat("znear", strZNear);
				float strZFar = pChild->GetValue<float>("zfar");
				kvExtra->SetFloat("zfar", strZFar);
				break;
			}
			case DX_DME_GAMEMODEL:
			{
				// Load model
				const char* pszModelName = pChild->GetValueString("modelName");
				if (pszModelName)
				{
					kvExtra->SetString("modelName", pszModelName);
				}
				KeyValues* kvBones = new KeyValues("bones");
				// Get bones
				const CUtlVector<CDmxElement*>& pBones = pChild->GetArray<CDmxElement*>("bones");
				if (pBones.Count() > 0)
				{
					for (int i = 0; i < pBones.Count(); i++)
					{
						// name the bone by its index
						const char* pszBoneName = VarArgs("bone_%i", i);
						KeyValues* kvBone = new KeyValues(pszBoneName);
						kvBone->SetFloat("position_x", 0);
						kvBone->SetFloat("position_y", 0);
						kvBone->SetFloat("position_z", 0);
						kvBone->SetFloat("orientation_x", 0);
						kvBone->SetFloat("orientation_y", 0);
						kvBone->SetFloat("orientation_z", 0);
						kvBone->SetFloat("orientation_w", 1);
						kvBone->SetFloat("scale_x", 1);
						kvBone->SetFloat("scale_y", 1);
						kvBone->SetFloat("scale_z", 1);
						kvBones->AddSubKey(kvBone);
						CDmxElement* pBone = pBones[i];
						if (!pBone)
							continue;
						Vector vecPosition = pBone->GetValue<Vector>("position");
						Quaternion angOrientation = pBone->GetValue<Quaternion>("orientation");
						float flScale = pBone->GetValue<float>("scale", 1);
						float flScaleX = pBone->GetValue<float>("scale_x", 0);
						float flScaleY = pBone->GetValue<float>("scale_y", 0);
						float flScaleZ = pBone->GetValue<float>("scale_z", 0);
						Vector vecScale;
						if (flScaleX == 0 && flScaleY == 0 && flScaleZ == 0)
							vecScale.Init(flScale, flScale, flScale);
						else
							vecScale.Init(flScaleX, flScaleY, flScaleZ);
						kvBone->SetFloat("position_x", vecPosition.x);
						kvBone->SetFloat("position_y", vecPosition.y);
						kvBone->SetFloat("position_z", vecPosition.z);
						kvBone->SetFloat("orientation_x", angOrientation.x);
						kvBone->SetFloat("orientation_y", angOrientation.y);
						kvBone->SetFloat("orientation_z", angOrientation.z);
						kvBone->SetFloat("orientation_w", angOrientation.w);
						kvBone->SetFloat("scale_x", vecScale.x);
						kvBone->SetFloat("scale_y", vecScale.y);
						kvBone->SetFloat("scale_z", vecScale.z);
					}
				}
				kvExtra->AddSubKey(kvBones);
				kvExtra->SetInt("_numbones", pBones.Count());
				break;
			}
		}

		// Get transform
		CDmxElement* pTransform = pChild->GetValue<CDmxElement*>("transform");
		if (!pTransform)
			continue;
		Vector vecPosition = pTransform->GetValue<Vector>("position");
		Quaternion angOrientation = pTransform->GetValue<Quaternion>("orientation");
		float flScale = pTransform->GetValue<float>("scale", 1);
		float flScaleX = pTransform->GetValue<float>("scale_x", 0);
		float flScaleY = pTransform->GetValue<float>("scale_y", 0);
		float flScaleZ = pTransform->GetValue<float>("scale_z", 0);
		Vector vecScale;
		if (flScaleX == 0 && flScaleY == 0 && flScaleZ == 0)
			vecScale.Init(flScale, flScale, flScale);
		else
			vecScale.Init(flScaleX, flScaleY, flScaleZ);

		// Offset
		Vector vecPositionOffset = dagParent->GetOrigin() + vecPosition;
		QAngle angEuler;
		QuaternionAngles(angOrientation, angEuler);
		QAngle angOrientationOffset = dagParent->GetAngles() + angEuler;
		Vector vecScaleOffset = dagParent->GetScale() * vecScale;

		// Create dag
		DXDag* dag = new DXDag( dagType, vecPositionOffset, angOrientationOffset, vecScaleOffset, kvExtra );
		dagParent->AddChild(dag);

		// Recurse
		RecursiveBuildScene(dag, pChild);
	}
}

void DXEditorHelper::RecursiveDrawScene( DXDag* dagParent, CMatRenderContextPtr& renderContext)
{
	// Draw scene
	switch (dagParent->GetDagType())
	{
		case DX_DME_CAMERA:
		{
			if(DXIsLayoff() && DXGetLayoffFlags() & DX_LAYOFF_NO_GIZMOS) //DX_LAYOFF_NO_SPRITES
				break;
			// Draw a sprite at the camera's position
			//const char* spriteName = "sprites/light_glow02_add_noz";
			//IMaterial *pMat = materials->FindMaterial( spriteName, TEXTURE_GROUP_CLIENT_EFFECTS );
			//color32 spriteColor = { 255, 255, 255, 255 };
			//renderContext->Bind( pMat, NULL );
			//DrawSprite( dagParent->GetOrigin(), 64, 64, spriteColor );
			// Draw camera frustum
			KeyValues* kvExtra = dagParent->GetKeyValues();
			if (kvExtra != nullptr)
			{
				// virtual void AddLineOverlay(const Vector& origin, const Vector& dest, int r, int g, int b,bool noDepthTest, float duration) = 0;
				float flFieldOfView = kvExtra->GetFloat("fieldOfView");
				float flZNear = kvExtra->GetFloat("znear");
				float flZFar = kvExtra->GetFloat("zfar");
				int nColRed = 255;
				int nColGreen = 255;
				int nColBlue = 255;
				bool bNoDepthTest = false;
				// TODO: delta time? time since last frame?
				float flDuration = 0.1f;
				Vector vecForward, vecRight, vecUp;
				AngleVectors(dagParent->GetAngles(), &vecForward, &vecRight, &vecUp);
				// Draw frustum from znear to zfar using fov and the aspect ratio of the viewport
				// So it stretches from one corner of the viewport (near) to the other (far)
				float flAspectRatio = (float)DirectorsCutGameSystem().GetViewportWidth() / (float)DirectorsCutGameSystem().GetViewportHeight();
				// Rotate aspect ratio by 90 degrees (quick fix because it's sideways)
				flAspectRatio = 1 / flAspectRatio;
				Vector vecOrigin = dagParent->GetOrigin();
				//Vector vecTopLeft = vecOrigin + vecForward * flZNear + vecUp * tan(flFieldOfView * M_PI / 360) * flZNear - vecRight * tan(flFieldOfView * M_PI / 360) * flZNear;
				//Vector vecTopRight = vecOrigin + vecForward * flZNear + vecUp * tan(flFieldOfView * M_PI / 360) * flZNear + vecRight * tan(flFieldOfView * M_PI / 360) * flZNear;
				//Vector vecBottomLeft = vecOrigin + vecForward * flZNear - vecUp * tan(flFieldOfView * M_PI / 360) * flZNear - vecRight * tan(flFieldOfView * M_PI / 360) * flZNear;
				//Vector vecBottomRight = vecOrigin + vecForward * flZNear - vecUp * tan(flFieldOfView * M_PI / 360) * flZNear + vecRight * tan(flFieldOfView * M_PI / 360) * flZNear;
				//Vector vecTopLeftFar = vecOrigin + vecForward * flZFar + vecUp * tan(flFieldOfView * M_PI / 360) * flZFar - vecRight * tan(flFieldOfView * M_PI / 360) * flZFar;
				//Vector vecTopRightFar = vecOrigin + vecForward * flZFar + vecUp * tan(flFieldOfView * M_PI / 360) * flZFar + vecRight * tan(flFieldOfView * M_PI / 360) * flZFar;
				//Vector vecBottomLeftFar = vecOrigin + vecForward * flZFar - vecUp * tan(flFieldOfView * M_PI / 360) * flZFar - vecRight * tan(flFieldOfView * M_PI / 360) * flZFar;
				//Vector vecBottomRightFar = vecOrigin + vecForward * flZFar - vecUp * tan(flFieldOfView * M_PI / 360) * flZFar + vecRight * tan(flFieldOfView * M_PI / 360) * flZFar;
				// Apply aspect ratio
				Vector vecTopLeft = vecOrigin + vecForward * flZNear + vecUp * tan(flFieldOfView * M_PI / 360) * flZNear * flAspectRatio - vecRight * tan(flFieldOfView * M_PI / 360) * flZNear;
				Vector vecTopRight = vecOrigin + vecForward * flZNear + vecUp * tan(flFieldOfView * M_PI / 360) * flZNear * flAspectRatio + vecRight * tan(flFieldOfView * M_PI / 360) * flZNear;
				Vector vecBottomLeft = vecOrigin + vecForward * flZNear - vecUp * tan(flFieldOfView * M_PI / 360) * flZNear * flAspectRatio - vecRight * tan(flFieldOfView * M_PI / 360) * flZNear;
				Vector vecBottomRight = vecOrigin + vecForward * flZNear - vecUp * tan(flFieldOfView * M_PI / 360) * flZNear * flAspectRatio + vecRight * tan(flFieldOfView * M_PI / 360) * flZNear;
				Vector vecTopLeftFar = vecOrigin + vecForward * flZFar + vecUp * tan(flFieldOfView * M_PI / 360) * flZFar * flAspectRatio - vecRight * tan(flFieldOfView * M_PI / 360) * flZFar;
				Vector vecTopRightFar = vecOrigin + vecForward * flZFar + vecUp * tan(flFieldOfView * M_PI / 360) * flZFar * flAspectRatio + vecRight * tan(flFieldOfView * M_PI / 360) * flZFar;
				Vector vecBottomLeftFar = vecOrigin + vecForward * flZFar - vecUp * tan(flFieldOfView * M_PI / 360) * flZFar * flAspectRatio - vecRight * tan(flFieldOfView * M_PI / 360) * flZFar;
				Vector vecBottomRightFar = vecOrigin + vecForward * flZFar - vecUp * tan(flFieldOfView * M_PI / 360) * flZFar * flAspectRatio + vecRight * tan(flFieldOfView * M_PI / 360) * flZFar;
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
				debugoverlay->AddLineOverlay(vecOrigin, vecTopLeft, nColRed, nColGreen, nColBlue, bNoDepthTest, flDuration);
				debugoverlay->AddLineOverlay(vecOrigin, vecTopRight, nColRed, nColGreen, nColBlue, bNoDepthTest, flDuration);
				debugoverlay->AddLineOverlay(vecOrigin, vecBottomRight, nColRed, nColGreen, nColBlue, bNoDepthTest, flDuration);
				debugoverlay->AddLineOverlay(vecOrigin, vecBottomLeft, nColRed, nColGreen, nColBlue, bNoDepthTest, flDuration);
			}
			break;
		}
		case DX_DME_GAMEMODEL:
		{
			// Draw model
			KeyValues* kvExtra = dagParent->GetKeyValues();
			if (kvExtra != nullptr)
			{
				// we can't render a new model every frame
				// so m_pModels uses the element id as the key
				const char* nElementId = kvExtra->GetString("_elementid");
				int found = m_pModels.Find(nElementId);
				CDirectorsCutPuppet* pModelEntity = nullptr;

				if (!m_pModels.IsValidIndex(found))
				{
					// print name
					const char* pszName = kvExtra->GetString("name");
					Msg("Model name: %s\n", pszName);
					const char* pszModelName = kvExtra->GetString("modelName");
					if (pszModelName != nullptr)
					{
						// Load model
						model_t* pModel = LoadModel(pszModelName);
						if (pModel != nullptr)
						{
							pModelEntity = new CDirectorsCutPuppet();
							pModelEntity->SetModelPointer(pModel);
							m_pModels.Insert(nElementId, pModelEntity);
						}
					}
				}
				else
				{
					pModelEntity = m_pModels.Element(found);
				}

				if (pModelEntity != nullptr)
				{
					sModels.AddToTail(nElementId);
					pModelEntity->SetAbsOrigin(dagParent->GetOrigin());
					pModelEntity->SetAbsAngles(dagParent->GetAngles());
					int boneCount = kvExtra->GetInt("_numbones");
					if(boneCount > MAXSTUDIOBONES)
						boneCount = MAXSTUDIOBONES;
					KeyValues* kvBones = kvExtra->FindKey("bones");
					if(kvBones != nullptr)
					{
						for (int i = 0; i < boneCount; i++)
						{
							const char* pszBoneName = VarArgs("bone_%i", i);
							KeyValues* kvBone = kvBones->FindKey(pszBoneName);
							if (kvBone != nullptr)
							{
								Vector newPos(kvBone->GetFloat("position_x"), kvBone->GetFloat("position_y"), kvBone->GetFloat("position_z"));
								Quaternion newQuat(kvBone->GetFloat("orientation_x"), kvBone->GetFloat("orientation_y"), kvBone->GetFloat("orientation_z"), kvBone->GetFloat("orientation_w"));
								QAngle newAng;
								QuaternionAngles(newQuat, newAng);
								//Vector vecScale(kvBone->GetFloat("scale_x"), kvBone->GetFloat("scale_y"), kvBone->GetFloat("scale_z"));
								pModelEntity->PushAllowBoneAccess(true, true, "DirectorsCut");
								pModelEntity->PoseBones(i, newPos, newAng);
								pModelEntity->PopBoneAccess("DirectorsCut");
							}
						}
					}
				}

				// TODO: bones (just model for now)
				// bones -> element_array of DmeTransform (position, orientation)
				// bones are in the same order as the model's bones
			}
			break;
		}
	}
	// Draw children
	const CUtlVector<DXDag*>& pChildren = dagParent->GetChildren();
	for (int i = 0; i < pChildren.Count(); i++)
	{
		DXDag* pChild = pChildren[i];
		if (!pChild)
			continue;
		RecursiveDrawScene(pChild, renderContext);
	}
}

void DXEditorHelper::PostRender()
{
	if(!engine->IsInGame())
		return;
	CMatRenderContextPtr renderContext(g_pMaterialSystem);
	if(m_Dag != NULL)
	{
		// Draw scene
		RecursiveDrawScene(m_Dag, renderContext);
		// Trim models (if they are not in the scene)
		for (unsigned int i = 0; i < m_pModels.Count(); i++)
		{
			const char* nElementId = m_pModels.Key(i);
			int found = sModels.Find(nElementId);
			if (found == -1)
			{
				CDirectorsCutPuppet* pModelEntity = m_pModels.Element(i);
				if (pModelEntity != nullptr)
				{
					delete pModelEntity;
					m_pModels.RemoveAt(i);
				}
			}
		}
	}
}

void DXEditorHelper::Update( float ft )
{
	if(NeedsUpdate(DX_NEEDS_UPDATE_TIMELINE))
	{
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
									// Track groups
									const CUtlVector<CDmxElement*>& pTrackGroups = pChild->GetArray<CDmxElement*>( "trackGroups" );
									int count = pTrackGroups.Count();
									if(count != 0)
									{
										for (int i = 0; i < pTrackGroups.Count(); i++)
										{
											CDmxElement* pTrackGroup = pTrackGroups[i];
											if( pTrackGroup != NULL )
											{
												const CUtlVector<CDmxElement*>& pTracks = pTrackGroup->GetArray<CDmxElement*>( "tracks" );
												if( pTracks.Count() != 0)
												{
													for (int j = 0; j < pTracks.Count(); j++)
													{
														CDmxElement* pTrack = pTracks[j];
														if( pTrack != NULL )
														{
															const CUtlVector<CDmxElement*>& pChildren = pTrack->GetArray<CDmxElement*>( "children" );
															if( pChildren.Count() != 0)
															{
																for (int k = 0; k < pChildren.Count(); k++)
																{
																	CDmxElement* pChild = pChildren[k];
																	if( pChild != NULL )
																	{
																		CDmxElement* pTimeFrame = pChild->GetValue<CDmxElement*>( "timeFrame" );
																		if( pTimeFrame != NULL )
																		{
																			float flStart = pTimeFrame->GetValue<float>( "start" );
																			float flPlayhead = GetPlayhead();
																			float flCurrentTime = flPlayhead - flStart;
																			// Channels might not exist
																			// check for "channels" attribute
																			if( pChild->HasAttribute( "channels" ) )
																			{
																				const CUtlVector<CDmxElement*>& pChannels = pChild->GetArray<CDmxElement*>( "channels" );
																				if( pChannels.Count() != 0)
																				{
																					for (int l = 0; l < pChannels.Count(); l++)
																					{
																						const char* fromAttribute = pChannels[l]->GetValueString( "fromAttribute" );
																						char* fromAttributeCopy = new char[strlen(fromAttribute) + 1];
																						// remove "value" and camelCase (valuePosition -> position)
																						// after removing "value" then make first letter lowercase
																						if( fromAttribute != NULL )
																						{
																							if( Q_strstr( fromAttribute, "value" ) != NULL )
																							{
																								// write to fromAttributeCopy
																								int i = 0;
																								int j = 0;
																								while( fromAttribute[i] != '\0' )
																								{
																									if( fromAttribute[i] == 'v' && fromAttribute[i + 1] == 'a' && fromAttribute[i + 2] == 'l' && fromAttribute[i + 3] == 'u' && fromAttribute[i + 4] == 'e' )
																									{
																										i += 5;
																										fromAttributeCopy[j] = fromAttribute[i];
																										j++;
																									}
																									else
																									{
																										fromAttributeCopy[j] = fromAttribute[i];
																										j++;
																									}
																									i++;
																								}
																								fromAttributeCopy[j] = '\0';
																								// make first letter lowercase
																								fromAttributeCopy[0] = tolower(fromAttributeCopy[0]);
																								fromAttribute = fromAttributeCopy;
																							}
																							CDmxElement* pChannel = pChannels[l];
																							if( pChannel != NULL )
																							{
																								CDmxElement* pToElement = pChannel->GetValue<CDmxElement*>( "toElement" );
																								if( pToElement != NULL )
																								{
																									CDmxElement* pLog = pChannel->GetValue<CDmxElement*>( "log" );
																									if( pLog != NULL )
																									{
																										const CUtlVector<CDmxElement*>& pLayers = pLog->GetArray<CDmxElement*>( "layers" );
																										if( pLayers.Count() != 0)
																										{
																											for (int l = 0; l < pLayers.Count(); l++)
																											{
																												const char* layerName = pLayers[l]->GetName();
																												const CUtlVector<float>& pTimes = pLayers[l]->GetArray<float>( "times" );
																												int timeIndex = -1;
																												for (int m = pTimes.Count() - 1; m >= 0; m--)
																												{
																													float thistime = pTimes[m];
																													if(flCurrentTime >= thistime)
																													{
																														timeIndex = m;
																														break;
																													}
																												}
																												if(timeIndex != -1)
																												{
																													// if layerName contains "vector3" or "quaternion" then make values into a vector3 or quaternion
																													if(Q_strstr(layerName, "vector3") != NULL)
																													{
																														const CUtlVector<Vector>& pValues = pLayers[l]->GetArray<Vector>( "values" );
																														if(pValues.Count() >= timeIndex)
																														{
																															Vector timedValue = pValues[timeIndex];
																															pToElement->SetValue<Vector>( fromAttribute, timedValue );
																														}
																													}
																													else if(Q_strstr(layerName, "quaternion") != NULL)
																													{
																														const CUtlVector<Quaternion>& pValues = pLayers[l]->GetArray<Quaternion>( "values" );
																														if(pValues.Count() >= timeIndex)
																														{
																															Quaternion timedValue = pValues[timeIndex];
																															pToElement->SetValue<Quaternion>( fromAttribute, timedValue );
																														}
																													}
																												}
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
									// Build scene view
									CDmxElement* pScene = pChild->GetValue<CDmxElement*>("scene");
									if (pScene != NULL)
									{
										Vector vecOrigin = pScene->GetValue<Vector>("origin");
										QAngle angAngles = pScene->GetValue<QAngle>("angles");
										float flScale = pScene->GetValue<float>("scale", 1);
										float flScaleX = pScene->GetValue<float>("scale_x", 0);
										float flScaleY = pScene->GetValue<float>("scale_y", 0);
										float flScaleZ = pScene->GetValue<float>("scale_z", 0);
										Vector vecScale;
										if (flScaleX == 0 && flScaleY == 0 && flScaleZ == 0)
											vecScale.Init(flScale, flScale, flScale);
										else
											vecScale.Init(flScaleX, flScaleY, flScaleZ);
										m_Dag = new DXDag(DX_DME_DAG, vecOrigin, angAngles, vecScale, new KeyValues("data"));
										RecursiveBuildScene(m_Dag, pScene);
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
