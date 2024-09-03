// qt needs to be included before source headers
#include <QApplication>
#include <QDir>
#include <QFile>
#include "ui.h"
#include "matsyswindow.h"

#include "dxfm.h"

#include "tier0/icommandline.h"
#include "tier1/tier1.h"
#include "tier0/memdbgon.h"


#include <vgui/isurface.h>
#include <vgui/IVGui.h>
#include <vgui/IInput.h>
#include "tier0/vprof.h"
#include <dx_vgui_controls/Panel.h>
#include <KeyValues.h>
#include "FileSystem.h"
#include "matsys_controls/matsyscontrols.h"
#include "vguimatsurface/IMatSystemSurface.h"
#include "vgui/isystem.h"
#include <vgui/ILocalize.h>
#include <tier3/tier3.h>
#include <steam/steam_api.h>
#include "dx_vgui_controls/animationcontroller.h"
#include <dx_vgui_controls/Frame.h>

using namespace vgui;

#include <vgui/IInputInternal.h>
#include <dx_vgui_controls/Controls.h>
#include "steam/steam_api.h"
#include "datacache/idatacache.h"
#include "engine/ienginesound.h"
#include "igameuifuncs.h"
#include "inputsystem/iinputsystem.h"
#include "tier0/icommandline.h"

#include "dx_ui_panel.h"

// qt!!!!!! we love qt!!! <3
QApplication* m_pApp;
CMainWindow* m_pMainWindow;

DXFM* g_pDXFM = NULL;

DXFM::DXFM()
{
	g_pDXFM = this;
}

const char *DXFM::GetToolName()
{
    return "Director's Cut";
}

bool DXFM::Init()
{
    return true;
}

bool DXFM::ClientInit(CreateInterfaceFn clientFactory)
{
    // qt!!!
    // TODO: Does this NEED to be in ClientInit or can it be in Init?
    
    // initialize QApplication and set it to m_pApp
    // this is required because qt will shut down if there is no QApplication instance
    int argc = 0;
    m_pApp = new QApplication(argc, nullptr);

    // get tool assets directory
    QString dir = QCoreApplication::applicationDirPath() + "/bin/tools/dxfm"; // steamapps\common\Source SDK Base 2013 Multiplayer\bin\tools\dxfm

    // Msg the qstring
    QByteArray ba = dir.toLocal8Bit();
    const char* pDir = ba.data();
    Msg("qt tools: %s\n", pDir);

    // define qdir!
    QDir::addSearchPath("tools", dir);

    // load dxfm.qss as the stylesheet
    QFile file("tools:stylesheets/dxfm.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    m_pApp->setStyleSheet(styleSheet);
    
    // window child of m_pApp
    m_pMainWindow = new CMainWindow(nullptr);
    m_pMainWindow->show();
    m_pMainWindow->init();
    return true;
}

void DXFM::Shutdown()
{
    // run vgui frame
    ivgui()->RunFrame();
}

void DXFM::OnToolActivate()
{
    DXUIPanel::SetEditorVisibility(true);

    // run vgui frame
    ivgui()->RunFrame();

    // ask vgui editor to populate itself
    DXUIPanel* editor = DXUIPanel::GetEditor();
    if (editor)
        editor->PopulateEditor();
}

void DXFM::OnToolDeactivate()
{
    DXUIPanel::SetEditorVisibility(false);
}

bool DXFM::ServerInit(CreateInterfaceFn serverFactory) {
    return true;
}

void DXFM::ServerShutdown()
{
}

void DXFM::ClientShutdown()
{
    // get rid of qt </3
    delete m_pMainWindow;
    delete m_pApp;
    m_pMainWindow = nullptr;
    m_pApp = nullptr;

    // BUG: crashes, what didn't we shut down?
}

bool DXFM::CanQuit() {
    return true;
}

void DXFM::PostMessage(HTOOLHANDLE hEntity, KeyValues* message)
{
}

void DXFM::Think(bool finalTick)
{
}

void DXFM::ServerLevelInitPreEntity()
{
}

void DXFM::ServerLevelInitPostEntity()
{
}

void DXFM::ServerLevelShutdownPreEntity()
{
}

void DXFM::ServerLevelShutdownPostEntity()
{
}

void DXFM::ServerFrameUpdatePreEntityThink()
{
}

void DXFM::ServerFrameUpdatePostEntityThink()
{
}

void DXFM::ServerPreClientUpdate()
{
}

void DXFM::ServerPreSetupVisibility()
{
}

const char* DXFM::GetEntityData(const char* pActualEntityData)
{
    return pActualEntityData;
}

void DXFM::ClientLevelInitPreEntity()
{
}

void DXFM::ClientLevelInitPostEntity()
{
}

void DXFM::ClientLevelShutdownPreEntity()
{
}

void DXFM::ClientLevelShutdownPostEntity()
{
}

void DXFM::ClientPreRender()
{
}

void DXFM::ClientPostRender()
{
    // TODO: pre or post render? what's the difference?
    QCoreApplication::sendPostedEvents();
    QCoreApplication::processEvents();
}

void DXFM::AdjustEngineViewport(int &x, int &y, int &width, int &height)
{
}

bool DXFM::SetupEngineView(Vector &origin, QAngle &angles, float &fov)
{
    return false;
}

bool DXFM::SetupAudioState(AudioState_t &audioState)
{
    return false;
}

bool DXFM::ShouldGameRenderView()
{
    return true;
}

bool DXFM::IsThirdPersonCamera() 
{
    return false;
}

bool DXFM::IsToolRecording()
{
    return false;
}

IMaterialProxy* DXFM::LookupProxy(const char *proxyName)
{
    return NULL;
}

bool DXFM::TrapKey(ButtonCode_t key, bool down) {
    return UpdateKeyState(key, down);
}

bool DXFM::GetSoundSpatialization(int iUserData, int guid, SpatializationInfo_t &info)
{
    return false;
}

void DXFM::RenderFrameBegin()
{
}

void DXFM::RenderFrameEnd()
{
}

void DXFM::HostRunFrameBegin()
{
}

void DXFM::HostRunFrameEnd()
{
}

void DXFM::VGui_PreRender(int paintMode)
{
}

void DXFM::VGui_PostRender(int paintMode)
{
}

void DXFM::VGui_PreSimulate()
{
    // Start counting time
    ft_cur = Plat_FloatTime();
}

void DXFM::VGui_PostSimulate()
{
    // Calculate time passed
    ft = Plat_FloatTime() - ft_cur;
}

bool DXFM::UpdateKeyState(ButtonCode_t key, bool down) {
    int keyBit = 1 << key;
    if (down)
        iKeyIsDownFlags |= keyBit;
    else
        iKeyIsDownFlags &= ~keyBit;
    bool isDown = (iKeyIsDownFlags & keyBit) != 0;
    bool wasDown = (iKeyWasDownFlags & keyBit) != 0;
    bool trap = false;
    if (isDown != wasDown)
        trap = HandleKeyChange(key, isDown, wasDown);
    iKeyWasDownFlags = iKeyIsDownFlags;
    return trap;
}

bool DXFM::HandleKeyChange(ButtonCode_t key, bool isDown, bool wasDown) {
    // Allow UI to trap key presses
    bool trap = DXUIPanel::HandleKeyChange(key, isDown, wasDown);
    if(trap == false)
    {
        // Pass through to global key handler
        if (key == KEY_F11 && isDown && !wasDown)
        {
            if(DXUIPanel::IsEditorVisible())
                OnToolDeactivate();
            else
                OnToolActivate();
            return true;
        }
    }
    return false;
}

int DXFM::AllocateViewport()
{
    // get first available flag in g_iAllocatedViewportFlags
    int i = 0;
    while (g_iAllocatedViewportFlags & (1 << i))
        i++;
    m_vecViewports.AddToTail(new DXViewport(i));
    return i;
}

bool DXFM::AllocateViewport(int index)
{
    // check if this index is available
    if (g_iAllocatedViewportFlags & (1 << index))
        return false;
    m_vecViewports.AddToTail(new DXViewport(index));
    return true;
}

void DXFM::FreeViewport(int index)
{
    // call ~DXViewport if this index is valid
    if (index >= 0 && index < m_vecViewports.Count())
    {
        delete m_vecViewports[index];
        m_vecViewports.Remove(index);
    }
    else
    {
        // clear flag in g_iAllocatedViewportFlags anyways
        g_iAllocatedViewportFlags &= ~(1 << index);
    }
}

DXViewport* DXFM::GetViewport(int index, bool create)
{
    if (index >= 0 && index < m_vecViewports.Count())
    {
        return m_vecViewports[index];
    }
    if (create)
    {
        AllocateViewport(index);
        return m_vecViewports[index];
    }
    return NULL;
}

int DXFM::GetViewportCount()
{
    return m_vecViewports.Count();
}

float DXFM::GetFrameTime()
{
    return ft;
}
