//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window controls for Director's Cut.
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dxeditoranimationseteditor.h"

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

using namespace vgui;

DXEditorAnimationSetEditor::DXEditorAnimationSetEditor(Panel* pParent)
	: BaseClass(pParent, "Animation Set Editor")
{
    //m_pTree = new TreeView(this, "DXEditorElementViewerTree");
}

void DXEditorAnimationSetEditor::OnThink()
{
}

void DXEditorAnimationSetEditor::ApplySchemeSettings(IScheme *pScheme)
{
	BaseClass::ApplySchemeSettings(pScheme);
}