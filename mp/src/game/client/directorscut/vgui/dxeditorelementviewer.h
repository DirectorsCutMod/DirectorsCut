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

#include <vgui/ISystem.h>
#include <vgui/IInput.h>
#include <vgui_controls/Frame.h>
#include <vgui_controls/PropertyPage.h>
#include <vgui_controls/ToolWindow.h>
#include <vgui_controls/TreeView.h>
#include <vgui_controls/ListPanel.h>
#include <vgui_controls/Button.h>
#include <vgui_controls/Splitter.h>
#include <vgui_controls/TextEntry.h>
#include <vgui_controls/CheckButton.h>
#include <vgui_controls/RichText.h>
#include <matsys_controls/colorpickerpanel.h>

using namespace vgui;

class DXEditorElementViewer : public EditablePanel
{
	DECLARE_CLASS_SIMPLE( DXEditorElementViewer, EditablePanel );

public:
	DXEditorElementViewer( Panel *pParent );

    MESSAGE_FUNC( OnTreeViewItemSelected, "TreeViewItemSelected" );
    void MakeRootButtonClick();

    virtual void ApplySchemeSettings( IScheme *scheme );
    virtual void OnThink();
    virtual void PerformLayout();

    void SetupProperties(bool reset);

protected:
    void RecursivePopulateTreeFromDocument( CDmxElement* pElement, int parentIndex );

    char m_selectedElement[ 256 ];
    TreeView* m_pTree;
    //Splitter* m_pSplitter;
    TextEntry* m_pPropTextEntry;
    CheckButton* m_pPropCheckButton;
    RichText* m_pPropLabel;
    CColorPickerButton* m_pColorPickerButton;
    Button* m_pMakeRootButton;
    RichText* pPreviewLabel;
    double lastClickTime;
    int lastSelectedIndex;
    bool m_bCanDoubleClick = true;
};

#endif // DXEDITORELEMENTVIEWER_H
