//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Puppet entity for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "gamestringpool.h"
#include "datacache/imdlcache.h"
#include "networkstringtable_clientdll.h"
#include "dxpuppet.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

CDirectorsCutPuppet::CDirectorsCutPuppet()
{
	m_BoneAccessor.SetWritableBones(BONE_USED_BY_ANYTHING);
	m_BoneAccessor.SetReadableBones(BONE_USED_BY_ANYTHING);
}

CDirectorsCutPuppet::~CDirectorsCutPuppet()
{
}

void CDirectorsCutPuppet::GetRenderBounds(Vector& theMins, Vector& theMaxs)
{
	VectorCopy(Vector(-16384, -16384, -16384), theMins);
	VectorCopy(Vector(16384, 16384, 16384), theMaxs);
}

float CDirectorsCutPuppet::GetFlexWeight(LocalFlexController_t index)
{
	if (index >= 0 && index < GetNumFlexControllers())
	{
		return forcedFlexes[index];
	}
	return 0.0;
}

void CDirectorsCutPuppet::SetFlexWeight(LocalFlexController_t index, float value)
{
	if (index >= 0 && index < GetNumFlexControllers())
	{
		forcedFlexes[index] = value;
	}
}

void CDirectorsCutPuppet::Simulate()
{
	C_BaseFlex::Simulate();
	for (int i = 0; i < GetNumFlexControllers(); i++)
	{
		C_BaseFlex::SetFlexWeight((LocalFlexController_t)i, forcedFlexes[i]);
	}
}

bool CDirectorsCutPuppet::SetModel(const char* pModelName)
{
	C_BaseFlex::SetModel(pModelName);
	return true;
}

void CDirectorsCutPuppet::PoseBones(int bonenumber, Vector pos, QAngle ang)
{
	posadds[bonenumber] = pos;
	anglehelper[bonenumber] = ang;
	deltaApplied = true;
}
	

bool CDirectorsCutPuppet::SetupBones(matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
{
	for (int i = 0; i < MAXSTUDIOBONES; i++)
	{
		AngleQuaternion(anglehelper[i], qadds[i]);
	}
	m_BoneAccessor.SetWritableBones(BONE_USED_BY_ANYTHING);
	m_BoneAccessor.SetReadableBones(BONE_USED_BY_ANYTHING);
	return C_BaseFlex::SetupBones(pBoneToWorldOut, nMaxBones, boneMask, currentTime, deltaApplied, posadds, qadds);
}

inline matrix3x4_t& CDirectorsCutPuppet::GetBoneForWrite(int iBone)
{
	m_BoneAccessor.SetWritableBones(BONE_USED_BY_ANYTHING);
	m_BoneAccessor.SetReadableBones(BONE_USED_BY_ANYTHING);
	return C_BaseFlex::GetBoneForWrite(iBone);
}

/*

void CDirectorsCutPuppet::ApplyBoneMatrixTransform(matrix3x4_t& transform)
{
	m_BoneAccessor.SetWritableBones(BONE_USED_BY_ANYTHING);
	m_BoneAccessor.SetReadableBones(BONE_USED_BY_ANYTHING);
	PushAllowBoneAccess(true, true, "CDirectorsCutPuppet::ApplyBoneMatrixTransform");
	CStudioHdr* hdr = GetModelPtr();
	if (hdr != NULL)
	{
		if (initializedBones)
		{
			// If origin/angles are dirty (old), add their differences to the bone matrix
			Vector origin = GetAbsOrigin();
			QAngle angles = GetAbsAngles();
			if (origin != dirtyOrigin || angles != dirtyAngles)
			{
				Vector diffOrigin = origin - dirtyOrigin;
				QAngle diffAngles = angles - dirtyAngles;
				Vector boneOrigin;
				QAngle boneAngles;
				for (int i = 0; i < hdr->numbones(); i++)
				{
					MatrixAngles(boneMatrices[i], boneAngles, boneOrigin);
					boneAngles += diffAngles;
					boneOrigin += diffOrigin;
					AngleMatrix(boneAngles, boneOrigin, boneMatrices[i]);
				}
				dirtyOrigin = origin;
				dirtyAngles = angles;
			}
		}
		else
		{
			dirtyOrigin = GetAbsOrigin();
			dirtyAngles = GetAbsAngles();
		}
		for (int i = 0; i < hdr->numbones(); i++)
		{
			matrix3x4_t& bone = GetBoneForWrite[i];
			mstudiobone_t* bonePtr = hdr->pBone[i];
			char* name = bonePtr->pszName();

			if(!initializedBones)
			{
				// Initialize bone matrices
				MatrixCopy(bone, boneMatrices[i]);
			}

			matrix3x4_t oldBone;
			MatrixCopy(bone, oldBone);
			
			// Write new bone matrices
			MatrixCopy(boneMatrices[i], bone);
			
			// compare name with "ValveBiped.Bip01_Head1"
			bool compare0 = (oldBone[0][0] != bone[0][0] || oldBone[0][1] != bone[0][1] || oldBone[0][2] != bone[0][2] || oldBone[0][3] != bone[0][3]);

			if (Q_strcmp(name, "ValveBiped.Bip01_Head1") != 0 && (compare0))
				Msg("New bone matrix: %f %f %f %f\n", bone[0][0], bone[0][1], bone[0][2], bone[0][3]);
		}
		if (!initializedBones)
			initializedBones = true;
	}
	PopBoneAccess("CDirectorsCutPuppet::ApplyBoneMatrixTransform");
	C_BaseAnimating::ApplyBoneMatrixTransform(transform);
}

*/
