//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window controls for Director's Cut.
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dxeditoranimationseteditor.h"

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
	if(DirectorsCutGameSystem().NeedsUpdate(1) == true)
    {
		DirectorsCutGameSystem().SetNeedsUpdate(false, 1);
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
    //DECLARE_DMX_CONTEXT_NODECOMMIT();
    if( m_pSelectedShot == NULL)
    {
        // Find first clip in document
        CDmxElement* pRoot = DirectorsCutGameSystem().GetDocument();
		if( pRoot == NULL )
			return;
		// activeClip -> subClipTrackGroup -> tracks -> [0] -> children -> [0]
		CDmxElement* pClip = pRoot->GetValue<CDmxElement*>( "activeClip" );
		if( pClip == NULL )
			return;
		CDmxElement* pSubClipTrackGroup = pClip->GetValue<CDmxElement*>( "subClipTrackGroup" );
		if( pSubClipTrackGroup == NULL )
			return;
		const CUtlVector<CDmxElement*>& pTracks = pSubClipTrackGroup->GetArray<CDmxElement*>( "tracks" );
		if( pTracks.Count() == 0 )
			return;
		CDmxElement* pTrack = pTracks[0];
		if( pTrack == NULL )
			return;
		const CUtlVector<CDmxElement*>& pChildren = pTrack->GetArray<CDmxElement*>( "children" );
		if( pChildren.Count() == 0)
			return;
		CDmxElement* pChild = pChildren[0];
		if( pChild == NULL )
			return;
		m_pSelectedShot = pChild;
    }

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

	// Populate tree view
	KeyValues* kv = new KeyValues( "TVI" );
	kv->SetString("Text", m_pSelectedShot->GetName());
	kv->SetString( "Data", "" );
	kv->SetString( "Type", "animationsets" );
	kv->SetString( "UniqueId", "" );
	int rootIndex = m_pTree->AddItem( kv, -1 );

	// Add a tree view item for each animation set in m_pSelectedShot -> animationSets
	const CUtlVector<CDmxElement*>& pAnimationSets = m_pSelectedShot->GetArray<CDmxElement*>( "animationSets" );
	if( pAnimationSets.Count() == 0)
		return;
	for( int i = 0; i < pAnimationSets.Count(); i++ )
	{
		CDmxElement* pAnimationSet = pAnimationSets[i];
		if( pAnimationSet == NULL )
			continue;
		KeyValues* kv = new KeyValues( "TVI" );
		kv->SetString( "Text", pAnimationSet->GetName() );
		kv->SetString( "Data", "" );
		kv->SetString( "Type", "dag" );
		char uniqueId[40];
		UniqueIdToString(pAnimationSet->GetId(), uniqueId, 40);
		kv->SetString("UniqueId", uniqueId);

		// if animation set contains an attribute named "camera", "gameModel" or "particle system" then set its type to that
		int type = -1;
		if(pAnimationSet->AttributeCount() > 0)
		{
			for( int j = 0; j < pAnimationSet->AttributeCount(); j++ )
			{
				CDmxAttribute* pAttribute = pAnimationSet->GetAttribute( j );
				if( pAttribute == NULL )
					continue;
				if( Q_strcmp( pAttribute->GetName(), "camera" ) == 0 )
				{
					kv->SetString( "Type", "camera" );
					type = 1;
					break;
				}
				else if( Q_strcmp( pAttribute->GetName(), "gameModel" ) == 0 )
				{
					kv->SetString( "Type", "gameModel" );
					type = 0;
					break;
				}
				else if( Q_strcmp( pAttribute->GetName(), "particle system" ) == 0 )
				{
					kv->SetString( "Type", "particle system" );
					type = 2;
					break;
				}
				else if( Q_strcmp( pAttribute->GetName(), "light" ) == 0 )
				{
					kv->SetString( "Type", "light" );
					type = 3;
					break;
				}
			}
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
		CDmxElement* pRootControlGroup = pAnimationSet->GetValue<CDmxElement*>( "rootControlGroup" );
		if( pRootControlGroup == NULL )
			continue;
		const CUtlVector<CDmxElement*>& pChildren = pRootControlGroup->GetArray<CDmxElement*>( "children" );
		if( pChildren.Count() == 0 )
			continue;
		for( int j = 0; j < pChildren.Count(); j++ )
		{
			const char* pChildName = pChildren[j]->GetName();
			if( pChildName == NULL )
				continue;
			KeyValues* kv = new KeyValues( "TVI" );
			kv->SetString( "Text", pChildName );
			kv->SetString( "Data", "" );
			kv->SetString( "Type", "controlGroup" );
			UniqueIdToString(pChildren[j]->GetId(), uniqueId, 40);
			kv->SetString("UniqueId", uniqueId);
			int controlGroupIndex = m_pTree->AddItem( kv, animationSetIndex );
			// Add each pChildren[j] -> controls attribute
			const CUtlVector<CDmxElement*>& pControls = pChildren[j]->GetArray<CDmxElement*>( "controls" );
			if( pControls.Count() == 0 )
				continue;
			for( int k = 0; k < pControls.Count(); k++ )
			{
				const char* pControlName = pControls[k]->GetName();
				if( pControlName == NULL )
					continue;
				KeyValues* kv = new KeyValues( "TVI" );
				kv->SetString( "Text", pControlName );
				kv->SetString( "Data", "" );
				kv->SetString( "Type", "control" );
				UniqueIdToString(pControls[k]->GetId(), uniqueId, 40);
				kv->SetString("UniqueId", uniqueId);
				m_pTree->AddItem( kv, controlGroupIndex );
				// TODO: If type is "DmeTransformControl", add pos, x, y, z, rot, x, y, and z tree view items
			}
		}
	}
}
