//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: User settings for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#ifndef _DIRECTORSCUT_DXE_DAG_H_
#define _DIRECTORSCUT_DXE_DAG_H_

#include "dxelement.h"
#include "kvhelpers.h"
#include "dxe_transform.h"

class DxeDag : public DxElement
{
public:
    DxeDag(const char* name);
    DxeDag(const char* name, const char* typeName);
    void InitElement() override;
    // Attributes
    DxeTransform* GetTransform() { return (DxeTransform*)FindKey("transform"); }
    DxElement* GetShape() { return (DxElement*)FindKey("shape"); }
    void SetVisible(bool visible) { SetBool("visible", visible); }
    bool GetVisible() { return GetBool("visible"); }
    KvDxElementArray* GetChildren() { return (KvDxElementArray*)FindKey("children"); }
    // TODO: Throw models in DxeGameModel and render them there or whatever
};

#endif // _DIRECTORSCUT_DXE_DAG_H_
