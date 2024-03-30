//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window controls for Director's Cut.
// Contributors:
// - KiwifruitDev
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

DXEditorViewport::DXEditorViewport(Panel* pParent)
	: BaseClass(pParent, "Primary Viewport")
{
	m_hFont = vgui::scheme()->GetIScheme( vgui::scheme()->GetScheme( "ClientScheme" ) )->GetFont( "Default", true );
}

DXEditorViewport::~DXEditorViewport()
{
}

void DXEditorViewport::OnThink()
{
	// Engine must be running and texture must be valid
	if (engine->IsInGame())
	{
		ITexture* ref = GetPrimaryViewportTex();
		Assert(ref != NULL);

		CMatRenderContextPtr pRenderContext(g_pMaterialSystem);

		pRenderContext->PushRenderTargetAndViewport(ref, 0, 0, DirectorsCutGameSystem().GetViewportWidth(), DirectorsCutGameSystem().GetViewportHeight());

		// Set up player view and render to texture
		CViewSetup playerview = *view->GetPlayerViewSetup();
		playerview.origin = DirectorsCutGameSystem().GetCameraOrigin();
		playerview.angles = DirectorsCutGameSystem().GetCameraAngles();
		// Convert vertical FOV to horizontal FOV
		float fVerticalFov = DirectorsCutGameSystem().GetCameraFOV();
		float aspectRatio = (float)playerview.width / (float)playerview.height;
		float fHorizontalFov = 2.0f * atan(tan(fVerticalFov * M_PI / 360.0f) * aspectRatio) * 180.0f / M_PI;
		playerview.fov = fHorizontalFov;
		playerview.m_bDoBloomAndToneMapping = false;
		render->SetMainView(playerview.origin, playerview.angles);
		view->RenderView(playerview, VIEW_CLEAR_DEPTH | VIEW_CLEAR_COLOR, 0);

		pRenderContext->PopRenderTargetAndViewport();
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

	int offset = 8;
	x += offset;
	y += offset;
	width -= offset * 2;
	height -= offset * 2;

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

	if(DirectorsCutGameSystem().GetDocument() == NULL)
	{
		// TODO: Standard function for drawing text
		wchar_t* text = L"NO SESSION";
		g_pMatSystemSurface->DrawSetTextFont( m_hFont );

		int textWidth = 0;
		int textHeight = 0;
		g_pMatSystemSurface->GetTextSize(m_hFont, text, textWidth, textHeight);
		g_pMatSystemSurface->DrawSetTextColor(255, 0, 0, 255);

		int textX = x + (width - textWidth) / 2;
		int textY = y + (height - textHeight) / 2;
		g_pMatSystemSurface->DrawSetTextPos(textX, textY);
		g_pMatSystemSurface->DrawPrintText(text, wcslen(text));
		return;
	}

	if(!engine->IsInGame())
	{
		// TODO: Standard function for drawing text
		wchar_t* text = L"NO MAP LOADED!";
		g_pMatSystemSurface->DrawSetTextFont( m_hFont );

		int textWidth = 0;
		int textHeight = 0;
		g_pMatSystemSurface->GetTextSize(m_hFont, text, textWidth, textHeight);
		g_pMatSystemSurface->DrawSetTextColor(255, 0, 0, 255);

		int textX = x + (width - textWidth) / 2;
		int textY = y + (height - textHeight) / 2;
		g_pMatSystemSurface->DrawSetTextPos(textX, textY);
		g_pMatSystemSurface->DrawPrintText(text, wcslen(text));
		return;
	}

	// Draw the viewport with texture ID
	int nTextureID = GetPrimaryViewportTexID();
	g_pMatSystemSurface->DrawSetTexture(nTextureID);
	g_pMatSystemSurface->DrawTexturedRect(viewportX, viewportY, viewportX + viewportW, viewportY + viewportH);

	if(DirectorsCutGameSystem().IsWorkCameraActive())
	{
		// TODO: Standard function for drawing text
		wchar_t* text = L"WORK CAMERA";
		g_pMatSystemSurface->DrawSetTextFont( m_hFont );

		int textWidth = 0;
		int textHeight = 0;
		g_pMatSystemSurface->GetTextSize(m_hFont, text, textWidth, textHeight);
		g_pMatSystemSurface->DrawSetTextColor(255, 255, 255, 255);

		int textX = x + (width - textWidth) / 2;
		int textY = height - textHeight - 4;
		g_pMatSystemSurface->DrawSetTextPos(textX, textY);
		g_pMatSystemSurface->DrawPrintText(text, wcslen(text));
	}
}

void DXEditorViewport::OnMousePressed(MouseCode code)
{
	// Needs to be in-game
	if (!engine->IsInGame())
		return;
		
	if (DirectorsCutGameSystem().GetDocument() == NULL)
		return;

	if(!DirectorsCutGameSystem().IsWorkCameraActive())
		return;

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
		if (DirectorsCutGameSystem().GetDocument() == NULL)
			return;

		if(!DirectorsCutGameSystem().IsWorkCameraActive())
			return;

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

void DXEditorViewport::OnMouseWheeled(int delta)
{
	if (DirectorsCutGameSystem().IsMouseCaptured())
	{
		if (DirectorsCutGameSystem().GetDocument() == NULL)
			return;

		if (!DirectorsCutGameSystem().IsWorkCameraActive())
			return;

		// Adjust FOV of camera
		float fov = DirectorsCutGameSystem().GetWorkCameraFOV();
		fov -= delta;
		fov = clamp(fov, 1.0f, 179.0f);
		DirectorsCutGameSystem().SetWorkCameraFOV(fov);
	}
}


