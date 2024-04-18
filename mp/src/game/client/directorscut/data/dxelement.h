//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: KeyValues data for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#ifndef _DIRECTORSCUT_DXELEMENT_H_
#define _DIRECTORSCUT_DXELEMENT_H_

#include "KeyValues.h"

class DxElement : public KeyValues
{
public:
	DxElement(const char* attributeName, const char* typeName, const char* elementName);
	DxElement(const char* attributeName, const char* typeName);
	DxElement(const char* attributeName);
    virtual void InitElement();
    // if this type name doesn't get used, just dummy it out
    // keyvalue iteration would just be harder to do
    const char* GetTypeName() { return GetString("_type"); }
    void SetTypeName(const char* name) { SetString("_type", name); }
    const char* GetElementName() { return GetString("name"); }
    void SetElementName(const char* name) { SetString("name", name); }
    // Factory attribute disambiguation
    bool IsFactoryAttribute(const char* attributeName);
protected:
    void AddFactoryAttribute(const char* attributeName);
    void RemoveFactoryAttribute(const char* attributeName);
    void ClearFactoryAttributes();
private:
    CUtlVector<const char*> m_FactoryAttributes;
};

#endif // _DIRECTORSCUT_DXELEMENT_H_
