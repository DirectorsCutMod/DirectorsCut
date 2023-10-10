//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Director's Cut system.
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "directorscut.h"
#include "iclientmode.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

DirectorsCutSystem g_DirectorsCutSystem;

DirectorsCutSystem& DirectorsCutGameSystem()
{
	return g_DirectorsCutSystem;
}

void DirectorsCutSystem::PostInit()
{
}

void DirectorsCutSystem::Shutdown()
{
}

void DirectorsCutSystem::LevelInitPostEntity()
{
}

void DirectorsCutSystem::LevelShutdownPreEntity()
{
}

void DirectorsCutSystem::Update(float frametime)
{
}
