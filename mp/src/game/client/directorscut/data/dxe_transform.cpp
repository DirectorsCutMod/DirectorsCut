//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: User settings for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dxe_transform.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

DxeTransform::DxeTransform(const char* name) : DxElement(name, "DxeTransform")
{
    InitElement();
};

DxeTransform::DxeTransform(const char* name, const char* typeName) : DxElement(name, typeName)
{
    InitElement();
};

void DxeTransform::InitElement()
{
    DxElement::InitElement();
    // Initial values
    AddSubKey(new KvVector("position"));
    AddSubKey(new KvQuaternion("orientation"));
    // Factory attributes
    AddFactoryAttribute("position");
    AddFactoryAttribute("orientation");
}
