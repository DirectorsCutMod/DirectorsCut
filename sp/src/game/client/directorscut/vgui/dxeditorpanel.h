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

#include "dxeditorelementviewer.h"
#include "dxeditorviewport.h"
#include "dxeditoranimationseteditor.h"
#include "dxeditortimeline.h"
#include "dxeditorproperties.h"
#include "dxeditorassetbrowser.h"
#include "dxeditorwelcome.h"

using namespace vgui;

#include <vgui/IVGui.h>
#include <vgui_controls/Panel.h>
#include <vgui_controls/Frame.h>
#include <vgui_controls/MenuBar.h>
#include <vgui_controls/MenuButton.h>
#include <vgui_controls/Label.h>
#include <vgui_controls/FileOpenDialog.h>


class DXEditorPanel : public Panel
{
	DECLARE_CLASS_SIMPLE( DXEditorPanel, Panel );
	DECLARE_REFERENCED_CLASS( DXEditorPanel );

public:
	static void DestroyEditor();
	static void ToggleEditor();
	static bool IsEditorVisible();
	void PopulateEditor();
	void OpenDocumentFileDialog(bool bSave);
	
	MESSAGE_FUNC_PARAMS( OnFileSelected, "FileSelected", pKV );

	~DXEditorPanel();

	static CUtlReference< DXEditorPanel > m_refInstance;

	CUtlVector< EditablePanel* > m_vecPanels;
	bool bShowedWelcome;

protected:
	DHANDLE< FileOpenDialog > m_hFileOpenDialog;
	void ApplySchemeSettings( IScheme *scheme );
	void PerformLayout();
	void PaintBackground();
	void MakeReadyForUse();
	virtual void OnMousePressed( MouseCode code );
	virtual void Think();
	virtual void OnCommand( char const *cmd );

	Frame* m_pPanel;
	MenuBar* m_pMenuBar;
	MenuButton* m_pMBut_File;
	Label* m_pLabel;

private:
	DXEditorPanel( VPANEL pParent );
};

#endif // DXEDITORPANEL_H
