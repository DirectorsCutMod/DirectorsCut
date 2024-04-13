//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Track for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dxe_track.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

DxeTrack::DxeTrack(const char* name) : DxElement(name, "DxeTrack")
{
    InitElement();
};

DxeTrack::DxeTrack(const char* name, const char* typeName) : DxElement(name, typeName)
{
    InitElement();
};

void DxeTrack::InitElement()
{
    DxElement::InitElement();
    // Initial values
    AddSubKey(new KvDxElementArray("children"));
    SetCollapsed(false);
    SetMute(false);
    SetSynched(true);
    SetClipType(0);
    SetVolume(1.0f);
    SetDisplayScale(1.0f);
    // Factory attributes
    AddFactoryAttribute("children");
    AddFactoryAttribute("collapsed");
    AddFactoryAttribute("mute");
    AddFactoryAttribute("synched");
    AddFactoryAttribute("clipType");
    AddFactoryAttribute("volume");
    AddFactoryAttribute("displayScale");
}
