#pragma once

#include "matsys_controls/matsyscontrols.h"
#include "vguimatsurface/IMatSystemSurface.h"
#include "materialsystem/MaterialSystemUtil.h"

using namespace vgui;

class DXViewport
{
public:
    DXViewport(int index = 0);
    ~DXViewport();
    IMaterial* GetScreenMaterial();
    KeyValues* GetScreenKV();
    ITexture* GetViewportTex();
    int GetViewportTexID();
    int GetViewportWidth();
    int GetViewportHeight();
private:
    int iIndex;
    IMaterial* pScreenMaterial;
    KeyValues* pScreenKV;
    CTextureReference nScreenTextureRef;
    int iScreenTextureID;
    int iViewportWidth;
    int iViewportHeight;
};

extern int g_iAllocatedViewportFlags;
