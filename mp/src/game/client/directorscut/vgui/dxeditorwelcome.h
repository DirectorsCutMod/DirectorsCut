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

class LinkButton
{
public:
    LinkButton( const char* szInternalName, const char* szDisplayName, const char* szURL )
	{
        m_szInternalName = szInternalName;
		m_szDisplayName = szDisplayName;
		m_szURL = szURL;
	}
    void SetInternalName( const char* szInternalName ) { m_szInternalName = szInternalName; }
    void SetDisplayName( const char* szDisplayName ) { m_szDisplayName = szDisplayName; }
    void SetURL( const char* szURL ) { m_szURL = szURL; }
	const char* GetInternalName() { return m_szInternalName; }
    const char* GetDisplayName() { return m_szDisplayName; }
    const char* GetURL() { return m_szURL; }
    const char* m_szInternalName;
    const char* m_szDisplayName;
    const char* m_szURL;
};;

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
    CUtlVector< LinkButton> m_vecLinks;
    CUtlVector< Button* > m_vecButtons;
};

#endif // DXEDITORWELCOME_H
