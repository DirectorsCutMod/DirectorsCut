//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window controls for Director's Cut.
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dxeditorassetbrowser.h"

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

using namespace vgui;

DXEditorAssetBrowser::DXEditorAssetBrowser(Panel* pParent)
	: BaseClass(pParent, "Asset Browser")
{
}

void DXEditorAssetBrowser::OnThink()
{
}

void DXEditorAssetBrowser::ApplySchemeSettings(IScheme *pScheme)
{
	BaseClass::ApplySchemeSettings(pScheme);
}