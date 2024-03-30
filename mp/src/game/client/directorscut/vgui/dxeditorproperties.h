//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window controls for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#ifndef DXEDITORPROPERTIES_H
#define DXEDITORPROPERTIES_H

#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/Frame.h>
#include <vgui_controls/PropertyPage.h>
#include <vgui_controls/ToolWindow.h>
#include <vgui_controls/TreeView.h>
#include <vgui_controls/ListPanel.h>
#include <vgui_controls/Splitter.h>

using namespace vgui;

class DXEditorProperties : public EditablePanel
{
	DECLARE_CLASS_SIMPLE( DXEditorProperties, EditablePanel );

public:
	DXEditorProperties( Panel *pParent );
    virtual void ApplySchemeSettings( IScheme *scheme );
    virtual void OnThink();
    virtual void PerformLayout();

    void ResetPanels(bool reset);

    Splitter* GetSplitter() { return m_pSplitter; }

protected:
    Splitter* m_pSplitter;
};

// singleton
DXEditorProperties* GetDXEditorProperties();

#endif // DXEDITORPROPERTIES_H
