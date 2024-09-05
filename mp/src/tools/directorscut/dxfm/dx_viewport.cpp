#include "dxfm.h"
#include "dx_viewport.h"
#include "tier0/memdbgon.h"
#include <vgui/ISurface.h>
#include "dx_vgui_controls/Controls.h"

#include "vguimatsurface/imatsystemsurface.h"
#include "view_shared.h"

#include <tier0/memdbgon.h>

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

void DXViewport::DrawViewport()
{
	// If the editor isn't visible, don't render the viewport
	if (!g_pDXFM->IsToolActive())
		return;

	// Get the viewport texture, this should also create it if it doesn't exist
	ITexture* ref = GetViewportTex();
	Assert(ref != NULL);

	CMatRenderContextPtr pRenderContext(g_pMaterialSystem);

	// Render to texture
	pRenderContext->PushRenderTargetAndViewport(ref, 0, 0, iViewportWidth, iViewportHeight);
		// Set up player view
		CViewSetup playerview;
		enginetools->GetPlayerView(playerview, 0, 0, iViewportWidth, iViewportHeight);
		playerview.origin = vecOrigin;
		playerview.angles = angAngles;
		// Convert vertical FOV to horizontal FOV
		// FIXME: Turns out that SFM doesn't use this system, figure out how to properly calculate FOV
		// Pragma uses predefined values with interpolation, could be useful
		// See https://github.com/Silverlan/pfm/blob/b03ef04029a5be72a3a1db67ab92db4d6b659255/lua/sfm.lua#L89
		float flVerticalFov = flFOV;
		float flAspectRatio = (float)iViewportWidth / (float)iViewportHeight;
		float flHorizontalFov = 2.0f * atan(tan(flVerticalFov * M_PI / 360.0f) * flAspectRatio) * 180.0f / M_PI;
		// TEST: Multiply by 1.777 (16:9 aspect ratio) to match SFM's FOV
		//flHorizontalFov *= flAspectRatio;
		playerview.fov = flHorizontalFov;
		playerview.m_bDoBloomAndToneMapping = false;
		render->SetMainView(playerview.origin, playerview.angles);
		enginetools->RenderView(playerview, VIEW_CLEAR_DEPTH | VIEW_CLEAR_COLOR, 0);
	pRenderContext->PopRenderTargetAndViewport();
}
