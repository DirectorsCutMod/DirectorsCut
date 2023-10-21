//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Director's Cut system.
//
// $NoKeywords: $
//=================================================================================//

#ifndef DIRECTORSCUT_H
#define DIRECTORSCUT_H

#include "igamesystem.h"
#include "dmxloader/dmxloader.h"
#include "dmxloader/dmxelement.h"
#include "filesystem.h"
#include "dxproperties.h"

IMaterial* GetPrimaryScreenMaterial();
KeyValues* GetPrimaryScreenKV();
ITexture* GetPrimaryViewportTex();
int GetPrimaryViewportTexID();
void AllocatePrimaryViewport();
void DeallocatePrimaryViewport();

#define DX_MAX_NEEDS_UPDATE 2

class DXEditorHelper : public CAutoGameSystemPerFrame
{
public:
	bool Init();
	void LevelShutdownPostEntity();
	void Update( float ft );
	void LevelInitPostEntity();
	//void PreRender();
	//void PostRender();

	void SetMouseCaptured( bool bCaptured ) { m_bMouseCaptured = bCaptured; };
	bool IsMouseCaptured() { return m_bMouseCaptured; };

	void SetWorkCameraActive( bool bActive ) { m_bIsWorkCameraActive = bActive; };
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

	void LoadDocument( const char* pszDocumentName );
	void NewDocument();
	void SaveDocument();
	void SaveDocument( const char* pszDocumentName );
	void CloseDocument();

	const char* GetLoadedDocumentName() { return m_pszLoadedDocumentName; };

	bool GetFileOpen() { return m_bFileOpen; };
	void SetFileOpen( bool bFileOpen ) { m_bFileOpen = bFileOpen; };

	void SetDocument( CDmxElement* pDocument )
	{
		m_pDocument = pDocument;
	};
	CDmxElement* GetDocument()
	{
		return m_pDocument;
	};

	void SetDocumentFocusedRoot( CDmxElement* pDocumentFocusedRoot ) { m_pDocumentFocusedRoot = pDocumentFocusedRoot; };
	CDmxElement* GetDocumentFocusedRoot() { return m_pDocumentFocusedRoot; };

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

	void SetPlayhead( float fPlayhead ) { m_fPlayhead = fPlayhead; };
	float GetPlayhead() { return m_fPlayhead; };

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
	CDmxElement* m_pDocument = NULL;
	CDmxElement* m_pDocumentFocusedRoot = NULL;
	CUtlVector<bool>& bNeedsUpdate = *(new CUtlVector<bool>);
	int m_nViewportWidth = 1280;
	int m_nViewportHeight = 720;
	float m_fPlayhead = 0;
};

DXEditorHelper &DirectorsCutGameSystem();

#endif // DIRECTORSCUT_H
