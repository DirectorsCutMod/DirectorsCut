//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Director's Cut system.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#ifndef DIRECTORSCUT_H
#define DIRECTORSCUT_H

#include "igamesystem.h"
#include "filesystem.h"
#include "dxproperties.h"
#include "materialsystem/imaterialsystem.h"
#include "entities/dxpuppet.h"
#include "data/dxelement.h"
#include "data/dxe_usersettings.h"
#include "data/dxe_filmclip.h"
#include "data/dxe_dag.h"
#include "data/dxe_camera.h"

IMaterial* GetPrimaryScreenMaterial();
KeyValues* GetPrimaryScreenKV();
ITexture* GetPrimaryViewportTex();
int GetPrimaryViewportTexID();
void AllocatePrimaryViewport();
void DeallocatePrimaryViewport();

#define DX_EDITOR_VERSION 1
#define DX_NEEDS_UPDATE_ELEMENTVIEWER 0
#define DX_NEEDS_UPDATE_ANIMSETEDITOR 1
#define DX_NEEDS_UPDATE_TIMELINE 2 // TODO: unused? will it ever be used?
#define DX_MAX_NEEDS_UPDATE 3

enum DXLayoffFlags
{
	DX_LAYOFF_ALL = 0,
	DX_LAYOFF_NO_SPRITES = 1,
	DX_LAYOFF_NO_GIZMOS = 2,
	DX_LAYOFF_NO_FRUSTRUM = 4,
	DX_LAYOFF_NONE = DX_LAYOFF_NO_SPRITES | DX_LAYOFF_NO_GIZMOS | DX_LAYOFF_NO_FRUSTRUM
};

class DXEditorHelper : public CAutoGameSystemPerFrame
{
public:
	bool Init();
	void LevelShutdownPostEntity();
	void Update( float ft );
	void LevelInitPostEntity();
	//void PreRender();
	void PostRender();

	model_t* LoadModel(const char* modelName);

	void SetMouseCaptured( bool bCaptured ) { m_bMouseCaptured = bCaptured; };
	bool IsMouseCaptured() { return m_bMouseCaptured; };

	void SetWorkCameraActive( bool bActive ) { m_bIsWorkCameraActive = bActive; SetAllNeedsUpdate(true); };
	bool IsWorkCameraActive() { return m_bIsWorkCameraActive; };

	void SetWorkCameraOrigin( const Vector& vecOrigin ) { m_vecWorkCameraOrigin = vecOrigin; };
	const Vector& GetWorkCameraOrigin() { return m_vecWorkCameraOrigin; };

	void SetWorkCameraAngles( const QAngle& angAngles ) { m_angWorkCameraAngles = angAngles; };
	const QAngle& GetWorkCameraAngles() { return m_angWorkCameraAngles; };

	void SetWorkCameraFOV( float flFOV ) { m_flWorkCameraFOV = flFOV; };
	float GetWorkCameraFOV() { return m_flWorkCameraFOV; };

	void SetSceneCameraOrigin( const Vector& vecOrigin ) { m_vecSceneCameraOrigin = vecOrigin; };
	const Vector& GetSceneCameraOrigin() { return m_vecSceneCameraOrigin; };

	void SetSceneCameraAngles( const QAngle& angAngles ) { m_angSceneCameraAngles = angAngles; };
	const QAngle& GetSceneCameraAngles() { return m_angSceneCameraAngles; };

	void SetSceneCameraFOV( float flFOV ) { m_flSceneCameraFOV = flFOV; };
	float GetSceneCameraFOV() { return m_flSceneCameraFOV; };

	Vector GetCameraOrigin()
	{
		if (m_bIsWorkCameraActive)
			return m_vecWorkCameraOrigin;
		else
			return m_vecSceneCameraOrigin;
	};

	QAngle GetCameraAngles()
	{
		if (m_bIsWorkCameraActive)
			return m_angWorkCameraAngles;
		else
			return m_angSceneCameraAngles;
	};

	float GetCameraFOV()
	{
		if (m_bIsWorkCameraActive)
			return m_flWorkCameraFOV;
		else
			return m_flSceneCameraFOV;
	};

	bool GetFileOpen() { return m_bFileOpen; };
	void SetFileOpen( bool bFileOpen ) { m_bFileOpen = bFileOpen; };

	void SetNeedsUpdate( bool needsUpdate, int index )
	{
		if (index >= DX_MAX_NEEDS_UPDATE)
			return;
		if (index >= bNeedsUpdate.Count())
			return;
		bNeedsUpdate[index] = needsUpdate;
	};
	void SetAllNeedsUpdate( bool needsUpdate )
	{
		bNeedsUpdate.RemoveAll();
		for (int i = 0; i < DX_MAX_NEEDS_UPDATE; i++)
		{
			bNeedsUpdate.AddToTail(needsUpdate);
		}
	};
	bool NeedsUpdate(int index)
	{
		if (index >= DX_MAX_NEEDS_UPDATE)
			return false;
		if (index >= bNeedsUpdate.Count())
			return false;
		return bNeedsUpdate[index];
	};

	void SetViewportWidth( int nViewportWidth ) { m_nViewportWidth = nViewportWidth; };
	int GetViewportWidth() { return m_nViewportWidth; };

	void SetViewportHeight( int nViewportHeight ) { m_nViewportHeight = nViewportHeight; };
	int GetViewportHeight() { return m_nViewportHeight; };

	void SetPlayhead( float fPlayhead );
	float GetPlayhead() { return m_fPlayhead; };

	void SetPlaybackSpeed( float fPlaybackSpeed ) { m_fPlaybackSpeed = fPlaybackSpeed; };
	float GetPlaybackSpeed() { return m_fPlaybackSpeed; };

	void SetLastTime( float fLastTime ) { m_fLastTime = fLastTime; };
	float GetLastTime() { return m_fLastTime; };

	void SetLockPlayhead( bool bLockPlayhead ) { m_bLockPlayhead = bLockPlayhead; };
	bool GetLockPlayhead() { return m_bLockPlayhead; };

	void SetZoomLevel( int nZoomLevel ) { m_nZoomLevel = nZoomLevel; };
	int GetZoomLevel() { return m_nZoomLevel; };

	void SetTimelineStart( float flTimelineStart ) { m_flTimelineStart = flTimelineStart; };
	float GetTimelineStart() { return m_flTimelineStart; };

	void SetFPS( float fps ) { this->fps = fps; };
	float GetFPS() { return fps; };
	
	void SetLayoff( bool bLayoff ) { m_bLayoff = bLayoff; };
	bool GetLayoff() { return m_bLayoff; };

	void SetLayoffFlags( DXLayoffFlags nLayoffFlags ) { m_nLayoffFlags = nLayoffFlags; };
	DXLayoffFlags GetLayoffFlags() { return m_nLayoffFlags; };

	DxeDag* RecursiveFindDag(DxeDag* parent, const char* name);
	void RecursiveRenderCurrentScene(DxeDag* parent);
	void RecursiveReleaseSceneHierarchy(DxeDag* parent);
	DxeCamera* GetCurrentCamera();

	// new keyvalues system
	void LoadDocument( const char* pszDocumentName );
	void NewDocument();
	void SaveDocument();
	void SaveDocument( const char* pszDocumentName );
	void CloseDocument();

	const char* GetLoadedDocumentName() { return m_pszLoadedDocumentName; };

	void SetDocument( DxElement* pDocument )
	{
		m_pSession = pDocument;
	};
	DxElement* GetDocument()
	{
		return m_pSession;
	};

	// SFM API-like functions
	DxeFilmClip* GetMovie();
	DxeFilmClip* GetShotAtCurrentTime();

protected:
	CDMXContextHelper* m_dmxContextHelper;
	bool m_bFileOpen = false;
	const char* m_pszLoadedDocumentName = NULL;
	bool m_bMouseCaptured;
	bool m_bIsWorkCameraActive = true;
	Vector m_vecWorkCameraOrigin;
	QAngle m_angWorkCameraAngles;
	float m_flWorkCameraFOV = 75.0f;
	Vector m_vecSceneCameraOrigin;
	QAngle m_angSceneCameraAngles;
	float m_flSceneCameraFOV = 75.0f;
	float m_flCurrentCameraMovementSpeed = 100.0f;
	bool m_bHoldingMovementKey = false;
	CUtlVector<bool>& bNeedsUpdate = *(new CUtlVector<bool>);
	int m_nViewportWidth = 1280;
	int m_nViewportHeight = 720;
	float m_fPlayhead = 0;
	float m_fPlaybackSpeed = 0; // paused or stopped by default
	float m_fLastTime = 0;
	bool m_bLockPlayhead = false;
	int m_nZoomLevel = 100;
	float m_flTimelineStart = -1;
	float fps = 24;
	bool m_bLayoff;
	DXLayoffFlags m_nLayoffFlags = DX_LAYOFF_NONE;
	DxElement* m_pSession = NULL;
	DxeUserSettings* m_pUserSettings = NULL;
};

DXEditorHelper &DirectorsCutGameSystem();

static bool DXIsLayoff()
{
	return DirectorsCutGameSystem().GetLayoff();
}

static DXLayoffFlags DXGetLayoffFlags()
{
	return DirectorsCutGameSystem().GetLayoffFlags();
}

#endif // DIRECTORSCUT_H
