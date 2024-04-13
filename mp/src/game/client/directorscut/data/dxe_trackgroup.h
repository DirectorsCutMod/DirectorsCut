//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Track group for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#ifndef _DIRECTORSCUT_DXE_TRACKGROUP_H_
#define _DIRECTORSCUT_DXE_TRACKGROUP_H_

#include "dxelement.h"
#include "kvhelpers.h"

class DxeTrackGroup : public DxElement
{
public:
    DxeTrackGroup(const char* name);
    DxeTrackGroup(const char* name, const char* typeName);
    void InitElement() override;
    // Attributes
    KvDxElementArray* GetTracks() { return (KvDxElementArray*)FindKey("tracks"); }
    void SetVisible(bool visible) { SetBool("visible", visible); }
    bool GetVisible() { return GetBool("visible"); }
    void SetMute(bool mute) { SetBool("mute", mute); }
    bool GetMute() { return GetBool("mute"); }
    void SetDisplayScale(float scale) { SetFloat("displayScale", scale); }
    float GetDisplayScale() { return GetFloat("displayScale", 1.0f); }
    void SetMinimized(bool minimized) { SetBool("minimized", minimized); }
    bool GetMinimized() { return GetBool("minimized"); }
    void SetVolume(float volume) { SetFloat("volume", volume); }
    float GetVolume() { return GetFloat("volume", 1.0f); }
    void SetForceMultiTrack(bool forceMultiTrack) { SetBool("forcemultitrack", forceMultiTrack); }
    bool GetForceMultiTrack() { return GetBool("forcemultitrack"); }
};

#endif // _DIRECTORSCUT_DXE_TRACKGROUP_H_
