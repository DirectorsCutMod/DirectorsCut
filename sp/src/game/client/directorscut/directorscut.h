//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Director's Cut system.
//
// $NoKeywords: $
//=================================================================================//

#ifndef _DIRECTORSCUT_H_
#define _DIRECTORSCUT_H_

#include "igamesystem.h"
#include "physpropclientside.h"
#include "mathlib/vector.h"

class DirectorsCutSystem : public CAutoGameSystemPerFrame
{
public:

	DirectorsCutSystem() : CAutoGameSystemPerFrame("DirectorsCutSystem")
	{
	}

	virtual bool InitAllSystems()
	{
		return true;
	}

	virtual void PostInit();
	virtual void Shutdown();
	virtual void LevelInitPostEntity();
	virtual void LevelShutdownPreEntity();
	virtual void Update(float frametime);
};

// singleton
DirectorsCutSystem& DirectorsCutGameSystem();

#endif // _DIRECTORSCUT_H_
