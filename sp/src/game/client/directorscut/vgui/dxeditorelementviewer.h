//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window controls for Director's Cut.
//
// $NoKeywords: $
//=================================================================================//

#ifndef DXEDITORELEMENTVIEWER_H
#define DXEDITORELEMENTVIEWER_H

#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/Frame.h>
#include <vgui_controls/PropertyPage.h>
#include <vgui_controls/ToolWindow.h>
#include <vgui_controls/TreeView.h>
#include <vgui_controls/ListPanel.h>
#include <vgui_controls/Button.h>

using namespace vgui;

class DXEditorElementViewer : public EditablePanel
{
	DECLARE_CLASS_SIMPLE( DXEditorElementViewer, EditablePanel );

public:
	DXEditorElementViewer( Panel *pParent );

    void OnViewItemSelected();

    MESSAGE_FUNC( OnTreeViewItemSelected, "TreeViewItemSelected" );
	MESSAGE_FUNC( OnItemSelected, "ItemSelected" );

    virtual void ApplySchemeSettings( IScheme *scheme );
    virtual void OnThink();

protected:
    void RecursivePopulateListFromTree( int current, CUtlVector< KeyValues* >& items );

    TreeView* m_pTree;
    ListPanel* m_pList;
    Button* m_pBackButton;
    Button* m_pForwardButton;
    Button* m_pUpButton;
    Button* m_pRefreshButton;
};

#endif // DXEDITORELEMENTVIEWER_H
