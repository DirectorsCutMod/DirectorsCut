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
    void DrawViewport();
private:
    int iIndex;
    IMaterial* pScreenMaterial;
    KeyValues* pScreenKV;
    CTextureReference nScreenTextureRef;
    int iScreenTextureID;
    int iViewportWidth;
    int iViewportHeight;
    Vector vecOrigin = Vector(0, 0, 0);
    QAngle angAngles = QAngle(0, 0, 0);
    float flFOV = 90.0f;
};

extern int g_iAllocatedViewportFlags;
