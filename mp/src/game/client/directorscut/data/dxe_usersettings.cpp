//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: User settings for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dxe_usersettings.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

DxeUserSettings::DxeUserSettings(const char* name) : DxElement(name, "DxeUserSettings")
{
    InitElement();
};

DxeUserSettings::DxeUserSettings(const char* name, const char* typeName) : DxElement(name, typeName)
{
    InitElement();
};

void DxeUserSettings::InitElement()
{
    DxElement::InitElement();
    // Initial values
    // Factory attributes
}
