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

#include <vgui/IVGui.h>
#include <vgui_controls/Panel.h>
#include <vgui_controls/Frame.h>
#include <vgui_controls/MenuBar.h>
#include <vgui_controls/MenuButton.h>
#include <vgui_controls/Label.h>

enum ERoot_FileMenu_t
{
	ER_FMENU_NEW = 0,
	ER_FMENU_OPEN,
	ER_FMENU_SAVE,
	ER_FMENU_SAVE_AS,
	ER_FMENU_SAVE_ALL,
	ER_FMENU_SCREENSHOT,
	ER_FMENU_ECONFIG,
	ER_FMENU_UNDO,
	ER_FMENU_REDO,
};

class DXEditorPanel : public Panel
{
	DECLARE_CLASS_SIMPLE( DXEditorPanel, Panel );
	DECLARE_REFERENCED_CLASS( DXEditorPanel );

public:

	MESSAGE_FUNC_INT( OnMenuFile, "onmenufile", entry );

	static void DestroyEditor();
	static void ToggleEditor();
	static bool IsEditorVisible();
	void PopulateEditor();

	~DXEditorPanel();

	static CUtlReference< DXEditorPanel > m_refInstance;

	CUtlVector< EditablePanel* > m_vecPanels;

protected:
	void ApplySchemeSettings( IScheme *scheme );
	void PerformLayout();
	void PaintBackground();
	virtual void OnMousePressed( MouseCode code );
	virtual void Think();

	Frame* m_pPanel;
	MenuBar* m_pMenuBar;
	MenuButton* m_pMBut_File;
	Label* m_pLabel;

private:
	DXEditorPanel( VPANEL pParent );
};

#endif // DXEDITORPANEL_H
