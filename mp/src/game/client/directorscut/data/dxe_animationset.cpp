//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: User settings for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dxe_animationset.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

DxeAnimationSet::DxeAnimationSet(const char* name) : DxElement(name, "DxeAnimationSet")
{
    InitElement();
};

DxeAnimationSet::DxeAnimationSet(const char* name, const char* typeName) : DxElement(name, typeName)
{
    InitElement();
};

void DxeAnimationSet::InitElement()
{
    DxElement::InitElement();
    // Initial values
    AddSubKey(new KvDxElementArray("controls"));
    AddSubKey(new KvDxElementArray("presetGroups"));
    AddSubKey(new KvDxElementArray("phonememap"));
    AddSubKey(new KvDxElementArray("operators"));
    AddSubKey(new DxeControlGroup("rootControlGroup"));
    // Factory attributes
    AddFactoryAttribute("controls");
    AddFactoryAttribute("presetGroups");
    AddFactoryAttribute("phonememap");
    AddFactoryAttribute("operators");
    AddFactoryAttribute("rootControlGroup");
}
