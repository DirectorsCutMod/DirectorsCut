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

class DXEditorHelper : public CAutoGameSystemPerFrame
{
public:
	void LevelShutdownPostEntity();
	void Update( float ft );
	void LevelInitPostEntity();

	void SetMouseCaptured( bool bCaptured ) { m_bMouseCaptured = bCaptured; };
	bool IsMouseCaptured() { return m_bMouseCaptured; };

	void SetWorkCameraActive( bool bActive ) { m_bIsWorkCameraActive = bActive; };
	bool IsWorkCameraActive() { return m_bIsWorkCameraActive; };

	void SetWorkCameraOrigin( const Vector& vecOrigin ) { m_vecWorkCameraOrigin = vecOrigin; };
	const Vector& GetWorkCameraOrigin() { return m_vecWorkCameraOrigin; };

	void SetWorkCameraAngles( const QAngle& angAngles ) { m_angWorkCameraAngles = angAngles; };
	const QAngle& GetWorkCameraAngles() { return m_angWorkCameraAngles; };

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

	void SetNeedsUpdate( bool bNeedsUpdate ) { this->bNeedsUpdate = bNeedsUpdate; };
	bool NeedsUpdate() { return bNeedsUpdate; };

protected:
	CDMXContextHelper* m_dmxContextHelper;
	bool m_bFileOpen = false;
	const char* m_pszLoadedDocumentName = NULL;
	bool m_bMouseCaptured;
	bool m_bIsWorkCameraActive = true;
	Vector m_vecWorkCameraOrigin;
	QAngle m_angWorkCameraAngles;
	float m_flCurrentCameraMovementSpeed = 100.0f;
	bool m_bHoldingMovementKey = false;

	CDmxElement* m_pDocument = NULL;
	CDmxElement* m_pDocumentFocusedRoot = NULL;
	bool bNeedsUpdate = false;
};

DXEditorHelper &DirectorsCutGameSystem();

#endif // DIRECTORSCUT_H
