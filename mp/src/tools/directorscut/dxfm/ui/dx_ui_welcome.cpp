#include "dx_ui_welcome.h"
#include "dx_vgui_controls/ScalableImagePanel.h"
#include "dx_vgui_controls/Button.h"
#include "dx_vgui_controls/Label.h"
#include "vgui/IInput.h"
#include "vgui/ISystem.h"
#include "tier0/memdbgon.h"

using namespace vgui;

LinkButton::LinkButton(const char* szInternalName, const char* szDisplayName, const char* szURL)
{
    m_szInternalName = szInternalName;
    m_szDisplayName = szDisplayName;
    m_szURL = szURL;
}

void LinkButton::SetInternalName(const char* szInternalName)
{
    m_szInternalName = szInternalName;
}

void LinkButton::SetDisplayName(const char* szDisplayName)
{
    m_szDisplayName = szDisplayName;
}

void LinkButton::SetURL(const char* szURL)
{
    m_szURL = szURL;
}

const char* LinkButton::GetInternalName()
{
    return m_szInternalName;
}

const char* LinkButton::GetDisplayName()
{
    return m_szDisplayName;
}

const char* LinkButton::GetURL()
{
    return m_szURL;
}

DXUIWelcome::DXUIWelcome(Panel* pParent) : BaseClass(pParent, "Welcome")
{
    pBannerContainer = new ScalableImagePanel(this, "banner" );
    pBannerContainer->SetImage( "directorscut/banner" );
    m_vecLinks.AddToTail(LinkButton("github", "GitHub", "https://github.com/DirectorsCutMod/DirectorsCut"));
    m_vecLinks.AddToTail(LinkButton("discord", "Discord", "https://discord.gg/3X3teNecWs"));
    m_vecLinks.AddToTail(LinkButton("youtube", "YouTube", "https://youtube.com/@DirectorsCutMod"));
    m_vecLinks.AddToTail(LinkButton("twitter", "X (Twitter)", "https://x.com/DirectorsCutMod"));
    m_vecLinks.AddToTail(LinkButton("bluesky", "Bluesky", "https://bsky.app/profile/directorscut.bsky.social"));
    m_vecLinks.AddToTail(LinkButton("vdc", "VDW", "https://developer.valvesoftware.com/wiki/Director%27s_Cut"));
    for ( int i = 0; i < m_vecLinks.Count(); i++ )
    {
        Button* pButton = new Button(this, m_vecLinks[i].GetInternalName(), m_vecLinks[i].GetDisplayName());
        char link[256];
        Q_snprintf(link, sizeof(link), "url %s", m_vecLinks[i].GetURL());
        pButton->SetCommand(link);
        m_vecButtons.AddToTail(pButton);
    }
    pInnerLabel = new Label( this, "inner_label", "Welcome to Director's Cut, a community-driven filmmaking mod for the Source engine.\nThis software is in early production and may be unstable.\nWant to contribute? Feel free to check out the GitHub page and Discord server.\nPress tab to switch between the editor window and in-game controls.\nYou may switch to the Primary Viewport tab to continue." );
    pLinksLabel = new Label( this, "links_label", "Links" );
}

void DXUIWelcome::PerformLayout()
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
    for (int i = 0; i < m_vecButtons.Count(); i++)
    {
        Button* pButton = m_vecButtons[i];
        pButton->SetBounds(currentX, startY, buttonWidth, buttonHeight);
        currentX += buttonWidth + (padding/2);
    }
}
