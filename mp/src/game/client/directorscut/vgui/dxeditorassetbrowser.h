//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window controls for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#ifndef DXEDITORASSETBROWSER_H
#define DXEDITORASSETBROWSER_H

#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/Frame.h>
#include <vgui_controls/PropertyPage.h>
#include <vgui_controls/ToolWindow.h>
#include <vgui_controls/TreeView.h>
#include <vgui_controls/ListPanel.h>

using namespace vgui;

class DXEditorAssetBrowser : public EditablePanel
{
	DECLARE_CLASS_SIMPLE( DXEditorAssetBrowser, EditablePanel );

public:
	DXEditorAssetBrowser( Panel *pParent );
    virtual void ApplySchemeSettings( IScheme *scheme );
    virtual void OnThink();
};

#endif // DXEDITORASSETBROWSER_H
