//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window controls for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#ifndef DXEDITORTIMELINE_H
#define DXEDITORTIMELINE_H

#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/Frame.h>
#include <vgui_controls/PropertyPage.h>
#include <vgui_controls/ToolWindow.h>
#include <vgui_controls/TreeView.h>
#include <vgui_controls/ListPanel.h>

using namespace vgui;

class DXEditorTimeline : public EditablePanel
{
	DECLARE_CLASS_SIMPLE( DXEditorTimeline, EditablePanel );

public:
	DXEditorTimeline( Panel *pParent );
    virtual void ApplySchemeSettings( IScheme *scheme );
    virtual void OnThink();
    virtual void Paint();

protected:
    HFont m_hFont;
};

#endif // DXEDITORTIMELINE
