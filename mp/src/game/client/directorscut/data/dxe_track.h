//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Track for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#ifndef _DIRECTORSCUT_DXE_TRACK_H_
#define _DIRECTORSCUT_DXE_TRACK_H_

#include "dxelement.h"
#include "kvhelpers.h"

class DxeTrack : public DxElement
{
public:
    DxeTrack(const char* name);
    DxeTrack(const char* name, const char* typeName);
    void InitElement() override;
    // Attributes
    KvDxElementArray* GetChildren() { return (KvDxElementArray*)FindKey("children"); }
    void SetCollapsed(bool collapsed) { SetBool("collapsed", collapsed); }
    bool GetCollapsed() { return GetBool("collapsed"); }
    void SetMute(bool mute) { SetBool("mute", mute); }
    bool GetMute() { return GetBool("mute"); }
    void SetSynched(bool synched) { SetBool("synched", synched); }
    bool GetSynched() { return GetBool("synched"); }
    void SetClipType(int clipType) { SetInt("clipType", clipType); }
    int GetClipType() { return GetInt("clipType"); }
    void SetVolume(float volume) { SetFloat("volume", volume); }
    float GetVolume() { return GetFloat("volume", 1.0f); }
    void SetDisplayScale(float scale) { SetFloat("displayScale", scale); }
    float GetDisplayScale() { return GetFloat("displayScale", 1.0f); }
};

#endif // _DIRECTORSCUT_DXE_TRACK_H_
