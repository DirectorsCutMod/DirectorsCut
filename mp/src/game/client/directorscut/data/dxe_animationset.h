//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: User settings for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#ifndef _DIRECTORSCUT_DXE_ANIMATIONSET_H_
#define _DIRECTORSCUT_DXE_ANIMATIONSET_H_

#include "dxelement.h"
#include "kvhelpers.h"
#include "dxe_controlgroup.h"

class DxeAnimationSet : public DxElement
{
public:
    DxeAnimationSet(const char* name);
    DxeAnimationSet(const char* name, const char* typeName);
    void InitElement() override;
    // Attributes
    KvDxElementArray* GetControls() { return (KvDxElementArray*)FindKey("controls"); }
    KvDxElementArray* GetPresetGroups() { return (KvDxElementArray*)FindKey("presetGroups"); }
    KvDxElementArray* GetPhonemeMap() { return (KvDxElementArray*)FindKey("phonememap"); }
    KvDxElementArray* GetOperators() { return (KvDxElementArray*)FindKey("operators"); }
    DxeControlGroup* GetRootControlGroup() { return (DxeControlGroup*)FindKey("rootControlGroup"); }
};

#endif // _DIRECTORSCUT_DXE_ANIMATIONSET_H_
