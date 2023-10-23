//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window controls for Director's Cut.
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dxeditorwelcome.h"
#include "vgui_controls/ScalableImagePanel.h"
#include "vgui_controls/Button.h"
#include "vgui_controls/Label.h"
#include <vgui/IInput.h>
#include <vgui/ISystem.h>

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

using namespace vgui;

DXEditorWelcome::DXEditorWelcome(Panel* pParent)
	: BaseClass(pParent, "Welcome")
{
	m_vecLinks.AddToTail(LinkButton("github", "GitHub", "https://github.com/KiwifruitDev/DirectorsCut"));
	m_vecLinks.AddToTail(LinkButton("discord", "Discord", "https://discord.gg/3X3teNecWs"));
	m_vecLinks.AddToTail(LinkButton("youtube", "YouTube", "https://youtube.com/@DirectorsCutMod"));
	m_vecLinks.AddToTail(LinkButton("twitter", "X (Twitter)", "https://x.com/DirectorsCutMod"));
	m_vecLinks.AddToTail(LinkButton("bluesky", "Bluesky", "https://bsky.app/profile/directorscut.bsky.social"));
	m_vecLinks.AddToTail(LinkButton("vdc", "Valve Developer Wiki", "https://developer.valvesoftware.com/wiki/Director%27s_Cut"));

	pBannerContainer = new ScalableImagePanel(this, "banner" );
	pBannerContainer->SetImage( "directorscut/banner" );

	// Even buttons on bottom for links
	for ( int i = 0; i < DXEDITORWELCOME_LINKS; i++ )
	{
		Button* pButton = new Button( this, m_vecLinks[i].GetInternalName(), m_vecLinks[i].GetDisplayName());
		char link[256];
		Q_snprintf( link, sizeof( link ), "url %s", m_vecLinks[i].GetURL() );
		pButton->SetCommand( link );
		m_vecButtons.AddToTail( pButton );
	}

	// Labels
	pInnerLabel = new Label( this, "inner_label", "Welcome to Director's Cut, a community-driven filmmaking mod for the Source engine.\nThis software is in early production and may be unstable.\nWant to contribute? Feel free to check out the GitHub page and Discord server.\nPress tab to switch between the editor window and in-game controls.\nYou may switch to the Primary Viewport tab to continue." );
	pLinksLabel = new Label( this, "links_label", "Links" );
}

void DXEditorWelcome::OnThink()
{
}

void DXEditorWelcome::ApplySchemeSettings(IScheme *pScheme)
{
	BaseClass::ApplySchemeSettings(pScheme);
}

void DXEditorWelcome::PerformLayout()
{
	BaseClass::PerformLayout();
	int w = GetWide();
	int h = GetTall();
	int startX = 8;
	int buttonHeight = 24;
	int startY = h - buttonHeight - startX;
	int padding = startX;
	int buttonWidth = (w - (startX*2) - ((padding/2)*(m_vecButtons.Count()-1))) / m_vecButtons.Count();
	int currentX = startX;
	pBannerContainer->SetBounds(startX, startX, w - (startX*2), 75);
	pInnerLabel->SizeToContents();
	pInnerLabel->SetPos(startX, pBannerContainer->GetTall() + startX + padding);
	pLinksLabel->SizeToContents();
	pLinksLabel->SetPos(startX, startY - pLinksLabel->GetTall() - padding);
	for ( int i = 0; i < m_vecButtons.Count(); i++ )
	{
		Button* pButton = m_vecButtons[i];
		pButton->SetBounds( currentX, startY, buttonWidth, buttonHeight );
		currentX += buttonWidth + (padding/2);
	}
}
