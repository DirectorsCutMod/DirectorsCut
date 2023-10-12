//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Director's Cut system.
//
// $NoKeywords: $
//=================================================================================//

#ifndef DIRECTORSCUT_H
#define DIRECTORSCUT_H

#include "igamesystem.h"

static class DXEditorHelper : public CAutoGameSystemPerFrame
{
public:
	void LevelShutdownPostEntity();
	void Update( float ft );
	void LevelInitPostEntity();

} __g_dxEditorHelper;

#endif // DIRECTORSCUT_H
