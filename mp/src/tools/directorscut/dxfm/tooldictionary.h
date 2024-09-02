#pragma once

#include "toolframework/itooldictionary.h"
#include "cdll_int.h"
#include "tier0/icommandline.h"
#include "tier1/tier1.h"
#include "interface.h"
#include "toolframework/ienginetool.h"
#include "ienginevgui.h"
#include "interface.h"
#include "vgui/VGUI.h"

#include "utllinkedlist.h"
#include "cdll_int.h"
#include "eiface.h"
#include <soundflags.h>
#include "mathlib/vector.h"
#include "materialsystem/materialsystemutil.h"
#include "cmodel.h"
#include "utlvector.h"
#include "engine/IEngineTrace.h"
#include "engine/IStaticPropMgr.h"
#include "networkvar.h"
#include <ivrenderview.h>

class IVModelRender;
class IVEngineClient;
class IVModelRender;
class IVRenderView;
class IMaterialSystem;
class IDataCache;
class IMDLCache;
class IVModelInfoClient;
class IEngineVGui;
class IFileSystem;
class IUniformRandomStream;
class CGaussianRandomStream;
class IEngineSound;
class IMatSystemSurface;
class IMaterialSystemHardwareConfig;
class IGameUIFuncs;
class CGlobalVarsBase;
class IInputSystem;

extern IVModelRender* modelrender;
extern IVModelRender* modelrender;
extern IVRenderView* render;
extern IMaterialSystem* materials;
extern IMaterialSystemHardwareConfig* g_pMaterialSystemHardwareConfig;
extern IDataCache* datacache;
extern IMDLCache* mdlcache;
extern IVModelInfoClient* modelinfo;
extern IEngineVGui* enginevgui;
extern IFileSystem* filesystem;
extern IUniformRandomStream* random;
extern CGaussianRandomStream* randomgaussian;
extern IEngineSound* enginesound;
extern IMatSystemSurface* g_pMatSystemSurface;
extern IGameUIFuncs* gameuifuncs;
extern CGlobalVarsBase* gpGlobals;
extern IInputSystem* inputsystem;

extern IVEngineClient* engine;
extern IEngineTool* enginetools;

class CToolDictionary : public IToolDictionary
{
public:
    virtual bool Connect( CreateInterfaceFn factory );
    virtual void Disconnect();
    virtual void* QueryInterface(const char *pInterfaceName);
    virtual InitReturnVal_t Init();
    virtual void Shutdown();
    virtual void CreateTools();
    virtual int GetToolCount() const;
    virtual IToolSystem* GetTool(int index);
private:
    CUtlVector<IToolSystem*> m_Tools;
};

static CToolDictionary g_ToolDictionary;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR( CToolDictionary, IToolDictionary, VTOOLDICTIONARY_INTERFACE_VERSION, g_ToolDictionary);
