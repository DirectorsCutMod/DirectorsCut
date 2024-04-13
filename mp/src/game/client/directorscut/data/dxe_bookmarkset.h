//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Bookmark set for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#ifndef _DIRECTORSCUT_DXE_BOOKMARKSET_H_
#define _DIRECTORSCUT_DXE_BOOKMARKSET_H_

#include "dxelement.h"
#include "kvhelpers.h"

class DxeBookmarkSet : public DxElement
{
public:
    DxeBookmarkSet(const char* name);
    DxeBookmarkSet(const char* name, const char* typeName);
    void InitElement() override;
    // Attributes
    KvDxElementArray* GetBookmarks() { return (KvDxElementArray*)FindKey("bookmarks"); }
};

#endif // _DIRECTORSCUT_DXE_BOOKMARKSET_H_
