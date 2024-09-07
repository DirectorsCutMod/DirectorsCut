#pragma once

#include "toolframework/itoolsystem.h"
#include "tooldictionary.h"
#include "soundinfo.h"
#include "keyvalues.h"
#include "cdll_int.h"
#include <materialsystem/imaterialproxyfactory.h>
#include "dx_viewport.h"

#define DXFM_VERSION_0 "0"
#define DXFM_VERSION_1 "0"
#define DXFM_VERSION_2 "0"
#define DXFM_VERSION_3 "1"
#define DXFM_VERSION_STAGE "pre-alpha"
#define DXFM_VERSION_STAGE_FORMAL "Pre-Alpha"

#define DXFM_VERSION DXFM_VERSION_0 "." DXFM_VERSION_1 "." DXFM_VERSION_2 "." DXFM_VERSION_3
#define DXFM_VERSION_STRING DXFM_VERSION " (" DXFM_VERSION_STAGE ")"

#define DXFM_PRODUCT_NAME "Director's Cut"
#define DXFM_PRODUCT_NAME_FULL DXFM_PRODUCT_NAME " [" DXFM_VERSION_STAGE_FORMAL "]"

#define DXFM_AUTHOR DXFM_PRODUCT_NAME " Contributors"

#define DXFM_INVALID_POINTER 0xFFEEFFEE

// Currently blank, but might be worth filling in if you need mat proxies
class CMaterialProxyFactory : public IMaterialProxyFactory
{
public:
	virtual IMaterialProxy* CreateProxy(const char* proxyName) { return nullptr; }
	virtual void DeleteProxy(IMaterialProxy* pProxy) { }
};
static CMaterialProxyFactory s_materialProxyFactory;

class DXFM : public IToolSystem
{
public:
    DXFM();
    virtual const char* GetToolName();
    virtual bool Init();
    virtual void Shutdown();
    virtual bool ClientInit(CreateInterfaceFn clientFactory);
    virtual void OnToolActivate();
    virtual void OnToolDeactivate();
    virtual bool ServerInit(CreateInterfaceFn serverFactory);
    virtual void ServerShutdown();
    virtual void ClientShutdown();
    virtual bool CanQuit();
    virtual void PostMessage(HTOOLHANDLE hEntity, KeyValues* message);
    virtual void Think(bool finalTick);
    virtual void ServerLevelInitPreEntity();
    virtual void ServerLevelInitPostEntity();
    virtual void ServerLevelShutdownPreEntity();
    virtual void ServerLevelShutdownPostEntity();
    virtual void ServerFrameUpdatePreEntityThink();
    virtual void ServerFrameUpdatePostEntityThink();
    virtual void ServerPreClientUpdate();
    virtual void ServerPreSetupVisibility();
    virtual const char* GetEntityData(const char* pActualEntityData);
    virtual void ClientLevelInitPreEntity();
    virtual void ClientLevelInitPostEntity();
    virtual void ClientLevelShutdownPreEntity();
    virtual void ClientLevelShutdownPostEntity();
    virtual void ClientPreRender();
    virtual void ClientPostRender();
    virtual void AdjustEngineViewport(int &x, int &y, int &width, int &height);
    virtual bool SetupEngineView(Vector &origin, QAngle &angles, float &fov);
    virtual bool SetupAudioState(AudioState_t &audioState);
    virtual bool ShouldGameRenderView();
    virtual bool IsThirdPersonCamera();
    virtual bool IsToolRecording();
    virtual IMaterialProxy* LookupProxy(const char *proxyName);
    virtual bool TrapKey(ButtonCode_t key, bool down);
    virtual bool GetSoundSpatialization(int iUserData, int guid, SpatializationInfo_t &info);
    virtual void RenderFrameBegin();
    virtual void RenderFrameEnd();
    virtual void HostRunFrameBegin();
    virtual void HostRunFrameEnd();
    virtual void VGui_PreRender(int paintMode);
    virtual void VGui_PostRender(int paintMode);
    virtual void VGui_PreSimulate();
    virtual void VGui_PostSimulate();
    void SetToolActive(bool active);
    void ToggleTool();
    bool IsToolActive();
    int AllocateViewport();
    bool AllocateViewport(int index);
    void FreeViewport(int index);
    DXViewport* GetViewport(int index, bool create = false);
    int GetViewportCount();
    float GetFrameTime();
    bool GetShouldHideEngineWindow();
    void SetShouldHideEngineWindow(bool hide);
    void HideOrShowEngineWindow(bool hide);
    void* GetEngineWindowHandle();
private:
    bool UpdateKeyState(ButtonCode_t key, bool down);
    bool HandleKeyChange(ButtonCode_t key, bool isDown, bool wasDown);
    bool bShouldHideEngineWindow = true;
    int iKeyWasDownFlags = 0;
    int iKeyIsDownFlags = 0;
    CUtlVector<DXViewport*> m_vecViewports;
    float ft; // how much time has passed since the last frame
    float ft_cur;
    void* pHWND = (void*)0xFFEEFFEE; // HWND, windows.h isn't included here
    bool bIsWindowHidden = false;
    bool bIsToolActive = false;
    bool bUseVGUI = false;
    bool bQtPort = true;
};

extern DXFM* g_pDXFM;
