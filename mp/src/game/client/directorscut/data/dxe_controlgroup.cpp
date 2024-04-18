//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: User settings for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dxe_controlgroup.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

DxeControlGroup::DxeControlGroup(const char* name) : DxElement(name, "DxeControlGroup")
{
    InitElement();
};

DxeControlGroup::DxeControlGroup(const char* name, const char* typeName) : DxElement(name, typeName)
{
    InitElement();
};

void DxeControlGroup::InitElement()
{
    DxElement::InitElement();
    // Initial values
    AddSubKey(new KvDxElementArray("children"));
    AddSubKey(new KvDxElementArray("controls"));
    SetGroupColor(Color(200, 200, 200, 255));
    SetControlColor(Color(200, 200, 200, 255));
    SetVisible(true);
    SetSelectable(true);
    SetSnappable(true);
    // Factory attributes
    AddFactoryAttribute("children");
    AddFactoryAttribute("controls");
    AddFactoryAttribute("groupColor");
    AddFactoryAttribute("controlColor");
    AddFactoryAttribute("visible");
    AddFactoryAttribute("selectable");
    AddFactoryAttribute("snappable");
}
