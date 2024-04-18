//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window controls for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dxeditoranimationseteditor.h"
#include "../data/dxe_animationset.h"

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

#define TREE_TEXT_COLOR Color( 200, 255, 200, 255 )
#define LIST_TEXT_COLOR TREE_TEXT_COLOR

using namespace vgui;

DXEditorAnimationSetEditor::DXEditorAnimationSetEditor(Panel* pParent)
	: BaseClass(pParent, "Animation Set Editor")
{
    m_pTree = new TreeView(this, "DXEditorElementViewerTree");
    IScheme* pscheme = scheme()->GetIScheme(GetScheme());
    HFont treeFont = pscheme->GetFont("DefaultVerySmall");
    m_pTree->SetFont(treeFont);
    m_pTree->SetFgColor(TREE_TEXT_COLOR);

    // Make ready for use
    m_pTree->MakeReadyForUse();
}

void DXEditorAnimationSetEditor::OnThink()
{
	if(DirectorsCutGameSystem().NeedsUpdate(DX_NEEDS_UPDATE_ANIMSETEDITOR) == true)
    {
		DirectorsCutGameSystem().SetNeedsUpdate(false, DX_NEEDS_UPDATE_ANIMSETEDITOR);
		PopulateTreeFromDocument();
        m_pTree->ExpandItem(m_pTree->GetRootItemIndex(), true);
	}

    // TODO: layout?

    int x, y, w, h;
    int offset = 8;

    GetBounds(x, y, w, h);
    m_pTree->SetBounds(offset, offset, w - offset * 2, h - offset * 2);
}

void DXEditorAnimationSetEditor::ApplySchemeSettings(IScheme *pScheme)
{
	BaseClass::ApplySchemeSettings(pScheme);

    // Dummy tree view
	HFont treeFont = pScheme->GetFont( "DefaultVerySmall" );
	m_pTree->SetFont( treeFont );
}


void DXEditorAnimationSetEditor::PopulateTreeFromDocument()
{
	DxeFilmClip* selectedShot = DirectorsCutGameSystem().GetShotAtCurrentTime();

	// Clear tree view
	int selIndex = m_pTree->GetFirstSelectedItem();
	if (selIndex != -1)
	{
		KeyValues* selData = m_pTree->GetItemData(selIndex);
		if (selData != NULL)
		{
			// Set selected element
			Q_strncpy(m_selectedElement, selData->GetString("Text"), 256);
		}
	}

	// Get current tree view bounds
	int x, y, w, h;
	m_pTree->GetBounds(x, y, w, h);

	// Clear tree view
	m_pTree->RemoveAll();

	// Set tree view bounds
	m_pTree->SetBounds(x, y, w, h);

	//if (m_pSelectedShot == NULL)
	if (selectedShot == NULL)
		return;

	// Populate tree view
	KeyValues* kv = new KeyValues( "TVI" );
	kv->SetString("Text", selectedShot->GetName());
	//kv->SetString("Text", m_pSelectedShot->GetName());
	kv->SetString( "Data", "" );
	kv->SetString( "Type", "animationsets" );
	int rootIndex = m_pTree->AddItem( kv, -1 );

	// Add a tree view item for each animation set in m_pSelectedShot -> animationSets
	for( int i = 0; i < selectedShot->GetAnimationSets()->GetSize(); i++ )
	{
		DxeAnimationSet* pAnimationSet = (DxeAnimationSet*)selectedShot->GetAnimationSets()->GetElement(i);
		if( pAnimationSet == NULL )
			continue;
		KeyValues* kv = new KeyValues( "TVI" );
		kv->SetString( "Text", pAnimationSet->GetName() );
		kv->SetString( "Data", "" );
		kv->SetString( "Type", "dag" );

		// if animation set contains an attribute named "camera", "gameModel" or "particle system" then set its type to that
		int type = -1;
		if( pAnimationSet->FindKey("camera") != NULL )
		{
			kv->SetString( "Type", "camera" );
			type = 1;
		}
		else if( pAnimationSet->FindKey("gameModel") != NULL )
		{
			kv->SetString( "Type", "gameModel" );
			type = 0;
		}
		else if( pAnimationSet->FindKey("particle system") != NULL )
		{
			kv->SetString( "Type", "particle system" );
			type = 2;
		}
		else if( pAnimationSet->FindKey("light") != NULL )
		{
			kv->SetString( "Type", "light" );
			type = 3;
		}

		int animationSetIndex = m_pTree->AddItem( kv, rootIndex );
		switch(type)
		{
			case 0: // gameModel
				m_pTree->SetItemFgColor(animationSetIndex, Color( 64, 255, 64, 255 ));
				break;
			case 1: // camera
				m_pTree->SetItemFgColor(animationSetIndex, Color( 64, 64, 255, 255 ));
				break;
			case 2: // particle system
				m_pTree->SetItemFgColor(animationSetIndex, Color( 255, 64, 64, 255 ));
				break;
			case 3: // light
				m_pTree->SetItemFgColor(animationSetIndex, Color( 255, 255, 64, 255 ));
				break;
		}

		// for each pAnimationSet -> rootControlGroup -> children -> [i], add a tree view item
		// TODO: recursion, rootControlGroup children can also have children
		DxeControlGroup* pRootControlGroup = pAnimationSet->GetRootControlGroup();
		if( pRootControlGroup == NULL )
			continue;
		for( int j = 0; j < pRootControlGroup->GetChildren()->GetSize(); j++ )
		{
			DxeControlGroup* pChild = (DxeControlGroup*)pRootControlGroup->GetChildren()->GetElement(j);
			if(!pChild)
				continue;
			const char* pChildName = pChild->GetElementName();
			if( pChildName == NULL )
				continue;
			KeyValues* kv = new KeyValues( "TVI" );
			kv->SetString( "Text", pChildName );
			kv->SetString( "Data", "" );
			kv->SetString( "Type", "controlGroup" );
			int controlGroupIndex = m_pTree->AddItem( kv, animationSetIndex );
			// Add each pChildren[j] -> controls attribute
			for( int k = 0; k < pChild->GetControls()->GetSize(); k++ )
			{
				DxElement* pControl = pChild->GetControls()->GetElement(k);
				const char* pControlName = pControl->GetElementName();
				if( pControlName == NULL )
					continue;
				KeyValues* kv = new KeyValues( "TVI" );
				kv->SetString( "Text", pControlName );
				kv->SetString( "Data", "" );
				kv->SetString( "Type", "control" );
				m_pTree->AddItem( kv, controlGroupIndex );
				// TODO: If type is "DmeTransformControl", add pos, x, y, z, rot, x, y, and z tree view items
			}
		}
	}
}
