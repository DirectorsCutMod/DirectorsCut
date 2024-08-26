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
#include <vgui_controls/Menu.h>
#include <vgui_controls/MenuItem.h>

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

using namespace vgui;

DXEditorViewport::DXEditorViewport(Panel* pParent)
	: BaseClass(pParent, "Primary Viewport")
{
	m_hFont = vgui::scheme()->GetIScheme( vgui::scheme()->GetScheme( "ClientScheme" ) )->GetFont( "Default", true );
	
	// Create context menu
	m_pContextMenu = new Menu(this, "contextmenu");

	// Render Settings... (button)
	// Progessive Refinement (checkbox)
	// --- Separator ---
	// Enable Lighting (checkbox)
	// Display (submenu)
	// - Show Focal Plane (checkbox)
	// - Show Camera Frustum (checkbox)
	// - Show View Targets (checkbox)
	// - Show Shot ID Overlay (checkbox)
	// - Show Transform Labels (checkbox)
	// - --- Separator ---
	// - Trigger Game Effects In Reverse (checkbox)
	// - Stereo Flip (checkbox)
	// - --- Separator ---
	// - Allow Pixel Zoom (checkbox)
	// Draw Game Entities (submenu)
	// - Players (checkbox)
	// - NPCs (checkbox)
	// - World Static Props (checkbox)
	// - World Brush Models (checkbox)
	// - Ropes (checkbox)
	// - Beams (checkbox)
	// - Particles (checkbox)
	// - Other Entities (checkbox)
	// Draw Tool Objects (submenu)
	// - Models (checkbox)
	// - Effects (checkbox)
	// - Particles (checkbox)
	// - Lights (checkbox)
	// --- Separator ---
	// Game (submenu)
	// Draw Tool Objects In Game (checkbox)
	// Teleport Player To Camera (button)
	// Teleport Sets FOV (checkbox)
	// Reset Player Roll And FOV (button)
	// Delete (submenu)
	// - Models Outside Camera Frustum (button)
	// - Particles Outside Camera Frustum (button)
	// --- Separator ---
	// Load Map (button)

	m_pContextMenu->AddMenuItem("Render Settings...", new KeyValues( "Command", "command", "rendersettings" ), this );
	m_pContextMenu->AddCheckableMenuItem("Progressive Refinement", "Progressive Refinement", "progressiverefine", this );
	m_pContextMenu->AddSeparator();
	m_pContextMenu->AddCheckableMenuItem("Enable Lighting", "Enable Lighting", "enablelighting", this );
	Menu* displayMenu = new Menu(this, "displaymenu");
	displayMenu->AddCheckableMenuItem("Show Focal Plane", "Show Focal Plane", "showfocalplane", this );
	displayMenu->AddCheckableMenuItem("Show Camera Frustum", "Show Camera Frustum", "showcamerafrustum", this );
	displayMenu->AddCheckableMenuItem("Show View Targets", "Show View Targets", "showviewtargets", this );
	displayMenu->AddCheckableMenuItem("Show Shot ID Overlay", "Show Shot ID Overlay", "showshotidoverlay", this );
	displayMenu->AddCheckableMenuItem("Show Transform Labels", "Show Transform Labels", "showtransformlabels", this );
	displayMenu->AddSeparator();
	displayMenu->AddCheckableMenuItem("Trigger Game Effects In Reverse", "Trigger Game Effects In Reverse", "triggergameeffectsreverse", this );
	displayMenu->AddCheckableMenuItem("Stereo Flip", "Stereo Flip", "stereoflip", this );
	displayMenu->AddSeparator();
	displayMenu->AddCheckableMenuItem("Allow Pixel Zoom", "Allow Pixel Zoom", "allowpixelzoom", this );
	m_pContextMenu->AddCascadingMenuItem("Display", "Display", "display", this, displayMenu);
	Menu* drawEntitiesMenu = new Menu(this, "drawentitiesmenu");
	drawEntitiesMenu->AddCheckableMenuItem("Players", "Players", "drawplayers", this );
	drawEntitiesMenu->AddCheckableMenuItem("NPCs", "NPCs", "drawnpcs", this );
	drawEntitiesMenu->AddCheckableMenuItem("World Static Props", "World Static Props", "drawworldstaticprops", this );
	drawEntitiesMenu->AddCheckableMenuItem("World Brush Models", "World Brush Models", "drawworldbrushmodels", this );
	drawEntitiesMenu->AddCheckableMenuItem("Ropes", "Ropes", "drawropes", this );
	drawEntitiesMenu->AddCheckableMenuItem("Beams", "Beams", "drawbeams", this );
	drawEntitiesMenu->AddCheckableMenuItem("Particles", "Particles", "drawparticles", this );
	drawEntitiesMenu->AddCheckableMenuItem("Other Entities", "Other Entities", "drawotherentities", this );
	m_pContextMenu->AddCascadingMenuItem("Draw Game Entities", "Draw Game Entities", "drawgameentities", this, drawEntitiesMenu);
	Menu* drawToolObjectsMenu = new Menu(this, "drawtoolobjectsmenu");
	drawToolObjectsMenu->AddCheckableMenuItem("Models", "Models", "drawmodels", this );
	drawToolObjectsMenu->AddCheckableMenuItem("Effects", "Effects", "draweffects", this );
	drawToolObjectsMenu->AddCheckableMenuItem("Particles", "Particles", "drawparticles", this );
	drawToolObjectsMenu->AddCheckableMenuItem("Lights", "Lights", "drawlights", this );
	m_pContextMenu->AddCascadingMenuItem("Draw Tool Objects", "Draw Tool Objects", "drawtoolobjects", this, drawToolObjectsMenu);
	m_pContextMenu->AddSeparator();
	Menu* gameMenu = new Menu(this, "gamemenu");
	gameMenu->AddCheckableMenuItem("Draw Tool Objects In Game", "Draw Tool Objects In Game", "drawtoolobjectsingame", this );
	gameMenu->AddMenuItem("Teleport Player To Camera", new KeyValues( "Command", "command", "teleportplayertocamera" ), this );
	gameMenu->AddCheckableMenuItem("Teleport Sets FOV", "Teleport Sets FOV", "teleportsetsfov", this );
	gameMenu->AddMenuItem("Reset Player Roll And FOV", new KeyValues( "Command", "command", "resetplayerrollandfov" ), this );
	m_pContextMenu->AddCascadingMenuItem("Game", "Game", "game", this, gameMenu);
	Menu* deleteMenu = new Menu(this, "deletemenu");
	deleteMenu->AddMenuItem("Models Outside Camera Frustum", new KeyValues( "Command", "command", "deleteoutsidecamerafrustummodels" ), this );
	deleteMenu->AddMenuItem("Particles Outside Camera Frustum", new KeyValues( "Command", "command", "deleteoutsidecamerafrumparticles" ), this );
	m_pContextMenu->AddCascadingMenuItem("Delete", "Delete", "delete", this, deleteMenu);
	m_pContextMenu->AddSeparator();
	m_pContextMenu->AddMenuItem("Load Map", new KeyValues( "Command", "command", "loadmap" ), this );
}

DXEditorViewport::~DXEditorViewport()
{
	m_pContextMenu->MarkForDeletion();
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

	/*
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
	*/

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

	if(!DirectorsCutGameSystem().IsWorkCameraActive())
		return;

	ConVar* mouseMoveButton = g_pCVar->FindVar("dx_mousemovebutton");
	ButtonCode_t moveButton = MOUSE_LEFT;
	ButtonCode_t contextButton = MOUSE_RIGHT;
	switch (mouseMoveButton->GetInt())
	{
	case 2:
		moveButton = MOUSE_RIGHT;
		contextButton = MOUSE_LEFT;
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
	else if (code == contextButton)
	{
		Menu::PlaceContextMenu( this, m_pContextMenu );
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
		if (!DirectorsCutGameSystem().IsWorkCameraActive())
			return;

		// Adjust FOV of camera
		float fov = DirectorsCutGameSystem().GetWorkCameraFOV();
		fov -= delta;
		fov = clamp(fov, 1.0f, 179.0f);
		DirectorsCutGameSystem().SetWorkCameraFOV(fov);
	}
}


