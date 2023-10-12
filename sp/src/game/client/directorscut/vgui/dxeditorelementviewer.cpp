//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window controls for Director's Cut.
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dxeditorelementviewer.h"

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

#define TREE_TEXT_COLOR Color( 200, 255, 200, 255 )
#define LIST_TEXT_COLOR TREE_TEXT_COLOR

using namespace vgui;

DXEditorElementViewer::DXEditorElementViewer(Panel* pParent)
	: BaseClass(pParent, "Element Viewer")
{
    // Buttons: Back, Forward, Up, Refresh
    m_pBackButton = new Button(this, "DXEditorElementViewerBackButton", "<-");
    m_pForwardButton = new Button(this, "DXEditorElementViewerForwardButton", "->");
    m_pUpButton = new Button(this, "DXEditorElementViewerUpButton", "^");
    m_pRefreshButton = new Button(this, "DXEditorElementViewerRefreshButton", "R");
    
    // Dummy tree view
    m_pTree = new TreeView(this, "DXEditorElementViewerTree");
    IScheme* pscheme = scheme()->GetIScheme(GetScheme());
    HFont treeFont = pscheme->GetFont("DefaultVerySmall");
    m_pTree->SetFont(treeFont);
    m_pTree->SetFgColor(TREE_TEXT_COLOR);

    // Populate tree view
    KeyValues* kv = new KeyValues("TVI");
    kv->SetString("Text", "session");
    kv->SetString("Data", "DmElement");
    kv->SetString("Type", "element");
    int rootIndex = m_pTree->AddItem(kv, -1);

    // Dummy items
    kv = new KeyValues("TVI");
    kv->SetString("Text", "name");
    kv->SetString("Data", "session");
    kv->SetString("Type", "string");
    m_pTree->AddItem(kv, rootIndex);

    kv = new KeyValues("TVI");
    kv->SetString("Text", "activeClip");
    kv->SetString("Data", "DmeFilmClip");
    kv->SetString("Type", "element");
    int filmClip = m_pTree->AddItem(kv, rootIndex);
    
    kv = new KeyValues("TVI");
    kv->SetString("Text", "name");
    kv->SetString("Data", "session");
    kv->SetString("Type", "string");
    m_pTree->AddItem(kv, filmClip);

    kv = new KeyValues("TVI");
    kv->SetString("Text", "miscBin");
    kv->SetString("Data", "0 items");
    kv->SetString("Type", "element_array");
    m_pTree->AddItem(kv, rootIndex);

    kv = new KeyValues("TVI");
    kv->SetString("Text", "cameraBin");
    kv->SetString("Data", "0 items");
    kv->SetString("Type", "element_array");
    m_pTree->AddItem(kv, rootIndex);

    kv = new KeyValues("TVI");
    kv->SetString("Text", "clipBin");
    kv->SetString("Data", "1 item");
    kv->SetString("Type", "element_array");
    int clipBin = m_pTree->AddItem(kv, rootIndex);

    kv = new KeyValues("TVI");
    kv->SetString("Text", "session");
    kv->SetString("Data", "DmeFilmClip");
    kv->SetString("Type", "element");
    m_pTree->AddItem(kv, clipBin);

    kv = new KeyValues("TVI");
    kv->SetString("Text", "settings");
    kv->SetString("Data", "DmElement");
    kv->SetString("Type", "element");
    int settings = m_pTree->AddItem(kv, rootIndex);

    kv = new KeyValues("TVI");
    kv->SetString("Text", "name");
    kv->SetString("Data", "sessionSettings");
    kv->SetString("Type", "string");
    m_pTree->AddItem(kv, settings);

    m_pTree->ExpandItem(rootIndex, true);

    // Make ready for use
    m_pTree->MakeReadyForUse();
    
    // Dummy list view
    m_pList = new ListPanel( this, "DXEditorElementViewerList" );
    m_pList->AddColumnHeader( 0, "Data", "Data", 150, ListPanel::COLUMN_RESIZEWITHWINDOW );
    m_pList->AddColumnHeader( 1, "Type", "Type", 150, ListPanel::COLUMN_RESIZEWITHWINDOW );

    // Set list view font and color
    IScheme* pScheme = scheme()->GetIScheme(GetScheme());
    m_pList->SetFont( pScheme->GetFont( "DefaultVerySmall" ) );
    m_pList->SetFgColor( LIST_TEXT_COLOR );
}

void DXEditorElementViewer::RecursivePopulateListFromTree( int current, CUtlVector< KeyValues* >& items )
{
    if( current == -1 )
    {
        current = m_pTree->GetRootItemIndex();
    }

    // Add current item to list
    KeyValues* kv = new KeyValues( "LI" );
    kv->SetString( "Data", m_pTree->GetItemData( current )->GetString( "Data" ) );
    kv->SetString( "Type", m_pTree->GetItemData( current )->GetString( "Type" ) );
    items.AddToTail( kv );

    // Recurse through children if expanded
    if( m_pTree->IsItemExpanded( current ) )
    {
        for( int i = 0; i < m_pTree->GetNumChildren( current ); i++ )
        {
            RecursivePopulateListFromTree( m_pTree->GetChild( current, i ), items );
        }
    }
}

void DXEditorElementViewer::OnTreeViewItemSelected()
{
    //OnViewItemSelected();
}

void DXEditorElementViewer::OnItemSelected()
{
    //OnViewItemSelected();
    // Select item in tree view
    int selected = m_pList->GetSelectedItem(0);
    m_pTree->AddSelectedItem(selected, true);
}

void DXEditorElementViewer::OnViewItemSelected()
{
    // Re-populate list view
    CUtlVector< KeyValues* > items;
    RecursivePopulateListFromTree( -1, items );

    // Clear list view
    m_pList->DeleteAllItems();

    // Add items to list view
    for( int i = 0; i < items.Count(); i++ )
    {
        m_pList->AddItem( items[i], 0, false, false );
    }

    // Select what the tree view has selected
    CUtlVector< int > selected;
    m_pTree->GetSelectedItems( selected );
    if (selected.Count() > 0)
    {
		m_pList->AddSelectedItem( selected[0] );
	}
}

void DXEditorElementViewer::OnThink()
{
    OnViewItemSelected();

    int x, y, w, h;
    GetBounds(x, y, w, h);

    // Extend views to fill the entire panel on each side with offset for buttons
    m_pTree->SetBounds(0, m_pBackButton->GetTall(), w / 2, h - m_pBackButton->GetTall());
    m_pList->SetBounds(w / 2, m_pBackButton->GetTall() - 20, w / 2, h - m_pBackButton->GetTall() + 20); // 20px offset so list lines up with tree

    // Order buttons in x space available
    int buttonWidth = w / 8;
    m_pBackButton->SetBounds(0, 0, buttonWidth, m_pBackButton->GetTall());
    m_pForwardButton->SetBounds(buttonWidth, 0, buttonWidth, m_pForwardButton->GetTall());
    m_pUpButton->SetBounds(buttonWidth * 2, 0, buttonWidth, m_pUpButton->GetTall());
    m_pRefreshButton->SetBounds(buttonWidth * 3, 0, buttonWidth, m_pRefreshButton->GetTall());

    // Update views
    m_pTree->InvalidateLayout();
    m_pList->InvalidateLayout();
}

void DXEditorElementViewer::ApplySchemeSettings(IScheme *pScheme)
{
	BaseClass::ApplySchemeSettings(pScheme);

    // Dummy tree view
	HFont treeFont = pScheme->GetFont( "DefaultVerySmall" );
	m_pTree->SetFont( treeFont );

    // Dummy list view
    HFont listFont = pScheme->GetFont( "DefaultVerySmall" );
    m_pList->SetFont( listFont );
}