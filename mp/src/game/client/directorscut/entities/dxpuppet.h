//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Puppet entity for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#ifndef _DIRECTORSCUT_DXPUPPET_H_
#define _DIRECTORSCUT_DXPUPPET_H_

#include "c_baseentity.h"
#include "c_baseanimating.h"
#include "basetypes.h"
#include "flashlighteffect.h"
#include "c_baseflex.h"
#include "c_point_camera.h"

class CDirectorsCutPuppet : public C_BaseFlex
{
	DECLARE_CLASS(CDirectorsCutPuppet, C_BaseFlex);
public:
	CDirectorsCutPuppet();
	~CDirectorsCutPuppet();
	virtual void	Simulate();
	virtual bool SetModel(const char* pModelName);
	void PoseBones(int bonenumber, Vector pos, QAngle ang);
	virtual matrix3x4_t& GetBoneForWrite(int iBone);
	virtual bool SetupBones(matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);
	virtual float GetFlexWeight(LocalFlexController_t index);
	virtual void SetFlexWeight(LocalFlexController_t index, float value);
	//virtual void ApplyBoneMatrixTransform(matrix3x4_t& transform);
	Vector posadds[MAXSTUDIOBONES];
	QAngle anglehelper[MAXSTUDIOBONES];
	QuaternionAligned qadds[MAXSTUDIOBONES];
	float forcedFlexes[MAXSTUDIOFLEXCTRL];
	virtual void GetRenderBounds(Vector& theMins, Vector& theMaxs);
	bool deltaApplied = false;
};

#endif // _DIRECTORSCUT_DXPUPPET_H_
