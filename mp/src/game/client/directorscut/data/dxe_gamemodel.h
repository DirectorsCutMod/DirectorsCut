//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Game model for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#ifndef _DIRECTORSCUT_DXE_GAMEMODEL_H_
#define _DIRECTORSCUT_DXE_GAMEMODEL_H_

#include "dxelement.h"
#include "kvhelpers.h"
#include "dxe_dag.h"
#include "../entities/dxpuppet.h"

class DxeGameModel : public DxeDag
{
public:
    DxeGameModel(const char* name);
    DxeGameModel(const char* name, const char* typeName);
    void InitElement() override;
    // Attributes
    KvFloatArray* GetFlexWeights() { return (KvFloatArray*)FindKey("flexWeights"); }
    void SetModelName(const char* modelName) { SetString("modelName", modelName); }
    const char* GetModelName() { return GetString("modelName"); }
    void SetSkin(int skin) { SetInt("skin", skin); }
    int GetSkin() { return GetInt("skin"); }
    void SetBody(int body) { SetInt("body", body); }
    int GetBody() { return GetInt("body"); }
    void SetSequence(int sequence) { SetInt("sequence", sequence); }
    int GetSequence() { return GetInt("sequence"); }
    void SetFlags(int flags) { SetInt("flags", flags); }
    int GetFlags() { return GetInt("flags"); }
    KvDxElementArray* GetBones() { return (KvDxElementArray*)FindKey("bones"); }
    KvDxElementArray* GetGlobalFlexControllers() { return (KvDxElementArray*)FindKey("globalFlexControllers"); }
    void SetComputeBounds(bool computeBounds) { SetBool("computeBounds", computeBounds); }
    bool GetComputeBounds() { return GetBool("computeBounds"); }
    void SetEvaluateProcedualBones(bool evaluateProcedualBones) { SetBool("evaluateProcedualBones", evaluateProcedualBones); }
    KvStringArray* GetFlexNames() { return (KvStringArray*)FindKey("flexnames"); }
    DxElement* GetIllumPositionDag() { return (DxElement*)FindKey("illumPositionDag"); }
    void SetFullPath(const char* fullPath) { SetString("fullpath", fullPath); }
    const char* GetFullPath() { return GetString("fullpath"); }
    // Internal
    CDirectorsCutPuppet* GetPuppet() { return m_pPuppet; }
    void CreatePuppet(bool force = false);
    void UpdatePuppet();
    void ReleasePuppet();
private:
    CDirectorsCutPuppet* m_pPuppet = NULL;
};

#endif // _DIRECTORSCUT_DXE_GAMEMODEL_H_
