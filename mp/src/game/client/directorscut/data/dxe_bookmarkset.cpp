//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Bookmark set for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dxe_bookmarkset.h"
#include "kvhelpers.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

DxeBookmarkSet::DxeBookmarkSet(const char* name) : DxElement(name, "DxeBookmarkSet")
{
    InitElement();
};

DxeBookmarkSet::DxeBookmarkSet(const char* name, const char* typeName) : DxElement(name, typeName)
{
    InitElement();
};

void DxeBookmarkSet::InitElement()
{
    DxElement::InitElement();
    // Initial values
    AddSubKey(new KvDxElementArray("bookmarks"));
    // Factory attributes
    AddFactoryAttribute("bookmarks");
}
