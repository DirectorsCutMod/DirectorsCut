//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: TimeFrame data for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#ifndef _DIRECTORSCUT_Dxe_TIMEFRAME_H_
#define _DIRECTORSCUT_Dxe_TIMEFRAME_H_

#include "dxelement.h"

class DxeTimeFrame : public DxElement
{
public:
	DxeTimeFrame(const char* name);
	DxeTimeFrame(const char* name, const char* typeName);
	void InitElement() override;
	// Attributes
	void SetStart(float time) { SetFloat("start", time); }
	float GetStart() { return GetFloat("start"); }
	void SetDuration(float time) { SetFloat("duration", time); }
	float GetDuration() { return GetFloat("duration"); }
	void SetOffset(float time) { SetFloat("offset", time); }
	float GetOffset() { return GetFloat("offset"); }
	void SetScale(float scale) { SetFloat("scale", scale); }
	float GetScale() { return GetFloat("scale", 1.0f); }
};

#endif // _DIRECTORSCUT_Dxe_TIMEFRAME_H_
