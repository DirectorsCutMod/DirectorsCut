//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window controls for Director's Cut.
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "..\directorscut.h"
#include "dxeditorproperties.h"
#include "..\dxproperties.h"

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

using namespace vgui;

DXEditorProperties* g_DXEditorProperties;
DXEditorProperties* GetDXEditorProperties()
{
	return g_DXEditorProperties;
}

DXEditorProperties::DXEditorProperties(Panel* pParent)
	: BaseClass(pParent, "Inspector")
{
	// Two column layout: left column is the preview, right column is the properties.
	m_pSplitter = new Splitter(this, "DXEditorElementViewerSplitter", SPLITTER_MODE_VERTICAL, 1);
	float flFractions[2] = { 0.6f, 0.4f };
	m_pSplitter->RespaceSplitters(flFractions);
	m_pSplitter->MakeReadyForUse();
	g_DXEditorProperties = this;
}

void DXEditorProperties::OnThink()
{
    // TODO: layout?
	InvalidateLayout(true);
	/*
	DXProperty* pProperty = DirectorsCutGameSystem().GetCurrentProperty();
	if(DirectorsCutGameSystem().PropertyUpdated())
	{
		DirectorsCutGameSystem().SetPropertyUpdated(false);
		if (pProperty != NULL)
		{
			m_pLeftPanel->MarkForDeletion();
			m_pRightPanel->MarkForDeletion();
			m_pLeftPanel = new EditablePanel(m_pSplitter->GetChild(0), "DXEditorElementViewerLeftPanel");
			m_pRightPanel = new EditablePanel(m_pSplitter->GetChild(1), "DXEditorElementViewerRightPanel");
			pProperty->CreatePanel(m_pLeftPanel, m_pRightPanel);
		}
	}
	if(DirectorsCutGameSystem().NeedsUpdate(0))
	{
		if (pProperty != NULL)
		{
			//pProperty->UpdatePanel(m_pLeftPanel, m_pRightPanel);
		}
	}
	*/
}

void DXEditorProperties::PerformLayout()
{
	BaseClass::PerformLayout();

	if(m_pSplitter == NULL)
		return;

	int offset = 4;
	int x, y, w, h;
    GetBounds(x, y, w, h);
	m_pSplitter->SetBounds(offset, offset, w - (offset*2), h - (offset*2));

	// Set children of splitter children to fill the splitter
	Panel* pLeft = m_pSplitter->GetChild(0);
	Panel* pRight = m_pSplitter->GetChild(1);
	if(pLeft->GetChildCount() > 0)
	{
		pLeft->GetBounds(x, y, w, h);
		for (int i = 0; i < pLeft->GetChildCount(); i++)
		{
			pLeft->GetChild(i)->SetBounds(offset, offset, w - (offset*2), h - (offset*2));
		}
	}
	if(pRight->GetChildCount() > 0)
	{
		pRight->GetBounds(x, y, w, h);
		for (int i = 0; i < pRight->GetChildCount(); i++)
		{
			pRight->GetChild(i)->SetBounds(offset, offset, w - (offset*2), h - (offset*2));
		}
	}
}

void DXEditorProperties::ApplySchemeSettings(IScheme *pScheme)
{
	BaseClass::ApplySchemeSettings(pScheme);
}

void DXEditorProperties::ResetPanels(bool reset)
{
	if (m_pSplitter != NULL)
	{
		Panel* pLeft = m_pSplitter->GetChild(0);
		Panel* pRight = m_pSplitter->GetChild(1);
		if(pLeft->GetChildCount() > 0)
		{
			// Remove all children of the left panel
			for (int i = 0; i < pLeft->GetChildCount(); i++)
			{
				if(reset)
					pLeft->GetChild(i)->MarkForDeletion();
				else
					pLeft->GetChild(i)->SetVisible(false);
			}
		}
		if(pRight->GetChildCount() > 0)
		{
			// Remove all children of the right panel
			for (int i = 0; i < pRight->GetChildCount(); i++)
			{
				if(reset)
					pRight->GetChild(i)->MarkForDeletion();
				else
					pRight->GetChild(i)->SetVisible(false);
			}
		}
	}
}
