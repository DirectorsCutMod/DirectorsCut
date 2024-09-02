#pragma once

#include "dxfm.h"
#include "dx_vgui_controls/Frame.h"
#include "dx_vgui_controls/PropertyPage.h"
#include "dx_vgui_controls/ToolWindow.h"
#include "dx_vgui_controls/TreeView.h"
#include "dx_vgui_controls/ListPanel.h"

using namespace vgui;

class LinkButton
{
public:
    LinkButton(const char* szInternalName, const char* szDisplayName, const char* szURL);
    void SetInternalName(const char* szInternalName);
    void SetDisplayName(const char* szDisplayName);
    void SetURL(const char* szURL);
    const char* GetInternalName();
    const char* GetDisplayName();
    const char* GetURL();
private:
    const char* m_szInternalName;
    const char* m_szDisplayName;
    const char* m_szURL;
};

class DXUIWelcome : public EditablePanel
{
    DECLARE_CLASS_SIMPLE( DXUIWelcome, EditablePanel );
public:
    DXUIWelcome(Panel* pParent);
    virtual void PerformLayout();
protected:
    ScalableImagePanel* pBannerContainer;
    Label* pInnerLabel;
    Label* pLinksLabel;
    CUtlVector<LinkButton> m_vecLinks;
    CUtlVector<Button*> m_vecButtons;
};
