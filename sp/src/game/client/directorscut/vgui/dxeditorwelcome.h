//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window controls for Director's Cut.
//
// $NoKeywords: $
//=================================================================================//

#ifndef DXEDITORWELCOME_H
#define DXEDITORWELCOME_H

#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/Frame.h>
#include <vgui_controls/PropertyPage.h>
#include <vgui_controls/ToolWindow.h>
#include <vgui_controls/TreeView.h>
#include <vgui_controls/ListPanel.h>

using namespace vgui;

#define DXEDITORWELCOME_LINKS 6

class DXEditorWelcome : public EditablePanel
{
	DECLARE_CLASS_SIMPLE( DXEditorWelcome, EditablePanel );

public:
	DXEditorWelcome( Panel *pParent );
    virtual void ApplySchemeSettings( IScheme *scheme );
    virtual void OnThink();
    virtual void PerformLayout();
    
protected:
    ScalableImagePanel* pBannerContainer;
    Label* pInnerLabel;
    Label* pLinksLabel;
	const char* m_szLinks[ DXEDITORWELCOME_LINKS ][3] = {
        {"github", "GitHub", "https://github.com/KiwifruitDev/DirectorsCut"},
        {"discord", "Discord", "https://discord.gg/3X3teNecWs"},
        {"youtube", "YouTube", "https://youtube.com/@DirectorsCutMod"},
        {"twitter", "Twitter", "https://x.com/DirectorsCutMod"},
        {"bluesky", "Bluesky", "https://bsky.app/profile/directorscut.bsky.social"},
        {"vdc", "Valve Developer Wiki", "https://developer.valvesoftware.com/wiki/Director%27s_Cut"}
    };
    CUtlVector< Button* > m_vecButtons;
};

#endif // DXEDITORWELCOME_H
