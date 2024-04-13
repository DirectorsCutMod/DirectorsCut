//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Track group for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dxe_trackgroup.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

DxeTrackGroup::DxeTrackGroup(const char* name) : DxElement(name, "DxeTrackGroup")
{
    InitElement();
};

DxeTrackGroup::DxeTrackGroup(const char* name, const char* typeName) : DxElement(name, typeName)
{
    InitElement();
};

void DxeTrackGroup::InitElement()
{
    DxElement::InitElement();
    // Initial values
    AddSubKey(new KvDxElementArray("tracks"));
    SetVisible(true);
    SetMute(false);
    SetDisplayScale(1.0f);
    SetMinimized(false);
    SetVolume(1.0f);
    SetForceMultiTrack(false);
    // Factory attributes
    AddFactoryAttribute("tracks");
    AddFactoryAttribute("visible");
    AddFactoryAttribute("mute");
    AddFactoryAttribute("displayScale");
    AddFactoryAttribute("minimized");
    AddFactoryAttribute("volume");
    AddFactoryAttribute("forcemultitrack");
}
