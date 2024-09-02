#include "dxfm.h"
#include "dx_viewport.h"
#include "tier0/memdbgon.h"
#include <vgui/ISurface.h>
#include "dx_vgui_controls/Controls.h"

ConVar viewportWidth( "dx_viewportwidth", "1280", FCVAR_ARCHIVE, "Viewport width" );
ConVar viewportHeight( "dx_viewportheight", "720", FCVAR_ARCHIVE, "Viewport height" );

int g_iAllocatedViewportFlags = 0;

DXViewport::DXViewport(int index)
{
    // Only allow one viewport per index
    int flags = 1 << index;
    if (g_iAllocatedViewportFlags & flags)
    {
        Assert(0);
        return;
    }
    g_iAllocatedViewportFlags |= flags;
    const char* viewportName = "_rt_DXViewport%d";
    char szViewportName[64];
    Q_snprintf(szViewportName, sizeof(szViewportName), viewportName, index);
    int width = viewportWidth.GetInt();
    int height = viewportHeight.GetInt();
    iViewportWidth = width;
    iViewportHeight = height;
	g_pMaterialSystem->BeginRenderTargetAllocation();
	nScreenTextureRef.Init(g_pMaterialSystem->CreateNamedRenderTargetTextureEx2(
		szViewportName,
		width, height, RT_SIZE_OFFSCREEN,
		g_pMaterialSystem->GetBackBufferFormat(),
		MATERIAL_RT_DEPTH_SHARED,
		0,
		CREATERENDERTARGETFLAGS_HDR));
	g_pMaterialSystem->EndRenderTargetAllocation();
	pScreenKV = new KeyValues("UnlitGeneric");
	pScreenKV->SetString("$basetexture", szViewportName);
	pScreenKV->SetInt("$ignorez", 1);
	pScreenKV->SetInt("$nofog", 1);
    const char* materialName = "__DXViewport%d";
    char szMaterialName[64];
    Q_snprintf(szMaterialName, sizeof(szMaterialName), materialName, index);
    pScreenMaterial = materials->CreateMaterial(szMaterialName, pScreenKV);
	pScreenMaterial->Refresh();
	iScreenTextureID = vgui::surface()->CreateNewTextureID();
	g_pMatSystemSurface->DrawSetTextureMaterial(iScreenTextureID, pScreenMaterial);
}

DXViewport::~DXViewport()
{
    if (pScreenMaterial != NULL)
	{
		pScreenMaterial->Release();
		pScreenMaterial = NULL;
	}

	if (pScreenKV != NULL)
	{
		pScreenKV->Clear();
		pScreenKV = NULL;
	}

	if (nScreenTextureRef.IsValid())
	{
		nScreenTextureRef.Shutdown();
		nScreenTextureRef.Init(NULL);
	}
}

IMaterial* DXViewport::GetScreenMaterial()
{
	if (pScreenMaterial != NULL)
		return pScreenMaterial;
	Assert(pScreenMaterial != NULL);
	return pScreenMaterial;
}

KeyValues* DXViewport::GetScreenKV()
{
	if (pScreenKV != NULL)
		return pScreenKV;
	Assert(pScreenKV != NULL);
	return pScreenKV;
}

ITexture* DXViewport::GetViewportTex()
{
	if (nScreenTextureRef.IsValid())
		return nScreenTextureRef;
	Assert(nScreenTextureRef.IsValid());
	return nScreenTextureRef;
}

int DXViewport::GetViewportTexID()
{
	if (iScreenTextureID != -1)
		return iScreenTextureID;
	Assert(iScreenTextureID != -1);
	return iScreenTextureID;
}

int DXViewport::GetViewportWidth()
{
	return iViewportWidth;
}

int DXViewport::GetViewportHeight()
{
	return iViewportHeight;
}
