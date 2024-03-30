//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: TF2 proxy dummies, so that materials aren't displayed incorrectly.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dummyproxies.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

bool CDummyProxy::Init(IMaterial* pMaterial, KeyValues* pKeyValues)
{
	mat = pMaterial;
	return true;
};

IMaterial* CDummyProxy::GetMaterial()
{
	return mat;
}

bool CDummyProxyResultFloat::Init(IMaterial* pMaterial, KeyValues* pKeyValues)
{
	bool foundVar;

	char const* pResultVarName = pKeyValues->GetString("resultVar");
	if (!pResultVarName)
		return false;

	resultVar = pMaterial->FindVar(pResultVarName, &foundVar, false);
	if (!foundVar)
		return false;

	resultVar->SetFloatValue(0.f);

	mat = pMaterial;
	return true;
};

bool CDummyProxyResultFloatInverted::Init(IMaterial* pMaterial, KeyValues* pKeyValues)
{
	bool foundVar;

	char const* pResultVarName = pKeyValues->GetString("resultVar");
	if (!pResultVarName)
		return false;

	resultVar = pMaterial->FindVar(pResultVarName, &foundVar, false);
	if (!foundVar)
		return false;

	resultVar->SetFloatValue(1.f);

	mat = pMaterial;
	return true;
};

bool CDummyProxyResultRGB::Init(IMaterial* pMaterial, KeyValues* pKeyValues)
{
	bool foundVar;

	char const* pResultVarName = pKeyValues->GetString("resultVar");
	if (!pResultVarName)
		return false;

	resultVar = pMaterial->FindVar(pResultVarName, &foundVar, false);
	if (!foundVar)
		return false;

	resultVar->SetStringValue("[0 0 0]");

	mat = pMaterial;
	return true;
};

bool CDummyProxyResultRGBInverted::Init(IMaterial* pMaterial, KeyValues* pKeyValues)
{
	bool foundVar;

	char const* pResultVarName = pKeyValues->GetString("resultVar");
	if (!pResultVarName)
		return false;

	resultVar = pMaterial->FindVar(pResultVarName, &foundVar, false);
	if (!foundVar)
		return false;

	resultVar->SetStringValue("[1 1 1]");

	mat = pMaterial;
	return true;
};
