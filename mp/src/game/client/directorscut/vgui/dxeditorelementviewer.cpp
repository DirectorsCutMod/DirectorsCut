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
#include "dxeditorproperties.h"

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
// TODO: Move property editing to properties window and standardize how we wanna handle attributes
// TODO: Do we need a tree view? It's only ever used for arrays and elements, unlike the animation set editor

#define TREE_TEXT_COLOR Color( 200, 255, 200, 255 )
#define LIST_TEXT_COLOR TREE_TEXT_COLOR

using namespace vgui;

DXEditorElementViewer::DXEditorElementViewer(Panel* pParent)
	: BaseClass(pParent, "Element Viewer")
{
    //pSplitter = new Splitter(this, "DXEditorElementViewerSplitter", SPLITTER_MODE_HORIZONTAL, 1);
    //float fractions[] = { 0.95f, 0.05f };
    //pSplitter->RespaceSplitters(fractions);

    // Top view is the tree view
    m_pTree = new TreeView(this, "DXEditorElementViewerTree");
    IScheme* pscheme = scheme()->GetIScheme(GetScheme());
    HFont treeFont = pscheme->GetFont("DefaultVerySmall");
    m_pTree->SetFont(treeFont);
    m_pTree->SetFgColor(TREE_TEXT_COLOR);

    // Make ready for use
    m_pTree->MakeReadyForUse();
}

void DXEditorElementViewer::SetupProperties(bool reset)
{
    DXEditorProperties* pProperties = GetDXEditorProperties();
    if (pProperties == NULL)
    {
        Msg("Error: Could not get properties window.\n");
        return;
    }

    Splitter* pSplitter = pProperties->GetSplitter();
    if (pSplitter == NULL
        || pSplitter->GetChildCount() < 2
        || pSplitter->GetChild(0) == NULL
        || pSplitter->GetChild(1) == NULL)
    {
        Msg("Error: Could not get splitter.\n");
        return;
    }

    pProperties->ResetPanels(false);

    // Left view is the preview
    // Just show the name and type of the element for now
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
    const char* pszText = kv->GetString("Text");
    const char* pszType = kv->GetString("Type");
    const char* pszUniqueId = kv->GetString("UniqueId");
    const char* pszData = kv->GetString("Data");

    // TODO: nullptr exception!!!
    if (pPreviewLabel == nullptr
        || m_pPropTextEntry == nullptr
        || m_pPropCheckButton == nullptr
        || m_pPropLabel == nullptr
        || m_pColorPickerButton == nullptr
        || m_pMakeRootButton == nullptr)
    {
        if (!reset)
        {
            Msg("Warning: Could not get property controls. Resetting.\n");
            reset = true;
        }
        else
        {
            Msg("Error: Could not get property controls.\n");
            return;
        }
    }

    // Right view is the property view
    // Store text entries, checkboxes, etc. for each property type to switch between
    if(reset)
    {
        m_pPropTextEntry = new TextEntry(pSplitter->GetChild(1), "DXEditorElementViewerPropTextEntry");
        m_pPropCheckButton = new CheckButton(pSplitter->GetChild(1), "DXEditorElementViewerPropCheckButton", "");
        m_pPropLabel = new RichText(pSplitter->GetChild(1), "DXEditorElementViewerPropLabel");
        m_pColorPickerButton = new CColorPickerButton(pSplitter->GetChild(1), "DXEditorElementViewerPropColorPickerButton", this);
        m_pMakeRootButton = new Button(pSplitter->GetChild(1), "DXEditorElementViewerMakeRootButton", "Make Root");
        pPreviewLabel = new RichText(pSplitter->GetChild(0), "DXEditorElementViewerPreviewLabel");

        // Hide all property views
        m_pPropTextEntry->SetVisible(false);
        m_pPropCheckButton->SetVisible(false);
        m_pPropLabel->SetVisible(false);
        m_pColorPickerButton->SetVisible(false);
        m_pMakeRootButton->SetVisible(false);
        pPreviewLabel->SetVisible(true);
    }

    char* pszPreviewText = new char[256];
    Q_snprintf(pszPreviewText, 256, "Name: %s\nType: %s\nUnique ID: %s\nData: %s", pszText, pszType, pszUniqueId, pszData);
    pPreviewLabel->SetText(pszPreviewText);

    // Disable editing of properties
    //m_pPropTextEntry->SetEditable(false);
    //m_pPropCheckButton->SetCheckButtonCheckable(false);
    //m_pColorPickerButton->SetMouseClickEnabled(MOUSE_LEFT, false);

    // Actions
    if(reset)
    {
        m_pTree->AddActionSignalTarget(this);
        m_pPropTextEntry->AddActionSignalTarget(this);
        m_pPropCheckButton->AddActionSignalTarget(this);
        m_pColorPickerButton->AddActionSignalTarget(this);
        m_pMakeRootButton->AddActionSignalTarget(this);
    }

    //pProperties->InvalidateLayout(true);
}

void DXEditorElementViewer::OnTreeViewItemSelected()
{
    //DECLARE_DMX_CONTEXT_NODECOMMIT();
    // Set appropriate property view
    int itemIndex = m_pTree->GetFirstSelectedItem();
    if (itemIndex == -1)
    {
        //Msg("Error: No tree view item selected.\n");
        return;
    }
    
    KeyValues* kv = m_pTree->GetItemData(itemIndex);
    if (kv == NULL)
    {
        //Msg("Error: Tree view item has no data.\n");
        return;
    }
    
    // Double click
    if(lastSelectedIndex == itemIndex)
    {
        double curTime = system()->GetFrameTime();
        if (m_bCanDoubleClick)
        {
            if (curTime - lastClickTime < 0.5)
            {
                // Double click
                MakeRootButtonClick();
            }
        }
        else
        {
            m_bCanDoubleClick = true;
        }
        lastClickTime = curTime;
    }
    else
    {
        lastSelectedIndex = itemIndex;
        m_bCanDoubleClick = false;
    }

    const char* pszType = kv->GetString("Type");

    SetupProperties(false);

    if(m_pPropTextEntry == NULL
        || m_pPropCheckButton == NULL
        || m_pPropLabel == NULL
        || m_pColorPickerButton == NULL
        || m_pMakeRootButton == NULL)
    {
        Msg("Error: Could not get property controls.\n");
        return;
    }

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
        m_pPropLabel->SetText("Unsupported type.");
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

        DXEditorProperties* pProperties = GetDXEditorProperties();
        if (pProperties == NULL)
        {
            //Msg("Error: Could not get properties window.\n");
            return;
        }
        pProperties->ResetPanels(false);
        
        if( pRoot == NULL)
        {
            ////Msg("No document loaded.\n");
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
        m_pTree->SetItemFgColor( rootIndex, Color( 0, 128, 255, 255 ) );
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
            Color col = Color(0, 0, 0, 255);
            switch (pCur->GetType())
            {
            case AT_ELEMENT:
                subElem = pCur->GetValue<CDmxElement*>();
                char uniqueId[40];
                UniqueIdToString(subElem->GetId(), uniqueId, 40);
                kv->SetString("UniqueId", uniqueId);
                kv->SetString("Type", "element");
                index = m_pTree->AddItem(kv, parentIndex);
                m_pTree->SetItemFgColor(index, Color(0, 128, 255, 255));
                /*
                if (subElem != NULL)
                    RecursivePopulateTreeFromDocument(subElem, index);
                */
                break;
            case AT_STRING:
                kv->SetString("Type", "string");
                kv->SetString("Data", pCur->GetValue<CUtlString>().Get());
                index = m_pTree->AddItem(kv, parentIndex);
                m_pTree->SetItemFgColor(index, Color(255, 255, 0, 255));
                break;
            case AT_INT:
                kv->SetString("Type", "int");
                Q_snprintf(pszData, 32, "%i", pCur->GetValue<int>());
                kv->SetString("Data", pszData);
                index = m_pTree->AddItem(kv, parentIndex);
                m_pTree->SetItemFgColor(index, Color(255, 0, 0, 255));
                break;
            case AT_FLOAT:
                kv->SetString("Type", "float");
                Q_snprintf(pszData, 32, "%f", pCur->GetValue<float>());
                kv->SetString("Data", pszData);
                index = m_pTree->AddItem(kv, parentIndex);
                m_pTree->SetItemFgColor(index, Color(0, 255, 0, 255));
                break;
            case AT_BOOL:
                kv->SetString("Type", "bool");
                kv->SetString("Data", pCur->GetValue<bool>() ? "true" : "false");
                index = m_pTree->AddItem(kv, parentIndex);
                m_pTree->SetItemFgColor(index, Color(0, 255, 0, 255));
                break;
            case AT_COLOR:
                kv->SetString("Type", "color");
                col = pCur->GetValue<Color>();
                col.SetColor(col.r(), col.g(), col.b(), 255);
                Q_snprintf(pszData, 32, "%i", col.GetRawColor());
                kv->SetString("Data", pszData);
                index = m_pTree->AddItem(kv, parentIndex);
                m_pTree->SetItemFgColor(index, col);
                break;
            case AT_ELEMENT_ARRAY:
                kv->SetString("Type", "element_array");
                Q_snprintf(pszData, 32, "%i item%s", pCur->GetArrayCount(), pCur->GetArrayCount() == 1 ? "" : "s");
                kv->SetString("Data", pszData);
                index = m_pTree->AddItem(kv, parentIndex);
                m_pTree->SetItemFgColor(index, Color(0, 128, 255, 255));
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
                m_pTree->SetItemFgColor(index, Color(255, 0, 0, 255));
                break;
            case AT_FLOAT_ARRAY:
                kv->SetString("Type", "float_array");
                for (int j = 0; j < pCur->GetArrayCount(); j++)
                {
                    Q_snprintf(pszData, 256, "%s%f", j == 0 ? "" : ", ", pCur->GetArray<float>()[j]);
                }
                kv->SetString("Data", pszData);
                index = m_pTree->AddItem(kv, parentIndex);
                m_pTree->SetItemFgColor(index, Color(0, 255, 0, 255));
                break;
            case AT_BOOL_ARRAY:
                kv->SetString("Type", "bool_array");
                for (int j = 0; j < pCur->GetArrayCount(); j++)
                {
                    Q_snprintf(pszData, 256, "%s%s", j == 0 ? "" : ", ", pCur->GetArray<bool>()[j] ? "true" : "false");
                }
                kv->SetString("Data", pszData);
                index = m_pTree->AddItem(kv, parentIndex);
                m_pTree->SetItemFgColor(index, Color(0, 255, 0, 255));
                break;
            case AT_COLOR_ARRAY:
                kv->SetString("Type", "color_array");
                for (int j = 0; j < pCur->GetArrayCount(); j++)
                {
                    col = pCur->GetArray<Color>()[j];
                    Q_snprintf(pszData, 256, "%s%i", j == 0 ? "" : ", ", col.GetRawColor());
                }
                col.SetColor(col.r(), col.g(), col.b(), 255);
                kv->SetString("Data", pszData);
                index = m_pTree->AddItem(kv, parentIndex);
                m_pTree->SetItemFgColor(index, col);
                break;
            }
            if(index == -1)
            {
                // Add anyways
                index = m_pTree->AddItem(kv, parentIndex);
                m_pTree->SetItemFgColor(index, Color(192, 192, 192, 255));
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
		//Msg("Error: No tree view item selected.\n");
		return;
	}

    // If pRoot's uniqueId is the same as the one we're trying to set, then set to the root document
    if (itemIndex == m_pTree->GetRootItemIndex())
    {
        // Set new root
        DirectorsCutGameSystem().SetDocumentFocusedRoot(NULL);
        DirectorsCutGameSystem().SetNeedsUpdate(true, 0);
        return;
    }

    KeyValues* kv = m_pTree->GetItemData(itemIndex);
    if (kv == NULL)
    {
        //Msg("Error: Tree view item has no data.\n");
    }

    // Get uniqueid
    const char* uniqueIdStr = kv->GetString("UniqueId");
    UniqueId_t uniqueId_t;
    bool failure = UuidFromString((unsigned char*)uniqueIdStr, (UUID*)&uniqueId_t);

    if (failure)
    {
        //Msg("Error: Could not convert uniqueId %s to UniqueId_t.\n", uniqueIdStr);
        return;
    }

    // Loop through attributes
    CDmxElement* pRoot = DirectorsCutGameSystem().GetDocumentFocusedRoot();
    if (pRoot == NULL)
        pRoot = DirectorsCutGameSystem().GetDocument();
    if (pRoot == NULL)
    {
        //Msg("No document loaded.\n");
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
    DirectorsCutGameSystem().SetNeedsUpdate(true, 0);
}

void DXEditorElementViewer::OnThink()
{
    //DECLARE_DMX_CONTEXT_NODECOMMIT();

    // Check to see if properties had changed from the tree view data
    int itemIndex = m_pTree->GetFirstSelectedItem();
    if (itemIndex != -1)
    {
        KeyValues* kv = m_pTree->GetItemData(itemIndex);
        if (kv != NULL)
        {
            // Check to see if properties are valid
            if (m_pPropTextEntry == NULL
                || m_pPropCheckButton == NULL
                || m_pPropLabel == NULL
                || m_pColorPickerButton == NULL
                || m_pMakeRootButton == NULL)
            {
				//Msg("Error: Could not get property controls.\n");
				return;
			}
            // Root button click
            if (m_pMakeRootButton->IsVisible()
                && m_pMakeRootButton->IsSelected())
            {
                m_pMakeRootButton->SetSelected(false);
                MakeRootButtonClick();
            }
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
                    //Msg("Updating %s to %s\n", pszText, pszTextEntry);
                    CDmxElement* pRoot = DirectorsCutGameSystem().GetDocumentFocusedRoot();
                    if (pRoot == NULL)
                        pRoot = DirectorsCutGameSystem().GetDocument();
                    if (pRoot == NULL)
                    {
                        //Msg("No document loaded.\n");
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
                    DirectorsCutGameSystem().SetAllNeedsUpdate(true);
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
                    //Msg("Updating %s to %s\n", pszText, bSelected ? "true" : "false");
                    CDmxElement* pRoot = DirectorsCutGameSystem().GetDocumentFocusedRoot();
                    if (pRoot == NULL)
                        pRoot = DirectorsCutGameSystem().GetDocument();
                    if (pRoot == NULL)
                    {
                        //Msg("No document loaded.\n");
                        return;
                    }
                    pRoot->SetValue<bool>(pszText, bSelected);
                    DirectorsCutGameSystem().SetNeedsUpdate(true, 0);
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
                    //Msg("Updating %s from %s to %s\n", pszText, kv->GetString("Data"), pszTextEntry);
                    kv->SetString("Data", pszTextEntry);
                    CDmxElement* pRoot = DirectorsCutGameSystem().GetDocumentFocusedRoot();
                    if (pRoot == NULL)
                        pRoot = DirectorsCutGameSystem().GetDocument();
                    if (pRoot == NULL)
                    {
                        //Msg("No document loaded.\n");
                        return;
                    }
                    pRoot->SetValue<Color>(pszText, clr);
                    DirectorsCutGameSystem().SetAllNeedsUpdate(true);
                }
            }
        }
    }

    if(DirectorsCutGameSystem().NeedsUpdate(0) == true)
    {
        //Msg("Updating element viewer...\n");
        DirectorsCutGameSystem().SetNeedsUpdate(false, 0);
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
                    m_bCanDoubleClick = false;
                    m_pTree->AddSelectedItem(i, true, false, true);
                    break;
                }
            }
        }
    }

    // TODO: layout?

    int x, y, w, h;
    int offset = 8;

    GetBounds(x, y, w, h);
    m_pTree->SetBounds(offset, offset, w - offset * 2, h - offset * 2);
}

void DXEditorElementViewer::PerformLayout()
{
    BaseClass::PerformLayout();
}

void DXEditorElementViewer::ApplySchemeSettings(IScheme *pScheme)
{
	BaseClass::ApplySchemeSettings(pScheme);

    // Dummy tree view
	HFont treeFont = pScheme->GetFont( "DefaultVerySmall" );
	m_pTree->SetFont( treeFont );
}