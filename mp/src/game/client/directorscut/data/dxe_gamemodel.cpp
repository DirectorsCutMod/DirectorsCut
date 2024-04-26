//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Game model for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dxe_gamemodel.h"
#include <directorscut/directorscut.h>
#include <gamestringpool.h>

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

DxeGameModel::DxeGameModel(const char* name) : DxeDag(name, "DxeGameModel")
{
    InitElement();
};

DxeGameModel::DxeGameModel(const char* name, const char* typeName) : DxeDag(name, typeName)
{
    InitElement();
};

void DxeGameModel::InitElement()
{
    DxElement::InitElement();
    // Initial values
    AddSubKey(new KvFloatArray("flexWeights"));
    SetModelName("");
    SetSkin(0);
    SetBody(0);
    SetSequence(0);
    SetFlags(0);
    AddSubKey(new KvDxElementArray("bones"));
    AddSubKey(new KvDxElementArray("globalFlexControllers"));
    SetComputeBounds(false);
    SetEvaluateProcedualBones(false);
    AddSubKey(new KvStringArray("flexnames"));
    AddSubKey(new DxElement("illumPositionDag"));
    SetFullPath("");
    // Factory attributes
    AddFactoryAttribute("flexWeights");
    AddFactoryAttribute("modelName");
    AddFactoryAttribute("skin");
    AddFactoryAttribute("body");
    AddFactoryAttribute("sequence");
    AddFactoryAttribute("flags");
    AddFactoryAttribute("bones");
    AddFactoryAttribute("globalFlexControllers");
    AddFactoryAttribute("computeBounds");
    AddFactoryAttribute("evaluateProcedualBones");
    AddFactoryAttribute("flexnames");
    AddFactoryAttribute("illumPositionDag");
    AddFactoryAttribute("fullpath");
}

void DxeGameModel::CreatePuppet(bool force)
{
    if(m_pPuppet != NULL && !force)
        return;
    const char* pszModelName = GetModelName();
    if (pszModelName != nullptr)
    {
        // Load model
        model_t* pModel = DirectorsCutGameSystem().LoadModel(pszModelName);
        if (pModel != nullptr)
        {
            m_pPuppet = new CDirectorsCutPuppet();
            m_pPuppet->SetModelPointer(pModel);
        }
    }
}

void DxeGameModel::UpdatePuppet()
{
    if(m_pPuppet == NULL)
        CreatePuppet();
    if(m_pPuppet != NULL)
    {
        // Set puppet position and orientation
        DxeTransform* pTransform = (DxeTransform*)FindKey("transform");
        if(pTransform != NULL)
        {
            Vector vecPosition = pTransform->GetPosition()->GetVector();
            Quaternion qOrientation = pTransform->GetOrientation()->GetQuaternion();
            QAngle angOrientation;
            QuaternionAngles(qOrientation, angOrientation);
            m_pPuppet->SetAbsOrigin(vecPosition);
            m_pPuppet->SetAbsAngles(angOrientation);
        }
        // Update model name if its value is different
        const char* pszModelName = GetModelName();
        if (pszModelName != nullptr)
        {
            string_t iszModelName = m_pPuppet->GetModelName();
            string_t iszNewModelName = AllocPooledString(pszModelName);
            if (iszModelName != iszNewModelName)
            {
                model_t* pModel = DirectorsCutGameSystem().LoadModel(pszModelName);
                if (pModel != nullptr)
                {
                    m_pPuppet->SetModelPointer(pModel);
                }
            }
        }
        // Loop through all bones and set model pointer's bones
        KvDxElementArray* pBones = GetBones();
        if(pBones != NULL)
        {
            for(int i = 0; i < pBones->GetSize(); i++)
            {
                DxeTransform* pBone = (DxeTransform*)pBones->GetElement(i);
                if(pBone != NULL)
                {
                    Vector vecPosition = pBone->GetPosition()->GetVector();
                    Quaternion qOrientation = pBone->GetOrientation()->GetQuaternion();
                    QAngle angOrientation;
                    QuaternionAngles(qOrientation, angOrientation);
                    m_pPuppet->PoseBones(i, vecPosition, angOrientation);
                }
            }
        }
    }
}

void DxeGameModel::ReleasePuppet()
{
    if(m_pPuppet != NULL)
    {
        m_pPuppet->Release();
        m_pPuppet = NULL;
    }
}
