//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: User settings for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#ifndef _DIRECTORSCUT_DXE_TRANSFORM_H_
#define _DIRECTORSCUT_DXE_TRANSFORM_H_

#include "dxelement.h"
#include "kvhelpers.h"

class DxeTransform : public DxElement
{
public:
    DxeTransform(const char* name);
    DxeTransform(const char* name, const char* typeName);
    void InitElement() override;
    // Attributes
    KvVector* GetPosition() { return (KvVector*)FindKey("position"); }
    KvQuaternion* GetOrientation() { return (KvQuaternion*)FindKey("orientation"); }
};

#endif // _DIRECTORSCUT_DXE_TRANSFORM_H_
