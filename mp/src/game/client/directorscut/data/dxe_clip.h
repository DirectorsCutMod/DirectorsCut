//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Clip data for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#ifndef _DIRECTORSCUT_DXE_CLIP_H_
#define _DIRECTORSCUT_DXE_CLIP_H_

#include "dxelement.h"
#include "dxe_timeframe.h"
#include "kvhelpers.h"

class DxeClip : public DxElement
{
public:
	DxeClip(const char* name);
	DxeClip(const char* name, const char* typeName);
	void InitElement() override;
	// Attributes
	DxeTimeFrame* GetTimeFrame() { return (DxeTimeFrame*)FindKey("timeFrame"); }
	void SetColorAttribute(Color color) { SetColor("color", color); }
	Color GetColorAttribute() { return GetColor("color"); }
	void SetText(const char* text) { SetString("text", text); }
	const char* GetText() { return GetString("text"); }
	void SetMute(bool mute) { SetBool("mute", mute); }
	bool GetMute() { return GetBool("mute"); }
	KvDxElementArray* GetTrackGroups() { return (KvDxElementArray*)FindKey("trackGroups"); }
	void SetDisplayScale(float scale) { SetFloat("displayScale", scale); }
	float GetDisplayScale() { return GetFloat("displayScale", 1.0f); }
};

#endif // _DIRECTORSCUT_DXE_CLIP_H_
