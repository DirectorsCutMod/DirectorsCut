//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window controls for Director's Cut.
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "../directorscut.h"
#include "dxeditorviewport.h"
#include "vguimatsurface/imatsystemsurface.h"
#include "iviewrender.h"
#include "view_shared.h"
#include <vgui/IInput.h>

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

using namespace vgui;

static CTextureReference _viewport;
ITexture *GetViewportTex()
{
	if ( !_viewport )
	{
		int viewportWidth;
		int viewportHeight;
		engine->GetScreenSize(viewportWidth, viewportHeight);

		g_pMaterialSystem->BeginRenderTargetAllocation();

		_viewport.Init(g_pMaterialSystem->CreateNamedRenderTargetTextureEx2(
			"_rt_DXViewport",
			viewportWidth, viewportHeight, RT_SIZE_OFFSCREEN,
			g_pMaterialSystem->GetBackBufferFormat(),
			MATERIAL_RT_DEPTH_SHARED,
			0,
			CREATERENDERTARGETFLAGS_HDR));

		g_pMaterialSystem->EndRenderTargetAllocation();
	}
	return _viewport;
}

DXEditorViewport::DXEditorViewport(Panel* pParent)
	: BaseClass(pParent, "Primary Viewport")
{
	GetViewportTex();
}

DXEditorViewport::~DXEditorViewport()
{
	m_pScreenKV->Clear();
	//ForceDeleteMaterial( &m_pScreenMaterial );
	m_pScreenMaterial->Release();
	m_pScreenKV = NULL;
}

void DXEditorViewport::OnThink()
{
	// Engine must be running and texture must be valid
	if (engine->IsInGame())
	{
		if (!m_pScreenMaterial)
		{
			Assert(!m_pScreenKV);

			m_pScreenKV = new KeyValues("UnlitGeneric");
			Assert(m_pScreenKV);
			m_pScreenKV->SetString("$basetexture", "_rt_DXViewport");
			m_pScreenKV->SetInt("$ignorez", 1);
			m_pScreenKV->SetInt("$nofog", 1);
			m_pScreenMaterial = materials->CreateMaterial("__DXViewport", m_pScreenKV);
			Assert(m_pScreenMaterial);
			m_pScreenMaterial->Refresh();
			m_nTextureID = surface()->CreateNewTextureID();
			g_pMatSystemSurface->DrawSetTextureMaterial(m_nTextureID, m_pScreenMaterial);
		}
		if (m_pScreenMaterial)
		{
			CMatRenderContextPtr pRenderContext(g_pMaterialSystem);

			int width;
			int height;
			GetSize(width, height);

			pRenderContext->PushRenderTargetAndViewport(GetViewportTex(), 0, 0, width, height);

			// Set up player view and render to texture
			CViewSetup playerview = *view->GetPlayerViewSetup();
			if (DirectorsCutGameSystem().IsWorkCameraActive())
			{
				playerview.origin = DirectorsCutGameSystem().GetWorkCameraOrigin();
				playerview.angles = DirectorsCutGameSystem().GetWorkCameraAngles();
			}
			else
			{
				C_BasePlayer *pPlayer = C_BasePlayer::GetLocalPlayer();
				if (pPlayer)
				{
					// get head origin
					playerview.origin = pPlayer->GetAbsOrigin() + pPlayer->GetViewOffset();
					playerview.angles = pPlayer->GetAbsAngles();
				}
			}
			render->SetMainView(playerview.origin, playerview.angles);
			view->RenderView(playerview, VIEW_CLEAR_DEPTH | VIEW_CLEAR_COLOR, RENDERVIEW_DRAWHUD | RENDERVIEW_DRAWVIEWMODEL);

			pRenderContext->PopRenderTargetAndViewport();
		}
	}
}

void DXEditorViewport::Paint()
{
	int x;
	int y;
	int width;
	int height;

	GetPos(x, y);
	GetSize(width, height);

	y -= 27; // I'm not sure why, but there's an offset here for some reason

	// Draw black background
	g_pMatSystemSurface->DrawSetColor( 0, 0, 0, 255 );
	g_pMatSystemSurface->DrawFilledRect( x, y, x + width, y + height );

	// Constrain aspect ratio so black bars are passed through and the viewport is centered
	int viewportWidth;
	int viewportHeight;
	engine->GetScreenSize(viewportWidth, viewportHeight);

	float aspectRatio = (float)viewportWidth / (float)viewportHeight;
	float viewportAspectRatio = (float)width / (float)height;

	int viewportX = x;
	int viewportY = y;
	int viewportW = width;
	int viewportH = height;

	if (viewportAspectRatio > aspectRatio)
	{
		viewportW = viewportH * aspectRatio;
		viewportX += (width - viewportW) / 2;
	}
	else if (viewportAspectRatio < aspectRatio)
	{
		viewportH = viewportW / aspectRatio;
		viewportY += (height - viewportH) / 2;
	}

	// Draw the viewport with texture ID
	if (engine->IsInGame())
	{
		// Draw the viewport with texture ID
		g_pMatSystemSurface->DrawSetTexture(m_nTextureID);
		g_pMatSystemSurface->DrawTexturedRect(viewportX, viewportY, viewportX + viewportW, viewportY + viewportH);
	}
	else
	{
		// Draw a blank viewport to indicate that the game is not running
		g_pMatSystemSurface->DrawSetColor( 64, 64, 64, 255 );
		g_pMatSystemSurface->DrawFilledRect( viewportX, viewportY, viewportX + viewportW, viewportY + viewportH );
	}
}

void DXEditorViewport::OnMousePressed(MouseCode code)
{
	ConVar* mouseMoveButton = g_pCVar->FindVar("dx_mousemovebutton");
	ButtonCode_t moveButton = MOUSE_LEFT;
	switch (mouseMoveButton->GetInt())
	{
	case 1:
		moveButton = MOUSE_LEFT;
		break;
	case 2:
		moveButton = MOUSE_RIGHT;
		break;
	case 3:
		moveButton = MOUSE_MIDDLE;
		break;
	case 4:
		moveButton = MOUSE_4;
		break;
	case 5:
		moveButton = MOUSE_5;
		break;
	}
	if (code == moveButton)
	{
		DirectorsCutGameSystem().SetMouseCaptured(true);
		input()->SetMouseCapture(GetVPanel());
		// Warp the mouse to the center of the screen
		int width, height;
		GetSize( width, height );
		int x = width / 2;
		int y = height / 2;

		int xpos = x;
		int ypos = y;
		LocalToScreen( xpos, ypos );
		input()->SetCursorPos( xpos, ypos );
	}
}

void DXEditorViewport::OnMouseReleased(MouseCode code)
{
	ConVar* mouseMoveButton = g_pCVar->FindVar("dx_mousemovebutton");
	ButtonCode_t moveButton = MOUSE_LEFT;
	switch (mouseMoveButton->GetInt())
	{
	case 1:
		moveButton = MOUSE_LEFT;
		break;
	case 2:
		moveButton = MOUSE_RIGHT;
		break;
	case 3:
		moveButton = MOUSE_MIDDLE;
		break;
	case 4:
		moveButton = MOUSE_4;
		break;
	case 5:
		moveButton = MOUSE_5;
		break;
	}
	if (code == moveButton)
	{
		DirectorsCutGameSystem().SetMouseCaptured(false);
		input()->SetMouseCapture(NULL);
	}
}

void DXEditorViewport::OnCursorMoved(int x, int y)
{
	if (DirectorsCutGameSystem().IsMouseCaptured())
	{
		// Set mouse to middle of viewport
		int width, height;
		GetSize(width, height);
		int xpos = width / 2;
		int ypos = height / 2;
		LocalToScreen(xpos, ypos);
		input()->SetCursorPos(xpos, ypos);

		// Get mouse delta
		int deltaX, deltaY;
		input()->GetCursorPos(deltaX, deltaY);
		deltaX -= xpos;
		deltaY -= ypos;

		// Mouse sensitivity
		ConVar* dx_mousesensitivity = g_pCVar->FindVar("dx_mousesensitivity");
		float mouseSensitivity = dx_mousesensitivity ? dx_mousesensitivity->GetFloat() : 0.1f;

		// Rotate camera
		QAngle angCamera = DirectorsCutGameSystem().GetWorkCameraAngles();
		angCamera.y -= deltaX * mouseSensitivity;
		angCamera.x += deltaY * mouseSensitivity;
		angCamera.x = clamp(angCamera.x, -89.0f, 89.0f);
		DirectorsCutGameSystem().SetWorkCameraAngles(angCamera);
	}
}


