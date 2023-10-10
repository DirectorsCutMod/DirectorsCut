//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window controls for Director's Cut.
//
// $NoKeywords: $
//=================================================================================//

#ifndef DXEDITORPANEL_H
#define DXEDITORPANEL_H

#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/Frame.h>
#include <vgui_controls/PropertyPage.h>
#include <vgui_controls/ToolWindow.h>

using namespace vgui;

class DXEditorPage : public EditablePanel
{
	DECLARE_CLASS_SIMPLE( DXEditorPage, EditablePanel );

public:
	DXEditorPage( Panel *pParent );
};

#endif // DXEDITORPANEL_H
