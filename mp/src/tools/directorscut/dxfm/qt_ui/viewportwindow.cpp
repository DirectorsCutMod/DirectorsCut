#include <QPainter>

#include "viewportwindow.h"

#include <materialsystem/imesh.h>
#include <materialsystem/itexture.h>
#include <tier2/camerautils.h>
#include <istudiorender.h>
#include <KeyValues.h>
#include "dx_vgui_controls/editablepanel.h"

#include "dxfm.h"

// convars
ConVar dx_qt_viewport_speed_min( "dx_qt_viewport_speed_min", "100.0", 0, "Default and minimum camera speed while moving" );
ConVar dx_qt_viewport_speed_max( "dx_qt_viewport_speed_max", "1000.0", 0, "Maximum camera speed while moving" );
ConVar dx_qt_viewport_speed_multiplier_sprint( "dx_qt_viewport_speed_multiplier_sprint", "5.0", 0, "Camera speed multiplier while holding the sprint key" );
ConVar dx_qt_viewport_speed_multiplier_walk( "dx_qt_viewport_speed_multiplier_walk", "0.2", 0, "Camera speed multiplier while holding the walk key" );
ConVar dx_qt_viewport_sensitivity( "dx_qt_viewport_sensitivity", "0.3", 0, "Mouse sensitivity while moving the camera" );

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

CViewportWindow::CViewportWindow(QWindow* pParent, int index) : CMatSysWindow(pParent)
{
	// TODO: Stop reliance on VGUI
	m_hFont = vgui::scheme()->GetIScheme( vgui::scheme()->GetScheme( "ClientScheme" ) )->GetFont( "Trebuchet18", true );
	SetViewport(index);
}

CViewportWindow::~CViewportWindow()
{
	g_pDXFM->FreeViewport(m_iIndex);
}

void CViewportWindow::paint()
{
	// ask for an update
	requestUpdate();

	// we need a viewport!
	if (m_pViewport == NULL && !m_bViewportIsDirty)
	{
		m_bViewportIsDirty = true;
		SetViewport(m_iIndex);
		return;
	}

	int windowWidth = this->width();
	int windowHeight = this->height();
	int viewportWidth = m_pViewport->GetViewportWidth();
	int viewportHeight = m_pViewport->GetViewportHeight();

	// Draw black background
	g_pMatSystemSurface->DrawSetColor(0, 0, 0, 255);
	g_pMatSystemSurface->DrawFilledRect(0, 0, viewportWidth, viewportHeight);

	// FIXME: THIS IS AN INSANE HACK

	// Scale up the window to match viewport while window maintaining aspect ratio
	float windowAspectRatio = (float)windowWidth / (float)windowHeight;
	float viewportAspectRatio = (float)viewportWidth / (float)viewportHeight;
	bool windowWider = windowAspectRatio > viewportAspectRatio;

	int windowScaledWidth = windowWider ? (int)(windowHeight * viewportAspectRatio) : windowWidth;
	int windowScaledHeight = windowWider ? windowHeight : (int)(windowWidth / viewportAspectRatio);

	int diffWidth = windowWidth - windowScaledWidth;
	int diffHeight = windowHeight - windowScaledHeight;

	// Subtract from the viewport width and height and center the viewport
	int fixedX = diffWidth / 2;
	int fixedY = diffHeight / 2;
	int fixedW = viewportWidth - diffWidth;
	int fixedH = viewportHeight - diffHeight;

	float pixelWidth = !windowWider ? 1.0f : (float)windowWidth / (float)windowScaledWidth;
	float pixelHeight = windowWider ? 1.0f : (float)windowHeight / (float)windowScaledHeight;

	// Draw the viewport
	if(engine->IsInGame() && !m_bViewportIsDirty && m_pViewport != NULL)
	{
		// Draw the viewport with texture ID
		int nTextureID = m_pViewport->GetViewportTexID();
		g_pMatSystemSurface->DrawSetTexture(nTextureID);
		g_pMatSystemSurface->DrawTexturedRect(fixedX, fixedY, fixedX + fixedW, fixedY + fixedH);

		// If the work camera is active, add a translucent blue border to indicate it when moving the camera
		if(m_bWorkCameraActive && m_bMouseCaptured)
		{
			int thickness = 4;
			float thicknessX = thickness * pixelWidth;
			float thicknessY = thickness * pixelHeight;
			g_pMatSystemSurface->DrawSetColor(64, 192, 255, 255);
			g_pMatSystemSurface->DrawFilledRect(fixedX + thicknessX, fixedY, fixedX + fixedW - thicknessX, fixedY + thicknessY);
			g_pMatSystemSurface->DrawFilledRect(fixedX, fixedY, fixedX + thicknessX, fixedY + fixedH);
			g_pMatSystemSurface->DrawFilledRect(fixedX + fixedW - thicknessX, fixedY, fixedX + fixedW, fixedY + fixedH);
			g_pMatSystemSurface->DrawFilledRect(fixedX + thicknessX, fixedY + fixedH - thicknessY, fixedX + fixedW - thicknessX, fixedY + fixedH);
		}
		
		// Each anchor has an offset increment so they don't overlap each other
		int anchorOffsetIncrement = 32;
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
			textHeight = 16; // this makes the top and bottom anchors symmetrical

			// Calculate text position and offsets
			int textX = 0;
			int textY = 0;
			switch(overlayText->GetAnchor())
			{
			case OVERLAY_ANCHOR_TOP_LEFT:
				textX = overlayText->GetTextOffsetX();
				textY = overlayText->GetTextOffsetY() + anchorOffsetTopLeft;
				anchorOffsetTopLeft += anchorOffsetIncrement;
				break;
			case OVERLAY_ANCHOR_TOP_CENTER:
				textX = (viewportWidth - textWidth) / 2 + overlayText->GetTextOffsetX();
				textY = overlayText->GetTextOffsetY() + anchorOffsetTopCenter;
				anchorOffsetTopCenter += anchorOffsetIncrement;
				break;
			case OVERLAY_ANCHOR_TOP_RIGHT:
				textX = viewportWidth - textWidth + overlayText->GetTextOffsetX();
				textY = overlayText->GetTextOffsetY() + anchorOffsetTopRight;
				anchorOffsetTopRight += anchorOffsetIncrement;
				break;
			case OVERLAY_ANCHOR_CENTER_LEFT:
				textX = overlayText->GetTextOffsetX();
				textY = (viewportHeight - textHeight) / 2 + overlayText->GetTextOffsetY() + anchorOffsetCenterLeft;
				anchorOffsetCenterLeft += anchorOffsetIncrement;
				break;
			case OVERLAY_ANCHOR_CENTER:
				textX = (viewportWidth - textWidth) / 2 + overlayText->GetTextOffsetX();
				textY = (viewportHeight - textHeight) / 2 + overlayText->GetTextOffsetY() + anchorOffsetCenter;
				anchorOffsetCenter += anchorOffsetIncrement;
				break;
			case OVERLAY_ANCHOR_CENTER_RIGHT:
				textX = viewportWidth - textWidth + overlayText->GetTextOffsetX();
				textY = (viewportHeight - textHeight) / 2 + overlayText->GetTextOffsetY() + anchorOffsetCenterRight;
				anchorOffsetCenterRight += anchorOffsetIncrement;
				break;
			// Bottom offsets increment by subtracting, so they go up
			case OVERLAY_ANCHOR_BOTTOM_LEFT:
				textX = overlayText->GetTextOffsetX();
				textY = viewportHeight - textHeight + overlayText->GetTextOffsetY() + anchorOffsetBottomLeft;
				anchorOffsetBottomLeft -= anchorOffsetIncrement;
				break;
			case OVERLAY_ANCHOR_BOTTOM_CENTER:
				textX = (viewportWidth - textWidth) / 2 + overlayText->GetTextOffsetX();
				textY = viewportHeight - textHeight + overlayText->GetTextOffsetY() + anchorOffsetBottomCenter;
				anchorOffsetBottomCenter -= anchorOffsetIncrement;
				break;
			case OVERLAY_ANCHOR_BOTTOM_RIGHT:
				textX = viewportWidth - textWidth + overlayText->GetTextOffsetX();
				textY = viewportHeight - textHeight + overlayText->GetTextOffsetY() + anchorOffsetBottomRight;
				anchorOffsetBottomRight -= anchorOffsetIncrement;
				break;
			}

			// Set text offset and draw
			g_pMatSystemSurface->DrawSetTextPos(textX, textY);
			g_pMatSystemSurface->DrawPrintText(text, wcslen(text));
		}
	}
}

bool CViewportWindow::event(QEvent* ev)
{
	// handle update events
	if(ev->type() == QEvent::UpdateRequest)
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
				// Convars
				float minSpeed = dx_qt_viewport_speed_min.GetFloat();
				float maxSpeed = dx_qt_viewport_speed_max.GetFloat();
				float multiplierSprint = dx_qt_viewport_speed_multiplier_sprint.GetFloat();
				float multiplierWalk = dx_qt_viewport_speed_multiplier_walk.GetFloat();

				// Get frame time
				float ft = enginetools->ClientFrameTime();

				// If not holding a movement key, set m_flCameraMovementSpeed to default
				if (!m_bKeyHeldForward && !m_bKeyHeldBackward && !m_bKeyHeldLeft && !m_bKeyHeldRight && !m_bKeyHeldUp && !m_bKeyHeldDown)
				{
					m_flCameraMovementSpeed = minSpeed;
				}
				else
				{
					// Increase m_flCameraMovementSpeed by multiplier until it reaches cameraMovementSpeedMax
					if (m_flCameraMovementSpeed < maxSpeed)
						m_flCameraMovementSpeed += ( maxSpeed - minSpeed ) * 0.1f * ft;
					else
						m_flCameraMovementSpeed = maxSpeed;
				}

				// Get forward, right, up vectors
				Vector vecForward, vecRight, vecUp;
				AngleVectors(m_angWorkCameraAngles, &vecForward, &vecRight, &vecUp);

				// Hold Shift or Ctrl to speed up or slow down movement
				float flSpeed = 1.0f;
				if (m_bKeyHeldSprint)
					flSpeed = multiplierSprint;
				if (m_bKeyHeldWalk)
					flSpeed = multiplierWalk;

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
		}

		// Remove overlay text for no map if it exists
		if(m_iNoMapOverlayText != -1)
		{
			RemoveOverlayText(m_iNoMapOverlayText);
			m_iNoMapOverlayText = -1;
		}

		// Mark viewport as dirty if it's not in game
		if((!engine->IsInGame() || m_pViewport == NULL) && !m_bViewportIsDirty)
		{
			m_bViewportIsDirty = true;
			return true;
		}
		else
		{
			// Mark as dirty if viewport is null
			if(m_pViewport == NULL && !m_bViewportIsDirty)
			{
				m_bViewportIsDirty = true;
				SetViewport(m_iIndex);
				return true;
			}

			// If the editor isn't visible, don't render the viewport
			if (!g_pDXFM->IsToolActive())
				return true;

			// Draw!
			m_pViewport->DrawViewport(m_vecWorkCameraOrigin, m_angWorkCameraAngles, m_flWorkCameraFOV);
		}
		return true;
	}
	return QWindow::event(ev);
}

void CViewportWindow::mousePressEvent(QMouseEvent* ev)
{
	// Get mouse button code
	Qt::MouseButton code = ev->button();

	// Set the appropriate boolean for the mouse button that was pressed
	m_bMouseButtonHeldPrimary = (code == m_iMouseButtonPrimary);
	m_bMouseButtonHeldSecondary = (code == m_iMouseButtonSecondary);
	m_bMouseButtonHeldMiddle = (code == m_iMouseButtonMiddleButton);
	m_bMouseButtonHeldX1 = (code == m_iMouseButtonX1Button);
	m_bMouseButtonHeldX2 = (code == m_iMouseButtonX2Button);

	// Capture the mouse if the primary mouse button is held
	if (code == m_iMouseButtonPrimary)
	{
		// Warp the mouse to the center of the viewport
		QCursor::setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));
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
	}
}

void CViewportWindow::mouseReleaseEvent(QMouseEvent* ev)
{
	// Get mouse button code
	Qt::MouseButton code = ev->button();

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
	if (code == m_iMouseButtonPrimary)
	{
		m_bMouseCaptured = false;

		// Reset held keys
		m_bKeyHeldSprint = false;
		m_bKeyHeldWalk = false;
		m_bKeyHeldRotate = false;
		m_bKeyHeldOrbit = false;
		m_bKeyHeldForward = false;
		m_bKeyHeldBackward = false;
		m_bKeyHeldLeft = false;
		m_bKeyHeldRight = false;
		m_bKeyHeldUp = false;
		m_bKeyHeldDown = false;

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
	}
}

void CViewportWindow::mouseMoveEvent(QMouseEvent* ev)
{
	// Get mouse delta if mouse is captured
	if (m_bMouseCaptured)
	{
		// Needs to be in-game and a viewport must be allocated
		if (!engine->IsInGame() || !g_pDXFM->IsToolActive() || m_pViewport == NULL || m_bViewportIsDirty)
			return;

		// Get mouse delta
		QPoint center = mapToGlobal(QPoint(width() / 2, height() / 2));
		QPoint delta = ev->globalPos() - center;

		// invert Y
		delta.setY(-delta.y());

		// Get mouse sensitivity
		float mouseSensitivity = dx_qt_viewport_sensitivity.GetFloat();

		// Rotate camera
		QAngle angWorkCamera = QAngle(m_angWorkCameraAngles.x, m_angWorkCameraAngles.y, m_angWorkCameraAngles.z);
		angWorkCamera.y -= delta.x() * mouseSensitivity;
		angWorkCamera.x -= delta.y() * mouseSensitivity;
		angWorkCamera.x = clamp(angWorkCamera.x, -89.0f, 89.0f);
		m_angWorkCameraAngles = angWorkCamera;
			
		// Set mouse to middle of viewport
		QCursor::setPos(center);
	}
}

void CViewportWindow::wheelEvent(QWheelEvent* ev)
{
	if (m_bMouseCaptured)
	{
		// Needs to be in-game and a viewport must be allocated
		if (!engine->IsInGame() || !g_pDXFM->IsToolActive() || m_pViewport == NULL || m_bViewportIsDirty)
			return;

		// Adjust FOV of camera
		if (m_bWorkCameraActive)
		{
			m_flWorkCameraFOV -= ev->delta() > 0 ? 1 : -1;
			m_flWorkCameraFOV = clamp(m_flWorkCameraFOV, 1.0f, 179.0f);
		}
	}
}

void CViewportWindow::keyPressEvent(QKeyEvent* ev)
{
	if (m_bMouseCaptured)
	{
		// Set movement keys to true
		if (ev->key() == m_iKeySprint)
			m_bKeyHeldSprint = true;
		if (ev->key() == m_iKeyWalk)
			m_bKeyHeldWalk = true;
		if (ev->key() == m_iKeyRotate)
			m_bKeyHeldRotate = true;
		if (ev->key() == m_iKeyOrbit)
			m_bKeyHeldOrbit = true;
		if (ev->key() == m_iKeyForward)
			m_bKeyHeldForward = true;
		if (ev->key() == m_iKeyBackward)
			m_bKeyHeldBackward = true;
		if (ev->key() == m_iKeyLeft)
			m_bKeyHeldLeft = true;
		if (ev->key() == m_iKeyRight)
			m_bKeyHeldRight = true;
		if (ev->key() == m_iKeyUp)
			m_bKeyHeldUp = true;
		if (ev->key() == m_iKeyDown)
			m_bKeyHeldDown = true;
	}
}

void CViewportWindow::keyReleaseEvent(QKeyEvent* ev)
{
	if (m_bMouseCaptured)
	{
		// Set movement keys to false
		if (ev->key() == m_iKeySprint)
			m_bKeyHeldSprint = false;
		if (ev->key() == m_iKeyWalk)
			m_bKeyHeldWalk = false;
		if (ev->key() == m_iKeyRotate)
			m_bKeyHeldRotate = false;
		if (ev->key() == m_iKeyOrbit)
			m_bKeyHeldOrbit = false;
		if (ev->key() == m_iKeyForward)
			m_bKeyHeldForward = false;
		if (ev->key() == m_iKeyBackward)
			m_bKeyHeldBackward = false;
		if (ev->key() == m_iKeyLeft)
			m_bKeyHeldLeft = false;
		if (ev->key() == m_iKeyRight)
			m_bKeyHeldRight = false;
		if (ev->key() == m_iKeyUp)
			m_bKeyHeldUp = false;
		if (ev->key() == m_iKeyDown)
			m_bKeyHeldDown = false;
	}
}

void CViewportWindow::SetViewport(int index)
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
	setTitle(combinedName);
}

OverlayText* CViewportWindow::GetOverlayText(int slot)
{
	if (slot < 0 || slot >= m_vecOverlayText.Count())
		return NULL;
	return m_vecOverlayText[slot];
}

void CViewportWindow::SetOverlayText(OverlayText* overlayText, int slot)
{
	if (slot < 0)
		return;
	if (slot >= m_vecOverlayText.Count())
		m_vecOverlayText.SetCount(slot + 1);
	m_vecOverlayText[slot] = overlayText;
}

void CViewportWindow::SetOverlayText(const wchar_t* text, int slot, OverlayAnchor anchor, Color textColor, Vector2D textOffset)
{
	SetOverlayText(new OverlayText(text, anchor, textColor, textOffset), slot);
}

void CViewportWindow::SetOverlayText(const wchar_t* text, int slot, OverlayAnchor anchor, Color textColor, int textOffsetX, int textOffsetY)
{
	SetOverlayText(text, slot, anchor, textColor, Vector2D(textOffsetX, textOffsetY));
}

int CViewportWindow::AddOverlayText(OverlayText* overlayText)
{
	m_vecOverlayText.AddToTail(overlayText);
	return m_vecOverlayText.Count() - 1;
}

int CViewportWindow::AddOverlayText(const wchar_t* text, OverlayAnchor anchor, Color textColor, Vector2D textOffset)
{
	return AddOverlayText(new OverlayText(text, anchor, textColor, textOffset));
}

int CViewportWindow::AddOverlayText(const wchar_t* text, OverlayAnchor anchor, Color textColor, int textOffsetX, int textOffsetY)
{
	return AddOverlayText(text, anchor, textColor, Vector2D(textOffsetX, textOffsetY));
}

void CViewportWindow::RemoveOverlayText(int slot)
{
	if (slot < 0 || slot >= m_vecOverlayText.Count())
		return;
	delete m_vecOverlayText[slot];
	m_vecOverlayText.Remove(slot);
}

void CViewportWindow::ClearOverlayText()
{
	for (int i = 0; i < m_vecOverlayText.Count(); i++)
		delete m_vecOverlayText[i];
	m_vecOverlayText.RemoveAll();
}

int CViewportWindow::GetOverlayTextCount()
{
	return m_vecOverlayText.Count();
}


#include "viewportwindow.h.moc"