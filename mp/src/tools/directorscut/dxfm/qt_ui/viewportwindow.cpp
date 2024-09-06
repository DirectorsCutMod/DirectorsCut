#include "viewportwindow.h"

#include <materialsystem/imesh.h>
#include <materialsystem/itexture.h>
#include <tier2/camerautils.h>
#include <istudiorender.h>
#include <KeyValues.h>

#include "dxfm.h"

CViewportWindow::CViewportWindow(QWindow* pParent, int index) : CMatSysWindow(pParent)
{
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

	// Draw the viewport
	if(engine->IsInGame() && !m_bViewportIsDirty && m_pViewport != NULL)
	{
		// Draw the viewport with texture ID
		int nTextureID = m_pViewport->GetViewportTexID();
		g_pMatSystemSurface->DrawSetTexture(nTextureID);
		g_pMatSystemSurface->DrawTexturedRect(fixedX, fixedY, fixedX + fixedW, fixedY + fixedH);
	}

	// If the work camera is active, add a translucent blue border (64, 192, 255, 64) to indicate it when moving the camera
	/*
	if(m_bWorkCameraActive && m_bMouseCaptured)
	{
		g_pMatSystemSurface->DrawSetColor(64, 192, 255, 64);
		g_pMatSystemSurface->DrawOutlinedRect(viewportX, viewportY, viewportX + viewportW, viewportY + viewportH);
	}
	*/
}

bool CViewportWindow::event(QEvent* ev)
{
	// handle update events
	if(ev->type() == QEvent::UpdateRequest)
	{
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

#include "viewportwindow.h.moc"