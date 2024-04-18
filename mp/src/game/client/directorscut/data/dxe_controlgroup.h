//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: User settings for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#ifndef _DIRECTORSCUT_DXE_CONTROLGROUP_H_
#define _DIRECTORSCUT_DXE_CONTROLGROUP_H_

#include "dxelement.h"
#include "kvhelpers.h"

class DxeControlGroup : public DxElement
{
public:
    DxeControlGroup(const char* name);
    DxeControlGroup(const char* name, const char* typeName);
    void InitElement() override;
    // Attributes
    KvDxElementArray* GetChildren() { return (KvDxElementArray*)FindKey("children"); }
    KvDxElementArray* GetControls() { return (KvDxElementArray*)FindKey("controls"); }
    void SetGroupColor(Color color) { SetColor("groupColor", color); }
    Color GetGroupColor() { return GetColor("groupColor"); }
    void SetControlColor(Color color) { SetColor("controlColor", color); }
    Color GetControlColor() { return GetColor("controlColor"); }
    void SetVisible(bool visible) { SetBool("visible", visible); }
    bool GetVisible() { return GetBool("visible"); }
    void SetSelectable(bool selectable) { SetBool("selectable", selectable); }
    bool GetSelectable() { return GetBool("selectable"); }
    void SetSnappable(bool snappable) { SetBool("snappable", snappable); }
    bool GetSnappable() { return GetBool("snappable"); }
};

#endif // _DIRECTORSCUT_DXE_CONTROLGROUP_H_
