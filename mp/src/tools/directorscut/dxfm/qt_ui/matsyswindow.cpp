#include <qpa/qplatformwindow.h>

// Source tends to do funny stuff with defines. Let's just include it last just to be safe.
#include <tier2/tier2.h>
#include <materialsystem/imaterialsystem.h>
#include <materialsystem/materialsystem_config.h>
#include <materialsystem/itexture.h>

#include "matsyswindow.h"
#include "dxfm.h"

// Main Window

CMatSysWindow::CMatSysWindow(QWindow* pParent) : QWindow(pParent)
{
}

void CMatSysWindow::redraw()
{
	// No handle, no service
	QPlatformWindow* hnd = handle();
	if (!hnd)
		return;
	// Tell matsys we want to draw to this window
	g_pMaterialSystem->SetView((void*)handle()->winId());
	paint();
}

void CMatSysWindow::paint()
{
	int vx = 0;
	int vy = 0;
	int vw = this->width();
	int vh = this->height();

	// By default, let's just make it pink to let em know they need to fill this in.
	//g_pMatSystemSurface->DrawSetColor(255, 0, 255, 255);
	//g_pMatSystemSurface->DrawFilledRect(0, 0, vw, vh);

	g_pMaterialSystem->BeginFrame(0);

	CMatRenderContextPtr ctx(g_pMaterialSystem);
	ctx->Viewport(vx, vy, vw, vh);
	ctx->ClearColor3ub(0xFF, 0x00, 0xFF);
	ctx->ClearBuffers(true, false);

	g_pMaterialSystem->EndFrame();
	g_pMaterialSystem->SwapBuffers();
}

QImage CMatSysWindow::screenshot()
{
	// Make sure we're the current window, and draw a frame so we know it all looks right
	redraw();

	// If we're not exactly where the viewport's supposed to be, this'll look wrong
	int x, y, w, h;
	CMatRenderContextPtr ctx(g_pMaterialSystem);
	ctx->GetViewport(x, y, w, h);

	// Dump to the image using the same image format
	QImage img(w, h, QImage::Format_RGBA8888);
	ctx->ReadPixels(x, y, w, h, (unsigned char*)img.bits(), IMAGE_FORMAT_RGBA8888);

	// Qt handles the memory for us, so we don't have to return as a pointer. How nice!
	return img;
}

void CMatSysWindow::resizeEvent(QResizeEvent* ev)
{
	//redraw();
}

#include "matsyswindow.h.moc"