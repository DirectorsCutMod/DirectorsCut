//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window controls for Director's Cut.
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dxeditorelementviewer.h"
#include "../directorscut.h"
#include "dmxloader/dmxattribute.h"
#include "dmxloader/dmxloader.h"

#undef GetCommandLine
#undef INVALID_HANDLE_VALUE
#undef ReadConsoleInput
#undef RegCreateKey
#undef RegCreateKeyEx
#undef RegOpenKey
#undef RegOpenKeyEx
#undef RegQueryValue
#undef RegQueryValueEx
#undef RegSetValue
#undef RegSetValueEx
#include <windows.h>

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

// This file is currently a mess but it works

#define TREE_TEXT_COLOR Color( 200, 255, 200, 255 )
#define LIST_TEXT_COLOR TREE_TEXT_COLOR

using namespace vgui;

DXEditorElementViewer::DXEditorElementViewer(Panel* pParent)
	: BaseClass(pParent, "Element Viewer")
{
    m_pSplitter = new Splitter(this, "DXEditorElementViewerSplitter", SPLITTER_MODE_HORIZONTAL, 1);
    float fractions[] = { 0.95f, 0.05f };
    m_pSplitter->RespaceSplitters(fractions);

    // Top view is the tree view
    m_pTree = new TreeView(m_pSplitter->GetChild(0), "DXEditorElementViewerTree");
    IScheme* pscheme = scheme()->GetIScheme(GetScheme());
    HFont treeFont = pscheme->GetFont("DefaultVerySmall");
    m_pTree->SetFont(treeFont);
    m_pTree->SetFgColor(TREE_TEXT_COLOR);

    // Bottom view is the property view
    // Store text entries, checkboxes, etc. for each property type to switch between
    m_pPropTextEntry = new TextEntry(m_pSplitter->GetChild(1), "DXEditorElementViewerPropTextEntry");
    m_pPropCheckButton = new CheckButton(m_pSplitter->GetChild(1), "DXEditorElementViewerPropCheckButton", "");
    m_pPropLabel = new Label(m_pSplitter->GetChild(1), "DXEditorElementViewerPropLabel", "");
    m_pColorPickerButton = new CColorPickerButton(m_pSplitter->GetChild(1), "DXEditorElementViewerPropColorPickerButton", this);
    m_pMakeRootButton = new Button(m_pSplitter->GetChild(1), "DXEditorElementViewerMakeRootButton", "Make Root");

    // Hide all property views
    m_pPropTextEntry->SetVisible(false);
    m_pPropCheckButton->SetVisible(false);
    m_pPropLabel->SetVisible(false);
    m_pColorPickerButton->SetVisible(false);
    m_pMakeRootButton->SetVisible(false);

    // Disable editing of properties
    //m_pPropTextEntry->SetEditable(false);
    //m_pPropCheckButton->SetCheckButtonCheckable(false);
    //m_pColorPickerButton->SetMouseClickEnabled(MOUSE_LEFT, false);

    // Actions
    m_pTree->AddActionSignalTarget(this);
    m_pPropTextEntry->AddActionSignalTarget(this);
    m_pPropCheckButton->AddActionSignalTarget(this);
    m_pColorPickerButton->AddActionSignalTarget(this);
    m_pMakeRootButton->AddActionSignalTarget(this);

    // Make ready for use
    m_pTree->MakeReadyForUse();
}

void DXEditorElementViewer::OnTreeViewItemSelected()
{
    //DECLARE_DMX_CONTEXT_NODECOMMIT();
    // Set appropriate property view
    int itemIndex = m_pTree->GetFirstSelectedItem();
    if (itemIndex == -1)
    {
        Msg("Error: No tree view item selected.\n");
        return;
    }
    
    KeyValues* kv = m_pTree->GetItemData(itemIndex);
    if (kv == NULL)
    {
        Msg("Error: Tree view item has no data.\n");
        return;
    }

    const char* pszType = kv->GetString("Type");

    // Hide all property views
    m_pPropTextEntry->SetVisible(false);
    m_pPropCheckButton->SetVisible(false);
    m_pPropLabel->SetVisible(false);
    m_pColorPickerButton->SetVisible(false);
    m_pMakeRootButton->SetVisible(false);

    // Show appropriate property view
    if (Q_strcmp(pszType, "string") == 0)
    {
        m_pPropTextEntry->SetVisible(true);
        m_pPropTextEntry->SetText(kv->GetString("Data"));
        m_pPropTextEntry->GotoTextEnd();
    }
    else if (Q_strcmp(pszType, "int") == 0)
    {
        m_pPropTextEntry->SetVisible(true);
        m_pPropTextEntry->SetText(kv->GetString("Data"));
        m_pPropTextEntry->GotoTextEnd();
    }
    else if (Q_strcmp(pszType, "float") == 0)
    {
        m_pPropTextEntry->SetVisible(true);
        m_pPropTextEntry->SetText(kv->GetString("Data"));
        m_pPropTextEntry->GotoTextEnd();
    }
    else if (Q_strcmp(pszType, "bool") == 0)
    {
        m_pPropCheckButton->SetVisible(true);
        m_pPropCheckButton->SetEnabled(true);
        m_pPropCheckButton->SetSelected(Q_strcmp(kv->GetString("Data"), "true") == 0);
        m_pPropCheckButton->SetText(kv->GetString("Text"));
    }
    else if (Q_strcmp(pszType, "color") == 0)
    {
        m_pColorPickerButton->SetVisible(true);
        Color clr;
        clr.SetRawColor(atoi(kv->GetString("Data")));
        m_pColorPickerButton->SetColor(clr);
        m_pColorPickerButton->SetEnabled(true);
    }
    // arrays
    else if (Q_strcmp(pszType, "int_array") == 0)
    {
        m_pPropTextEntry->SetVisible(true);
        m_pPropTextEntry->SetText(kv->GetString("Data"));
        m_pPropTextEntry->GotoTextEnd();
    }
    else if (Q_strcmp(pszType, "float_array") == 0)
    {
        m_pPropTextEntry->SetVisible(true);
        m_pPropTextEntry->SetText(kv->GetString("Data"));
        m_pPropTextEntry->GotoTextEnd();
    }
    else if (Q_strcmp(pszType, "bool_array") == 0)
    {
        m_pPropTextEntry->SetVisible(true);
        m_pPropTextEntry->SetText(kv->GetString("Data"));
        m_pPropTextEntry->GotoTextEnd();
    }
    else if (Q_strcmp(pszType, "color_array") == 0)
    {
        m_pPropTextEntry->SetVisible(true);
        m_pPropTextEntry->SetText(kv->GetString("Data"));
        m_pPropTextEntry->GotoTextEnd();
    }
    // selecting elements will make them the root element
    else if (Q_strcmp(pszType, "element") == 0)
    {
        m_pMakeRootButton->SetVisible(true);
    }
    else
    {
        // Show label to indicate that this property cannot be edited
        m_pPropLabel->SetVisible(true);
        m_pPropLabel->SetText("This property cannot be edited.");
        m_pPropLabel->SetContentAlignment(Label::a_center);
    }
}

void DXEditorElementViewer::RecursivePopulateTreeFromDocument( CDmxElement* pElement, int parentIndex )
{
    //DECLARE_DMX_CONTEXT_NODECOMMIT();
    if( pElement == NULL)
    {
        // Find root element
        CDmxElement* pRoot = DirectorsCutGameSystem().GetDocumentFocusedRoot();
        if (pRoot == NULL)
            pRoot = DirectorsCutGameSystem().GetDocument();

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

        m_pSplitter->InvalidateLayout(true);
        float fractions[] = { 0.95f, 0.05f };
        m_pSplitter->RespaceSplitters(fractions);

        // Clear properties
        m_pPropTextEntry->SetVisible(false);
        m_pPropCheckButton->SetVisible(false);
        m_pPropLabel->SetVisible(false);
        m_pColorPickerButton->SetVisible(false);
        m_pMakeRootButton->SetVisible(false);
        
        if( pRoot == NULL)
        {
            //Msg("No document loaded.\n");
            return;
        }

        // Populate tree view
        KeyValues* kv = new KeyValues( "TVI" );
        kv->SetString("Text", pRoot->GetName());
        kv->SetString( "Data", "" );
        kv->SetString( "Type", "element" );
        char uniqueId[40];
        UniqueIdToString( pRoot->GetId(), uniqueId, 40 );
        kv->SetString( "UniqueId", uniqueId );
        int rootIndex = m_pTree->AddItem( kv, -1 );
        RecursivePopulateTreeFromDocument( pRoot, rootIndex );
    }
    else
    {
        // Add attributes
        for (int i = 0; i < pElement->AttributeCount(); i++)
        {
            //DECLARE_DMX_CONTEXT_NODECOMMIT();
            int index = -1;
            CDmxAttribute* pCur = pElement->GetAttribute(i);
            CDmxElement* subElem = NULL;
            KeyValues* kv = new KeyValues("TVI");
            kv->SetString("UniqueId", "");
            kv->SetString("Text", pCur->GetName());
            kv->SetString("Type", "unknown");
            kv->SetString("Data", "");
            char* pszData = new char[32];
            switch (pCur->GetType())
            {
            case AT_ELEMENT:
                subElem = pCur->GetValue<CDmxElement*>();
                char uniqueId[40];
                UniqueIdToString(subElem->GetId(), uniqueId, 40);
                kv->SetString("UniqueId", uniqueId);
                kv->SetString("Type", "element");
                index = m_pTree->AddItem(kv, parentIndex);
                /*
                if (subElem != NULL)
                    RecursivePopulateTreeFromDocument(subElem, index);
                */
                break;
            case AT_STRING:
                kv->SetString("Type", "string");
                kv->SetString("Data", pCur->GetValue<CUtlString>().Get());
                index = m_pTree->AddItem(kv, parentIndex);
                break;
            case AT_INT:
                kv->SetString("Type", "int");
                Q_snprintf(pszData, 32, "%i", pCur->GetValue<int>());
                kv->SetString("Data", pszData);
                index = m_pTree->AddItem(kv, parentIndex);
                break;
            case AT_FLOAT:
                kv->SetString("Type", "float");
                Q_snprintf(pszData, 32, "%f", pCur->GetValue<float>());
                kv->SetString("Data", pszData);
                index = m_pTree->AddItem(kv, parentIndex);
                break;
            case AT_BOOL:
                kv->SetString("Type", "bool");
                kv->SetString("Data", pCur->GetValue<bool>() ? "true" : "false");
                index = m_pTree->AddItem(kv, parentIndex);
                break;
            case AT_COLOR:
                kv->SetString("Type", "color");
                Q_snprintf(pszData, 32, "%i", pCur->GetValue<Color>().GetRawColor());
                kv->SetString("Data", pszData);
                index = m_pTree->AddItem(kv, parentIndex);
                break;
            case AT_ELEMENT_ARRAY:
                kv->SetString("Type", "element_array");
                Q_snprintf(pszData, 32, "%i item%s", pCur->GetArrayCount(), pCur->GetArrayCount() == 1 ? "" : "s");
                kv->SetString("Data", pszData);
                index = m_pTree->AddItem(kv, parentIndex);
                if (pCur->GetArrayCount() > 0)
                {
                    for (int j = 0; j < pCur->GetArrayCount(); j++)
                    {
                        CDmxElement* subElem = pCur->GetArray<CDmxElement*>()[j];
                        kv = new KeyValues("TVI");
                        char uniqueId[40];
                        UniqueIdToString(subElem->GetId(), uniqueId, 40);
                        kv->SetString("UniqueId", uniqueId);
                        kv->SetString("Text", subElem->GetName());
                        kv->SetString("Type", "element");
                        kv->SetString("Data", "");
                        m_pTree->AddItem(kv, index);
                        //RecursivePopulateTreeFromDocument(subElem, subIndex);
                    }
                }
                break;
            case AT_INT_ARRAY:
                kv->SetString("Type", "int_array");
                for (int j = 0; j < pCur->GetArrayCount(); j++)
                {
                    Q_snprintf(pszData, 256, "%s%i", j == 0 ? "" : ", ", pCur->GetArray<int>()[j]);
                }
                kv->SetString("Data", pszData);
                index = m_pTree->AddItem(kv, parentIndex);
                break;
            case AT_FLOAT_ARRAY:
                kv->SetString("Type", "float_array");
                for (int j = 0; j < pCur->GetArrayCount(); j++)
                {
                    Q_snprintf(pszData, 256, "%s%f", j == 0 ? "" : ", ", pCur->GetArray<float>()[j]);
                }
                kv->SetString("Data", pszData);
                index = m_pTree->AddItem(kv, parentIndex);
                break;
            case AT_BOOL_ARRAY:
                kv->SetString("Type", "bool_array");
                for (int j = 0; j < pCur->GetArrayCount(); j++)
                {
                    Q_snprintf(pszData, 256, "%s%s", j == 0 ? "" : ", ", pCur->GetArray<bool>()[j] ? "true" : "false");
                }
                kv->SetString("Data", pszData);
                index = m_pTree->AddItem(kv, parentIndex);
                break;
            case AT_COLOR_ARRAY:
                kv->SetString("Type", "color_array");
                for (int j = 0; j < pCur->GetArrayCount(); j++)
                {
                    Q_snprintf(pszData, 256, "%s%i", j == 0 ? "" : ", ", pCur->GetArray<Color>()[j].GetRawColor());
                }
                kv->SetString("Data", pszData);
                index = m_pTree->AddItem(kv, parentIndex);
                break;
            }
            if(index == -1)
            {
                // Add anyways
                index = m_pTree->AddItem(kv, parentIndex);
            }
        }
    }
}

void DXEditorElementViewer::MakeRootButtonClick()
{
    // Set root element
    int itemIndex = m_pTree->GetFirstSelectedItem();
    if (itemIndex == -1)
    {
		Msg("Error: No tree view item selected.\n");
		return;
	}

    // If pRoot's uniqueId is the same as the one we're trying to set, then set to the root document
    if (itemIndex == m_pTree->GetRootItemIndex())
    {
        // Set new root
        DirectorsCutGameSystem().SetDocumentFocusedRoot(NULL);
        DirectorsCutGameSystem().SetNeedsUpdate(true);
        return;
    }

    KeyValues* kv = m_pTree->GetItemData(itemIndex);
    if (kv == NULL)
    {
        Msg("Error: Tree view item has no data.\n");
    }

    // Get uniqueid
    const char* uniqueIdStr = kv->GetString("UniqueId");
    UniqueId_t uniqueId_t;
    bool failure = UuidFromString((unsigned char*)uniqueIdStr, (UUID*)&uniqueId_t);

    if (failure)
    {
        Msg("Error: Could not convert uniqueId %s to UniqueId_t.\n", uniqueIdStr);
        return;
    }

    // Loop through attributes
    CDmxElement* pRoot = DirectorsCutGameSystem().GetDocumentFocusedRoot();
    if (pRoot == NULL)
        pRoot = DirectorsCutGameSystem().GetDocument();
    if (pRoot == NULL)
    {
        Msg("No document loaded.\n");
        return;
    }

    // Set root element
    CDmxElement* pNewRoot = NULL;
    for (int i = 0; i < pRoot->AttributeCount(); i++)
    {
        CDmxAttribute* pCur = pRoot->GetAttribute(i);
        if (pCur->GetType() == AT_ELEMENT)
        {
            CDmxElement* subElem = pCur->GetValue<CDmxElement*>();
            if (subElem != NULL)
            {
                if (subElem->GetId() == uniqueId_t)
                {
                    // Found it, set as new root
                    pNewRoot = subElem;
                    break;
                }
            }
        }
        else if (pCur->GetType() == AT_ELEMENT_ARRAY)
        {
            const CUtlVector<CDmxElement*>& subElemArray = pCur->GetArray<CDmxElement*>();
            for (int j = 0; j < subElemArray.Count(); j++)
            {
                CDmxElement* subElem = subElemArray[j];
                if (subElem != NULL)
                {
                    if (subElem->GetId() == uniqueId_t)
                    {
                        // Found it, set as new root
                        pNewRoot = subElem;
                        break;
                    }
                }
            }
        }
    }

    // Set new root
    DirectorsCutGameSystem().SetDocumentFocusedRoot(pNewRoot);
    DirectorsCutGameSystem().SetNeedsUpdate(true);
}

void DXEditorElementViewer::OnThink()
{
    //DECLARE_DMX_CONTEXT_NODECOMMIT();
    
    // Root button click
    if (m_pMakeRootButton->IsVisible() && m_pMakeRootButton->IsSelected())
    {
        m_pMakeRootButton->SetSelected(false);
        MakeRootButtonClick();
    }

    // Check to see if properties had changed from the tree view data
    int itemIndex = m_pTree->GetFirstSelectedItem();
    if (itemIndex != -1)
    {
        KeyValues* kv = m_pTree->GetItemData(itemIndex);
        if (kv != NULL)
        {
            const char* pszType = kv->GetString("Type");
            if (Q_strcmp(pszType, "string") == 0
                || Q_strcmp(pszType, "int") == 0
                || Q_strcmp(pszType, "float") == 0
                || Q_strcmp(pszType, "int_array") == 0
                || Q_strcmp(pszType, "float_array") == 0
                || Q_strcmp(pszType, "bool_array") == 0
                || Q_strcmp(pszType, "color_array") == 0)
            {
                // Check to see if the property has changed
                char pszTextEntry[256];
                m_pPropTextEntry->GetText(pszTextEntry, 256);
                if (Q_strcmp(pszTextEntry, kv->GetString("Data")) != 0)
                {
                    // Update property
                    kv->SetString("Data", pszTextEntry);
                    const char* pszText = kv->GetString("Text");
                    Msg("Updating %s to %s\n", pszText, pszTextEntry);
                    CDmxElement* pRoot = DirectorsCutGameSystem().GetDocumentFocusedRoot();
                    if (pRoot == NULL)
                        pRoot = DirectorsCutGameSystem().GetDocument();
                    if (pRoot == NULL)
                    {
                        Msg("No document loaded.\n");
                        return;
                    }
                    if (Q_strcmp(pszType, "string") == 0)
                    {
                        pRoot->SetValue<CUtlString>(pszText, pszTextEntry);
                    }
                    else if (Q_strcmp(pszType, "int") == 0)
                    {
                        pRoot->SetValue<int>(pszText, atoi(pszTextEntry));
                    }
                    else if (Q_strcmp(pszType, "float") == 0)
                    {
                        pRoot->SetValue<float>(pszText, atof(pszTextEntry));
                    }
                    // arrays are comma separated
                    else if (Q_strcmp(pszType, "int_array") == 0)
                    {
                        CUtlVector<int> intArray;
                        char* pszToken = strtok(pszTextEntry, ",");
                        while (pszToken != NULL)
                        {
                            intArray.AddToTail(atoi(pszToken));
                            pszToken = strtok(NULL, ",");
                        }
                        pRoot->GetAttribute(pszText)->GetArrayForEdit<int>().RemoveAll();
                        for (int i = 0; i < intArray.Count(); i++)
                        {
                            pRoot->GetAttribute(pszText)->GetArrayForEdit<int>().AddToTail(intArray[i]);
						}
                    }
                    else if (Q_strcmp(pszType, "float_array") == 0)
                    {
                        CUtlVector<float> floatArray;
                        char* pszToken = strtok(pszTextEntry, ",");
                        while (pszToken != NULL)
                        {
                            floatArray.AddToTail(atof(pszToken));
                            pszToken = strtok(NULL, ",");
                        }
                        pRoot->GetAttribute(pszText)->GetArrayForEdit<float>().RemoveAll();
                        for (int i = 0; i < floatArray.Count(); i++)
                        {
                            pRoot->GetAttribute(pszText)->GetArrayForEdit<float>().AddToTail(floatArray[i]);
                        }
                    }
                    else if (Q_strcmp(pszType, "bool_array") == 0)
                    {
                        CUtlVector<bool> boolArray;
                        char* pszToken = strtok(pszTextEntry, ",");
                        while (pszToken != NULL)
                        {
                            boolArray.AddToTail(Q_strcmp(pszToken, "true") == 0);
                            pszToken = strtok(NULL, ",");
                        }
                        pRoot->GetAttribute(pszText)->GetArrayForEdit<bool>().RemoveAll();
                        for (int i = 0; i < boolArray.Count(); i++)
                        {
                            pRoot->GetAttribute(pszText)->GetArrayForEdit<bool>().AddToTail(boolArray[i]);
                        }
                    }
                    else if (Q_strcmp(pszType, "color_array") == 0)
                    {
                        CUtlVector<Color> colorArray;
                        char* pszToken = strtok(pszTextEntry, ",");
                        while (pszToken != NULL)
                        {
                            int rawColor = atoi(pszToken);
                            Color clr;
                            clr.SetRawColor(rawColor);
                            colorArray.AddToTail(clr);
                            pszToken = strtok(NULL, ",");
                        }
                        pRoot->GetAttribute(pszText)->GetArrayForEdit<Color>().RemoveAll();
                        for (int i = 0; i < colorArray.Count(); i++)
                        {
                            pRoot->GetAttribute(pszText)->GetArrayForEdit<Color>().AddToTail(colorArray[i]);
                        }
                    }
                    DirectorsCutGameSystem().SetNeedsUpdate(true);
                }
            }
            else if (Q_strcmp(pszType, "bool") == 0)
            {
                // Check to see if the property has changed
                bool bSelected = m_pPropCheckButton->IsSelected();
                if (Q_strcmp(bSelected ? "true" : "false", kv->GetString("Data")) != 0)
                {
                    // Update property
                    kv->SetString("Data", bSelected ? "true" : "false");
                    const char* pszText = kv->GetString("Text");
                    Msg("Updating %s to %s\n", pszText, bSelected ? "true" : "false");
                    CDmxElement* pRoot = DirectorsCutGameSystem().GetDocumentFocusedRoot();
                    if (pRoot == NULL)
                        pRoot = DirectorsCutGameSystem().GetDocument();
                    if (pRoot == NULL)
                    {
                        Msg("No document loaded.\n");
                        return;
                    }
                    pRoot->SetValue<bool>(pszText, bSelected);
                    DirectorsCutGameSystem().SetNeedsUpdate(true);
                }
            }
            else if (Q_strcmp(pszType, "color") == 0)
            {
                // Check to see if the property has changed
                Color clr = m_pColorPickerButton->GetColor();
                char pszTextEntry[256];
                Q_snprintf(pszTextEntry, 256, "%i", clr.GetRawColor());
                if (Q_strcmp(pszTextEntry, kv->GetString("Data")) != 0)
                {
                    // Update property
                    const char* pszText = kv->GetString("Text");
                    Msg("Updating %s from %s to %s\n", pszText, kv->GetString("Data"), pszTextEntry);
                    kv->SetString("Data", pszTextEntry);
                    CDmxElement* pRoot = DirectorsCutGameSystem().GetDocumentFocusedRoot();
                    if (pRoot == NULL)
                        pRoot = DirectorsCutGameSystem().GetDocument();
                    if (pRoot == NULL)
                    {
                        Msg("No document loaded.\n");
                        return;
                    }
                    pRoot->SetValue<Color>(pszText, clr);
                    DirectorsCutGameSystem().SetNeedsUpdate(true);
                }
            }
        }
    }

    if(DirectorsCutGameSystem().NeedsUpdate() == true)
    {
        Msg("Updating element viewer...\n");
        DirectorsCutGameSystem().SetNeedsUpdate(false);
        RecursivePopulateTreeFromDocument(NULL, -1);
        // Expand all items
        CUtlVector <int> expandedItems;
        for (int i = 0; i < m_pTree->GetItemCount(); i++)
        {
            expandedItems.AddToTail(i);
        }
        m_pTree->ExpandItem(m_pTree->GetRootItemIndex(), true);
        // Find previously selected item and select it again
        for (int i = 0; i < m_pTree->GetItemCount(); i++)
        {
            KeyValues* kv = m_pTree->GetItemData(i);
            if (kv != NULL)
            {
                const char* pszText = kv->GetString("Text");
                if (Q_strcmp(pszText, m_selectedElement) == 0)
                {
                    m_pTree->AddSelectedItem(i, true, false, true);
                    break;
                }
            }
        }
    }

    int x, y, w, h;
    GetBounds(x, y, w, h);
	y -= 27; // I'm not sure why, but there's an offset here for some reason
    m_pSplitter->SetBounds(x, y, w, h);

    m_pSplitter->GetChild(0)->GetBounds(x, y, w, h);
    m_pTree->SetBounds(0, 0, w, h);

    // Extend properties to use all available space
    m_pSplitter->GetChild(1)->GetBounds(x, y, w, h);
    m_pPropTextEntry->SetBounds(0, 0, w, h);
    m_pPropCheckButton->SetBounds(0, 0, w, h);
    m_pPropLabel->SetBounds(0, 0, w, h);
    m_pColorPickerButton->SetBounds(0, 0, w, h);
    m_pMakeRootButton->SetBounds(0, 0, w, h);
}

void DXEditorElementViewer::ApplySchemeSettings(IScheme *pScheme)
{
	BaseClass::ApplySchemeSettings(pScheme);

    // Dummy tree view
	HFont treeFont = pScheme->GetFont( "DefaultVerySmall" );
	m_pTree->SetFont( treeFont );
}