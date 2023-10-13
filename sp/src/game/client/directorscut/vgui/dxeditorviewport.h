//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window controls for Director's Cut.
//
// $NoKeywords: $
//=================================================================================//

#ifndef DXEDITORVIEWPORT_H
#define DXEDITORVIEWPORT_H

#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/EditablePanel.h>

using namespace vgui;

class DXEditorViewport : public EditablePanel
{
	DECLARE_CLASS_SIMPLE(DXEditorViewport, EditablePanel);

public:
	DXEditorViewport(Panel* pParent);

	~DXEditorViewport();
	virtual void Paint();
	virtual void OnThink();

	virtual void OnMousePressed(MouseCode code);
	virtual void OnMouseReleased(MouseCode code);
	virtual void OnCursorMoved(int x, int y);

protected:
	int m_nTextureID;
	IMaterial *m_pScreenMaterial;
	KeyValues *m_pScreenKV;
};

#endif // DXEDITORVIEWPORT_H
