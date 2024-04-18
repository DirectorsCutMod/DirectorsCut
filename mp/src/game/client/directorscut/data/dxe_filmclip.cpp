//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Clip data for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dxe_filmclip.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

DxeFilmClip::DxeFilmClip(const char* name) : DxeClip(name, "DxeFilmClip")
{
    InitElement();
};

DxeFilmClip::DxeFilmClip(const char* name, const char* typeName) : DxeClip(name, typeName)
{
    InitElement();
};

void DxeFilmClip::InitElement()
{
    DxeClip::InitElement();
    // Initial values
    //AddSubKey(new DxeMaterialOverlayFXClip("materialOverlay"));
    SetMapName("");
    SetActiveCamera("");
    AddSubKey(new KvDxElementArray("monitorCameras"));
    SetActiveMonitor(-1);
    //AddSubKey(new DxeScene("scene"));
    SetAviFile("");
    SetFadeIn(0.0f);
    SetFadeOut(0.0f);
    AddSubKey(new KvDxElementArray("inputs"));
    AddSubKey(new KvDxElementArray("operators"));
    SetUseAviFile(false);
    AddSubKey(new KvDxElementArray("animationSets"));
    AddSubKey(new KvDxElementArray("bookmarkSets"));
    SetActiveBookmarkSet(0);
    //AddSubKey(new DxeTrackGroup("subClipTrackGroup"));
    SetVolume(1.0f);
    AddSubKey(new KvStringArray("concommands"));
    AddSubKey(new KvStringArray("convars"));
    // Factory attributes
    AddFactoryAttribute("materialOverlay");
    AddFactoryAttribute("mapname");
    AddFactoryAttribute("activeCamera");
    AddFactoryAttribute("monitorCameras");
    AddFactoryAttribute("activeMonitor");
    AddFactoryAttribute("scene");
    AddFactoryAttribute("aviFile");
    AddFactoryAttribute("fadeIn");
    AddFactoryAttribute("fadeOut");
    AddFactoryAttribute("inputs");
    AddFactoryAttribute("operators");
    AddFactoryAttribute("useAviFile");
    AddFactoryAttribute("animationSets");
    AddFactoryAttribute("bookmarkSets");
    AddFactoryAttribute("activeBookmarkSet");
    AddFactoryAttribute("subClipTrackGroup");
    AddFactoryAttribute("volume");
    AddFactoryAttribute("concommands");
    AddFactoryAttribute("convars");
}
