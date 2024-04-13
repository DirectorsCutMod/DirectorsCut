//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Clip data for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dxe_clip.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

DxeClip::DxeClip(const char* name) : DxElement(name, "DxeClip")
{
    InitElement();
}

DxeClip::DxeClip(const char* name, const char* typeName) : DxElement(name, typeName)
{
    InitElement();
}

void DxeClip::InitElement()
{
    DxElement::InitElement();
    // Initial values
    AddSubKey(new DxeTimeFrame("timeFrame"));
    SetColorAttribute(Color(0, 0, 0, 255));
    SetText("");
    SetMute(false);
    AddSubKey(new KvDxElementArray("trackGroups"));
    SetDisplayScale(1.0f);
    // Factory attributes
    AddFactoryAttribute("timeFrame");
    AddFactoryAttribute("color");
    AddFactoryAttribute("text");
    AddFactoryAttribute("mute");
    AddFactoryAttribute("trackGroups");
    AddFactoryAttribute("displayScale");
}
