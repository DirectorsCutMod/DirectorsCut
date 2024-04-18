//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: User settings for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dxe_dag.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

DxeDag::DxeDag(const char* name) : DxElement(name, "DxeDag")
{
    InitElement();
};

DxeDag::DxeDag(const char* name, const char* typeName) : DxElement(name, typeName)
{
    InitElement();
};

void DxeDag::InitElement()
{
    DxElement::InitElement();
    // Initial values
    AddSubKey(new DxeTransform("transform"));
    AddSubKey(new DxElement("shape"));
    SetVisible(true);
    AddSubKey(new KvDxElementArray("children"));
    // Factory attributes
    AddFactoryAttribute("transform");
    AddFactoryAttribute("shape");
    AddFactoryAttribute("visible");
    AddFactoryAttribute("children");
}
