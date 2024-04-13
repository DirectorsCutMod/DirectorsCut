//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: KeyValues data for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dxelement.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

DxElement::DxElement(const char* attributeName, const char* typeName, const char* elementName) : KeyValues(attributeName)
{
	SetTypeName(typeName);
	SetElementName(elementName);
    InitElement();
}
DxElement::DxElement(const char* attributeName, const char* typeName) : KeyValues(attributeName)
{
	SetTypeName(typeName);
	SetElementName("unnamed");
    InitElement();
}
DxElement::DxElement(const char* attributeName) : KeyValues(attributeName)
{
	SetTypeName("DxElement");
	SetElementName("unnamed");
    InitElement();
}
DxElement::~DxElement()
{
	ClearFactoryAttributes();
	deleteThis();
}
void DxElement::InitElement()
{
	// This is where children are populated in derived classes
	AddFactoryAttribute("_type");
	AddFactoryAttribute("name");
}
void DxElement::AddFactoryAttribute(const char* attributeName)
{
	// Add the attribute to the factory attributes list
	m_FactoryAttributes.AddToTail(attributeName);
}
void DxElement::RemoveFactoryAttribute(const char* attributeName)
{
	// Remove the attribute from the factory attributes list
	m_FactoryAttributes.FindAndRemove(attributeName);
}
void DxElement::ClearFactoryAttributes()
{
	// Clear the factory attributes list
	m_FactoryAttributes.RemoveAll();
}
bool DxElement::IsFactoryAttribute(const char* attributeName)
{
	// Check m_FactoryAttributes for the attribute
	return m_FactoryAttributes.HasElement(attributeName);
}
