#include "dxfm.h"
#include "dx_viewport.h"
#include "dx_ui_viewport.h"
#include "dx_ui_panel.h"
#include "vguimatsurface/imatsystemsurface.h"
#include "view_shared.h"
#include <vgui/IInput.h>
#include <tier0/memdbgon.h>

using namespace vgui;

ConVar cameraMovementSpeedMin( "dx_viewport_speed_min", "100.0", 0, "Default and minimum camera speed while moving" );
ConVar cameraMovementSpeedMax( "dx_viewport_speed_max", "1000.0", 0, "Maximum camera speed while moving" );
ConVar cameraMovementSpeedMultiplierSprint( "dx_viewport_speed_multiplier_sprint", "5.0", 0, "Camera speed multiplier, applied while holding the sprint key and moving" );
ConVar cameraMovementSpeedMultiplierWalk( "dx_viewport_speed_multiplier_walk", "0.2", 0, "Camera speed multiplier, applied while holding the walk key and moving" );
ConVar mouseSensitivity( "dx_viewport_sensitivity", "0.3", 0, "Mouse sensitivity while moving the camera" );

OverlayText::OverlayText(const wchar_t* text, OverlayAnchor anchor, Color textColor, Vector2D textOffset)
{
	m_text = text;
	m_anchor = anchor;
	m_textColor = textColor;
	m_textOffset = textOffset;
}

OverlayText::OverlayText(const wchar_t* text, OverlayAnchor anchor, Color textColor, int textOffsetX, int textOffsetY)
{
	m_text = text;
	m_anchor = anchor;
	m_textColor = textColor;
	m_textOffset = Vector2D(textOffsetX, textOffsetY);
}

const wchar_t* OverlayText::GetText()
{
	return m_text;
}

OverlayAnchor OverlayText::GetAnchor()
{
	return m_anchor;
}

Color OverlayText::GetTextColor()
{
	return m_textColor;
}

Vector2D OverlayText::GetTextOffset()
{
	return m_textOffset;
}

int OverlayText::GetTextOffsetX()
{
	return m_textOffset.x;
}

int OverlayText::GetTextOffsetY()
{
	return m_textOffset.y;
}

void OverlayText::SetText(const wchar_t* text)
{
	m_text = text;
}

void OverlayText::SetAnchor(OverlayAnchor anchor)
{
	m_anchor = anchor;
}

void OverlayText::SetTextColor(Color textColor)
{
	m_textColor = textColor;
}

void OverlayText::SetTextOffset(Vector2D textOffset)
{
	m_textOffset = textOffset;
}

void OverlayText::SetTextOffsetX(int textOffsetX)
{
	m_textOffset.x = textOffsetX;
}

void OverlayText::SetTextOffsetY(int textOffsetY)
{
	m_textOffset.y = textOffsetY;
}

DXUIViewport::DXUIViewport(Panel* pParent, int index) : BaseClass(pParent, "Viewport")
{
	m_hFont = vgui::scheme()->GetIScheme( vgui::scheme()->GetScheme( "ClientScheme" ) )->GetFont( "Default", true );
	SetViewport(index);
}

DXUIViewport::~DXUIViewport()
{
	g_pDXFM->FreeViewport(m_iIndex);
}

void DXUIViewport::OnThink()
{
	// TODO: Session document support, add and remove this overlay text as needed
	if(m_iNoSessionOverlayText == -1)
		m_iNoSessionOverlayText = AddOverlayText(L"NO SESSION", OVERLAY_ANCHOR_TOP_CENTER, Color(255, 0, 0, 255), 0, 0);
	// Map loaded state is handled by IsInGame()
	if (!engine->IsInGame())
	{
		// Add overlay text for no map if it doesn't exist
		if(m_iNoMapOverlayText == -1)
			m_iNoMapOverlayText = AddOverlayText(L"NO MAP LOADED!", OVERLAY_ANCHOR_TOP_CENTER, Color(255, 0, 0, 255), 0, 0);
	}
	else
	{
		// Only apply movement if mouse is captured
		if (m_bMouseCaptured)
		{
			// Get frame time
			float ft = g_pDXFM->GetFrameTime();

			// Set input variables
			m_bKeyHeldForward = vgui::input()->IsKeyDown(m_iKeyForward);
			m_bKeyHeldBackward = vgui::input()->IsKeyDown(m_iKeyBackward);
			m_bKeyHeldLeft = vgui::input()->IsKeyDown(m_iKeyLeft);
			m_bKeyHeldRight = vgui::input()->IsKeyDown(m_iKeyRight);
			m_bKeyHeldUp = vgui::input()->IsKeyDown(m_iKeyUp);
			m_bKeyHeldDown = vgui::input()->IsKeyDown(m_iKeyDown);
			m_bKeyHeldSpeed = vgui::input()->IsKeyDown(m_iKeySpeed);
			m_bKeyHeldSlow = vgui::input()->IsKeyDown(m_iKeySlow);
			m_bKeyHeldRotate = vgui::input()->IsKeyDown(m_iKeyRotate);
			m_bKeyHeldOrbit = vgui::input()->IsKeyDown(m_iKeyOrbit);

			// If not holding a movement key, set m_flCameraMovementSpeed to default
			if (!m_bKeyHeldForward && !m_bKeyHeldBackward && !m_bKeyHeldLeft && !m_bKeyHeldRight && !m_bKeyHeldUp && !m_bKeyHeldDown)
			{
				m_flCameraMovementSpeed = cameraMovementSpeedMin.GetFloat();
			}
			else
			{
				// Increase m_flCameraMovementSpeed by multiplier until it reaches cameraMovementSpeedMax
				if (m_flCameraMovementSpeed < cameraMovementSpeedMax.GetFloat())
					m_flCameraMovementSpeed += ( cameraMovementSpeedMax.GetFloat() - cameraMovementSpeedMin.GetFloat() ) * 0.1f * ft;
				else
					m_flCameraMovementSpeed = cameraMovementSpeedMax.GetFloat();
			}

			// Get forward, right, up vectors
			Vector vecForward, vecRight, vecUp;
			AngleVectors(m_angWorkCameraAngles, &vecForward, &vecRight, &vecUp);

			// Hold Shift or Ctrl to speed up or slow down movement
			float flSpeed = 1.0f;
			if (m_bKeyHeldSpeed)
				flSpeed = cameraMovementSpeedMultiplierSprint.GetFloat();
			if (m_bKeyHeldSlow)
				flSpeed = cameraMovementSpeedMultiplierWalk.GetFloat();

			flSpeed *= 0.01f; // too fast?

			// Handle key presses for movement
			if (m_bKeyHeldForward)
				m_vecWorkCameraOrigin += vecForward * m_flCameraMovementSpeed * flSpeed;
			if (m_bKeyHeldBackward)
				m_vecWorkCameraOrigin -= vecForward * m_flCameraMovementSpeed * flSpeed;
			if (m_bKeyHeldLeft)
				m_vecWorkCameraOrigin -= vecRight * m_flCameraMovementSpeed * flSpeed;
			if (m_bKeyHeldRight)
				m_vecWorkCameraOrigin += vecRight * m_flCameraMovementSpeed * flSpeed;
			if (m_bKeyHeldUp)
				m_vecWorkCameraOrigin += Vector(0, 0, m_flCameraMovementSpeed * flSpeed);
			if (m_bKeyHeldDown)
				m_vecWorkCameraOrigin -= Vector(0, 0, m_flCameraMovementSpeed * flSpeed);
		}
		else
		{
			// Reset held variables
			m_bKeyHeldForward = false;
			m_bKeyHeldBackward = false;
			m_bKeyHeldLeft = false;
			m_bKeyHeldRight = false;
			m_bKeyHeldUp = false;
			m_bKeyHeldDown = false;
			m_bKeyHeldSpeed = false;
			m_bKeyHeldSlow = false;
			m_bKeyHeldRotate = false;
			m_bKeyHeldOrbit = false;
		}

		// Remove overlay text for no map if it exists
		if(m_iNoMapOverlayText != -1)
		{
			RemoveOverlayText(m_iNoMapOverlayText);
			m_iNoMapOverlayText = -1;
		}

		// Mark viewport as dirty if it's not in game
		if(!engine->IsInGame() || m_pViewport == NULL)
		{
			m_bViewportIsDirty = true;
			SetViewport(m_iIndex);
			return;
		}

		// If the editor isn't visible, don't render the viewport
		if (!DXUIPanel::IsEditorVisible())
			return;

		// Draw!
		m_pViewport->DrawViewport(m_vecWorkCameraOrigin, m_angWorkCameraAngles, m_flWorkCameraFOV);
	}
}

void DXUIViewport::Paint()
{
	// Don't bother rendering if the editor isn't visible
	if(!DXUIPanel::IsEditorVisible())
		return;
		
	int x, y, width, height;
	GetPos(x, y);
	GetSize(width, height);

	y -= 28; // I'm not sure why, but there's an offset here for some reason

	//int offset = 8;
	//x += offset;
	//y += offset;
	//width -= offset * 2;
	//height -= offset * 2;

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

	if(engine->IsInGame() && !m_bViewportIsDirty && m_pViewport != NULL)
	{
		// Draw the viewport with texture ID
		int nTextureID = m_pViewport->GetViewportTexID();
		g_pMatSystemSurface->DrawSetTexture(nTextureID);
		g_pMatSystemSurface->DrawTexturedRect(viewportX, viewportY, viewportX + viewportW, viewportY + viewportH);
	}

	// If the work camera is active, add a translucent blue border (64, 192, 255, 64) to indicate it when moving the camera
	if(m_bWorkCameraActive && m_bMouseCaptured)
	{
		g_pMatSystemSurface->DrawSetColor(64, 192, 255, 64);
		g_pMatSystemSurface->DrawOutlinedRect(viewportX, viewportY, viewportX + viewportW, viewportY + viewportH);
	}

	// Each anchor has an offset increment so they don't overlap each other
	int anchorOffsetIncrement = 8;
	int anchorOffsetTopLeft = 0;
	int anchorOffsetTopCenter = 0;
	int anchorOffsetTopRight = 0;
	int anchorOffsetCenterLeft = 0;
	int anchorOffsetCenter = 0;
	int anchorOffsetCenterRight = 0;
	
	// Bottom offsets have a default negative value so they aren't out of bounds
	int anchorOffsetBottomLeft = -anchorOffsetIncrement/2;
	int anchorOffsetBottomCenter = -anchorOffsetIncrement/2;
	int anchorOffsetBottomRight = -anchorOffsetIncrement/2;

	// Draw overlay text
	for (int i = 0; i < m_vecOverlayText.Count(); i++)
	{
		OverlayText* overlayText = GetOverlayText(i);

		// Text and text color
		const wchar_t* text = overlayText->GetText();
		g_pMatSystemSurface->DrawSetTextColor(overlayText->GetTextColor());

		// TODO: Allow OverlayText to choose font
		// Use default font for now
		g_pMatSystemSurface->DrawSetTextFont(m_hFont);

		// Get text size
		int textWidth = 0;
		int textHeight = 0;
		g_pMatSystemSurface->GetTextSize(m_hFont, text, textWidth, textHeight);

		// Calculate text position and offsets
		int textX = 0;
		int textY = 0;
		switch(overlayText->GetAnchor())
		{
		case OVERLAY_ANCHOR_TOP_LEFT:
			textX = x + overlayText->GetTextOffsetX();
			textY = y + overlayText->GetTextOffsetY() + anchorOffsetTopLeft;
			anchorOffsetTopLeft += anchorOffsetIncrement;
			break;
		case OVERLAY_ANCHOR_TOP_CENTER:
			textX = x + (width - textWidth) / 2 + overlayText->GetTextOffsetX();
			textY = y + overlayText->GetTextOffsetY() + anchorOffsetTopCenter;
			anchorOffsetTopCenter += anchorOffsetIncrement;
			break;
		case OVERLAY_ANCHOR_TOP_RIGHT:
			textX = x + width - textWidth + overlayText->GetTextOffsetX();
			textY = y + overlayText->GetTextOffsetY() + anchorOffsetTopRight;
			anchorOffsetTopRight += anchorOffsetIncrement;
			break;
		case OVERLAY_ANCHOR_CENTER_LEFT:
			textX = x + overlayText->GetTextOffsetX();
			textY = y + (height - textHeight) / 2 + overlayText->GetTextOffsetY() + anchorOffsetCenterLeft;
			anchorOffsetCenterLeft += anchorOffsetIncrement;
			break;
		case OVERLAY_ANCHOR_CENTER:
			textX = x + (width - textWidth) / 2 + overlayText->GetTextOffsetX();
			textY = y + (height - textHeight) / 2 + overlayText->GetTextOffsetY() + anchorOffsetCenter;
			anchorOffsetCenter += anchorOffsetIncrement;
			break;
		case OVERLAY_ANCHOR_CENTER_RIGHT:
			textX = x + width - textWidth + overlayText->GetTextOffsetX();
			textY = y + (height - textHeight) / 2 + overlayText->GetTextOffsetY() + anchorOffsetCenterRight;
			anchorOffsetCenterRight += anchorOffsetIncrement;
			break;
		// Bottom offsets increment by subtracting, so they go up
		case OVERLAY_ANCHOR_BOTTOM_LEFT:
			textX = x + overlayText->GetTextOffsetX();
			textY = y + height - textHeight + overlayText->GetTextOffsetY() + anchorOffsetBottomLeft;
			anchorOffsetBottomLeft -= anchorOffsetIncrement;
			break;
		case OVERLAY_ANCHOR_BOTTOM_CENTER:
			textX = x + (width - textWidth) / 2 + overlayText->GetTextOffsetX();
			textY = y + height - textHeight + overlayText->GetTextOffsetY() + anchorOffsetBottomCenter;
			anchorOffsetBottomCenter -= anchorOffsetIncrement;
			break;
		case OVERLAY_ANCHOR_BOTTOM_RIGHT:
			textX = x + width - textWidth + overlayText->GetTextOffsetX();
			textY = y + height - textHeight + overlayText->GetTextOffsetY() + anchorOffsetBottomRight;
			anchorOffsetBottomRight -= anchorOffsetIncrement;
			break;
		}

		// Set text offset and draw
		g_pMatSystemSurface->DrawSetTextPos(textX, textY);
		g_pMatSystemSurface->DrawPrintText(text, wcslen(text));
	}
}

void DXUIViewport::OnMousePressed(MouseCode code)
{
	// Needs to be in-game
	if (!engine->IsInGame())
		return;
	if(m_bMouseCaptured)
		return;

	// Set the appropriate boolean for the mouse button that was pressed
	m_bMouseButtonHeldPrimary = (code == m_iMouseButtonPrimary);
	m_bMouseButtonHeldSecondary = (code == m_iMouseButtonSecondary);
	m_bMouseButtonHeldMiddle = (code == m_iMouseButtonMiddleButton);
	m_bMouseButtonHeldX1 = (code == m_iMouseButtonX1Button);
	m_bMouseButtonHeldX2 = (code == m_iMouseButtonX2Button);

	// Capture the mouse if the primary mouse button is held
	// Holding ALT+Right or Alt+Middle should also capture the mouse
	if ((code == m_iMouseButtonPrimary) || ((m_bMouseButtonHeldSecondary || m_bMouseButtonHeldMiddle) && m_iKeyOrbit))
	{
		m_bMouseCaptured = true;

		// Only show overlay text while moving the camera
		if(m_bWorkCameraActive)
		{
			m_iWorkCameraOverlayText = AddOverlayText(L"WORK CAMERA", OVERLAY_ANCHOR_BOTTOM_CENTER, Color(64, 192, 255, 255), 0, 0);
		}
		else
		{
			// TODO: Get name of scene camera, not done yet because there is no session document structure
			m_iSceneCameraOverlayText = AddOverlayText(L"SCENE CAMERA", OVERLAY_ANCHOR_BOTTOM_CENTER, Color(255, 255, 255, 255), 0, 0);
		}
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

void DXUIViewport::OnMouseReleased(MouseCode code)
{
	// Needs to be in-game
	if (!engine->IsInGame())
		return;

	// Release the appropriate boolean for the mouse button that was released
	if (code == m_iMouseButtonPrimary)
		m_bMouseButtonHeldPrimary = false;
	if (code == m_iMouseButtonSecondary)
		m_bMouseButtonHeldSecondary = false;
	if (code == m_iMouseButtonMiddleButton)
		m_bMouseButtonHeldMiddle = false;
	if (code == m_iMouseButtonX1Button)
		m_bMouseButtonHeldX1 = false;
	if (code == m_iMouseButtonX2Button)
		m_bMouseButtonHeldX2 = false;

	// Release mouse capture if primary mouse button is released
	// Releasing ALT+Right, ALT+Middle, or ALT (if primary mouse button isn't held) should also release the mouse
	if (code == m_iMouseButtonPrimary || ((m_bMouseButtonHeldSecondary || m_bMouseButtonHeldMiddle) && m_iKeyOrbit) || (m_bMouseButtonHeldPrimary && m_iKeyOrbit))
	{
		m_bMouseCaptured = false;
		// Always remove the overlay text even if work camera is not active
		// Could be dormant after switching to scene camera
		if(m_iWorkCameraOverlayText != -1)
		{
			RemoveOverlayText(m_iWorkCameraOverlayText);
			m_iWorkCameraOverlayText = -1;
		}
		// Remove scene camera overlay text if it exists
		if(m_iSceneCameraOverlayText != -1)
		{
			RemoveOverlayText(m_iSceneCameraOverlayText);
			m_iSceneCameraOverlayText = -1;
		}
		input()->SetMouseCapture(NULL);
	}
}

void DXUIViewport::OnCursorMoved(int x, int y)
{
	// Don't bother if the editor isn't visible
	if(!DXUIPanel::IsEditorVisible())
		return;

	// Set m_bMouseInRange to true if the mouse is hovering over the viewport
	int viewportX, viewportY;
	GetPos(viewportX, viewportY);
	int viewportWidth, viewportHeight;
	GetSize(viewportWidth, viewportHeight);
	if (x >= viewportX && x <= viewportX + viewportWidth && y >= viewportY && y <= viewportY + viewportHeight)
		m_bMouseInRange = true;
	else
		m_bMouseInRange = false;

	// Get mouse delta if mouse is captured
	if (m_bMouseCaptured)
	{
		// Set mouse to middle of viewport
		int xpos = viewportWidth / 2;
		int ypos = viewportHeight / 2;
		LocalToScreen(xpos, ypos);
		input()->SetCursorPos(xpos, ypos);

		// Get mouse delta
		int deltaX, deltaY;
		input()->GetCursorPos(deltaX, deltaY);
		deltaX -= xpos;
		deltaY -= ypos;

		// Rotate camera
		QAngle angWorkCamera = QAngle(m_angWorkCameraAngles.x, m_angWorkCameraAngles.y, m_angWorkCameraAngles.z);
		angWorkCamera.y -= deltaX * mouseSensitivity.GetFloat();
		angWorkCamera.x += deltaY * mouseSensitivity.GetFloat();
		angWorkCamera.x = clamp(angWorkCamera.x, -89.0f, 89.0f);
		m_angWorkCameraAngles = angWorkCamera;
	}
}

void DXUIViewport::OnMouseWheeled(int delta)
{
	if (m_bMouseCaptured)
	{
		// Adjust FOV of camera
		if (m_bWorkCameraActive)
		{
			m_flWorkCameraFOV -= delta;
			m_flWorkCameraFOV = clamp(m_flWorkCameraFOV, 1.0f, 179.0f);
		}
	}
}

bool DXUIViewport::RequestInfo(KeyValues* data)
{
	if (Q_strcmp(data->GetName(), "HandleKeyChange") == 0)
	{
		// Handle key presses
		ButtonCode_t key = (ButtonCode_t)data->GetInt("key");
		bool isDown = data->GetBool("isDown");
		bool wasDown = data->GetBool("wasDown");
		return HandleKeyChange(key, isDown, wasDown);
	}
	else if (Q_strcmp(data->GetName(), "PageHasContextMenu") == 0)
	{
		// Return true if the page has a context menu
		return true;
	}
	return false;
}

void DXUIViewport::OnCommand(const char *pcCommand)
{
}


void DXUIViewport::OnOpenContextMenu(KeyValues* data)
{
	// Don't bother if we're invisible
	if (!IsVisible())
		return;
	// Show context menu
	if(CreateContextMenu())
		OpenContextMenu();
}

void DXUIViewport::SetViewport(int index)
{
	if(m_bViewportIsDirty)
	{
		m_iIndex = index;
		// Free the old viewport
		if (m_pViewport != NULL)
		{
			//g_pDXFM->FreeViewport(m_iIndex);
			m_pViewport = NULL;
		}
		// Can't allocate a viewport if the engine isn't in-game
		if(!engine->IsInGame())
			return;
		// Set the new viewport
		m_pViewport = g_pDXFM->GetViewport(m_iIndex, true);
		m_bViewportIsDirty = false;
	}

	// Add index to name
	const char* baseName = "Viewport";
	const char* namePrefix = "Primary ";
	const char* nameSuffix = "";
	int count = g_pDXFM->GetViewportCount();

	if (count == 1 || count > 2)
	{
		namePrefix = "";
	}
	if (count > 2)
	{
		namePrefix = "";
		// Identify by numbers
		int indexIdentifier = m_iIndex + 1;
		char* indexIdentifierString = new char[16];
		Q_snprintf(indexIdentifierString, 16, " %d", indexIdentifier);
		nameSuffix = indexIdentifierString;
	}
	else if (m_iIndex == 1)
	{
		namePrefix = "Secondary ";
	}

	// Calculate the length of the combined string
	int combinedLength = Q_strlen(namePrefix) + Q_strlen(baseName) + Q_strlen(nameSuffix) + 1;

	// Allocate memory for the combined string
	char* combinedName = new char[combinedLength];

	// Combine the strings
	Q_strcpy(combinedName, namePrefix);
	Q_strcat(combinedName, baseName, combinedLength);
	Q_strcat(combinedName, nameSuffix, combinedLength);

	// Set the name
	SetName(combinedName);
}

bool DXUIViewport::CreateContextMenu()
{	
	// Recreate context menu if it's NULL or invalid
	bool isNull = (m_pContextMenu == NULL || m_pContextMenu == (Menu*)DXFM_INVALID_POINTER);
	if (!isNull)
	{
		m_pContextMenu->DeleteAllItems();
		delete m_pContextMenu;
		m_pContextMenu = NULL;
	}

	// Attempt to create the context menu
	m_pContextMenu = new Menu(this, "ContextMenu");

	// Stop if the context menu is still NULL
	if (m_pContextMenu == NULL || m_pContextMenu == (Menu*)DXFM_INVALID_POINTER)
		return false;

	// Add menu items
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
	
	// Hide for now
	m_pContextMenu->SetVisible(false);
	m_pContextMenu->SetParent(this);
	m_pContextMenu->AddActionSignalTarget(this);
	return true;
}

void DXUIViewport::OpenContextMenu()
{
	// Get mouse position
	int x, y;
	input()->GetCursorPos(x, y);

	// Offset the context menu so it doesn't overlap the mouse cursor
	x += 8;
	y += 8;

	// Show the context menu
	m_pContextMenu->SetPos(x, y);
	m_pContextMenu->SetVisible(true);
}

bool DXUIViewport::HandleKeyChange(ButtonCode_t key, bool isDown, bool wasDown)
{
    // Movement keys will move the camera
	bool keyHandled = false;
	
	/*
	// Accept key held inputs if mouse is hovering over the viewport
    if (m_bMouseCaptured || m_bMouseInRange)
    {
		// Set held variables if key is held
		if (key == m_iKeyForward)
		{
			m_bKeyHeldForward = isDown;
			keyHandled = true;
		}
		if (key == m_iKeyBackward)
		{
			m_bKeyHeldBackward = isDown;
			keyHandled = true;
		}
		if (key == m_iKeyLeft)
		{
			m_bKeyHeldLeft = isDown;
			keyHandled = true;
		}
		if (key == m_iKeyRight)
		{
			m_bKeyHeldRight = isDown;
			keyHandled = true;
		}
		if (key == m_iKeyUp)
		{
			m_bKeyHeldUp = isDown;
			keyHandled = true;
		}
		if (key == m_iKeyDown)
		{
			m_bKeyHeldDown = isDown;
			keyHandled = true;
		}
		if (key == m_iKeySpeed)
		{
			m_bKeyHeldSpeed = isDown;
			keyHandled = true;
		}
		if (key == m_iKeySlow)
		{
			m_bKeyHeldSlow = isDown;
			keyHandled = true;
		}
		if (key == m_iKeyRotate)
		{
			m_bKeyHeldRotate = isDown;
			keyHandled = true;
		}
		if (key == m_iKeyOrbit)
		{
			m_bKeyHeldOrbit = isDown;
			keyHandled = true;
		}
	}
	else if (!m_bMouseCaptured)
	{
		// Reset held variables
		m_bKeyHeldForward = false;
		m_bKeyHeldBackward = false;
		m_bKeyHeldLeft = false;
		m_bKeyHeldRight = false;
		m_bKeyHeldUp = false;
		m_bKeyHeldDown = false;
		m_bKeyHeldSpeed = false;
		m_bKeyHeldSlow = false;
		m_bKeyHeldRotate = false;
		m_bKeyHeldOrbit = false;
	}
	*/
    return keyHandled;
}

OverlayText* DXUIViewport::GetOverlayText(int slot)
{
	if (slot < 0 || slot >= m_vecOverlayText.Count())
		return NULL;
	return m_vecOverlayText[slot];
}

void DXUIViewport::SetOverlayText(OverlayText* overlayText, int slot)
{
	if (slot < 0)
		return;
	if (slot >= m_vecOverlayText.Count())
		m_vecOverlayText.SetCount(slot + 1);
	m_vecOverlayText[slot] = overlayText;
}

void DXUIViewport::SetOverlayText(const wchar_t* text, int slot, OverlayAnchor anchor, Color textColor, Vector2D textOffset)
{
	SetOverlayText(new OverlayText(text, anchor, textColor, textOffset), slot);
}

void DXUIViewport::SetOverlayText(const wchar_t* text, int slot, OverlayAnchor anchor, Color textColor, int textOffsetX, int textOffsetY)
{
	SetOverlayText(text, slot, anchor, textColor, Vector2D(textOffsetX, textOffsetY));
}

int DXUIViewport::AddOverlayText(OverlayText* overlayText)
{
	m_vecOverlayText.AddToTail(overlayText);
	return m_vecOverlayText.Count() - 1;
}

int DXUIViewport::AddOverlayText(const wchar_t* text, OverlayAnchor anchor, Color textColor, Vector2D textOffset)
{
	return AddOverlayText(new OverlayText(text, anchor, textColor, textOffset));
}

int DXUIViewport::AddOverlayText(const wchar_t* text, OverlayAnchor anchor, Color textColor, int textOffsetX, int textOffsetY)
{
	return AddOverlayText(text, anchor, textColor, Vector2D(textOffsetX, textOffsetY));
}

void DXUIViewport::RemoveOverlayText(int slot)
{
	if (slot < 0 || slot >= m_vecOverlayText.Count())
		return;
	delete m_vecOverlayText[slot];
	m_vecOverlayText.Remove(slot);
}

void DXUIViewport::ClearOverlayText()
{
	for (int i = 0; i < m_vecOverlayText.Count(); i++)
		delete m_vecOverlayText[i];
	m_vecOverlayText.RemoveAll();
}

int DXUIViewport::GetOverlayTextCount()
{
	return m_vecOverlayText.Count();
}
