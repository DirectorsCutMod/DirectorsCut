//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Clip data for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#ifndef _DIRECTORSCUT_DXE_FILMCLIP_H_
#define _DIRECTORSCUT_DXE_FILMCLIP_H_

#include "dxe_clip.h"
#include "dxe_trackgroup.h"

class DxeFilmClip : public DxeClip
{
public:
	DxeFilmClip(const char* name);
	DxeFilmClip(const char* name, const char* typeName);
	void InitElement() override;
	// Attributes
	//DxeMaterialOverlayFXClip* GetMaterialOverlay() { return (DxeMaterialOverlayFXClip*)FindKey("materialOverlay"); }
	DxElement* GetMaterialOverlay() { return (DxElement*)FindKey("materialOverlay"); }
	void SetMapName(const char* mapName) { SetString("mapname", mapName); }
	const char* GetMapName() { return GetString("mapname"); }
	void SetActiveCamera(const char* activeCamera) { SetString("activeCamera", activeCamera); }
	const char* GetActiveCamera() { return GetString("activeCamera"); }
	KvDxElementArray* GetMonitorCameras() { return (KvDxElementArray*)FindKey("monitorCameras"); }
	void SetActiveMonitor(int activeMonitorCamera) { SetInt("activeMonitor", activeMonitorCamera); }
	int GetActiveMonitor() { return GetInt("activeMonitor", -1); }
	//DxeDag* GetScene() { return (DxeScene*)FindKey("scene"); }
	DxElement* GetScene() { return (DxElement*)FindKey("scene"); }
	void SetAviFile(const char* aviFile) { SetString("aviFile", aviFile); }
	const char* GetAviFile() { return GetString("aviFile"); }
	void SetFadeIn(float time) { SetFloat("fadeIn", time); }
	float GetFadeIn() { return GetFloat("fadeIn"); }
	void SetFadeOut(float time) { SetFloat("fadeOut", time); }
	float GetFadeOut() { return GetFloat("fadeOut"); }
	KvDxElementArray* GetInputs() { return (KvDxElementArray*)FindKey("inputs"); }
	KvDxElementArray* GetOperators() { return (KvDxElementArray*)FindKey("operators"); }
	void SetUseAviFile(bool useAviFile) { SetBool("useAviFile", useAviFile); }
	bool GetUseAviFile() { return GetBool("useAviFile"); }
	KvDxElementArray* GetAnimationSets() { return (KvDxElementArray*)FindKey("animationSets"); }
	KvDxElementArray* GetBookmarkSets() { return (KvDxElementArray*)FindKey("bookmarkSets"); }
	void SetActiveBookmarkSet(int activeBookmarkSet) { SetInt("activeBookmarkSet", activeBookmarkSet); }
	int GetActiveBookmarkSet() { return GetInt("activeBookmarkSet"); }
	DxeTrackGroup* GetSubClipTrackGroup() { return (DxeTrackGroup*)FindKey("subClipTrackGroup"); }
	void SetVolume(float volume) { SetFloat("volume", volume); }
	float GetVolume() { return GetFloat("volume"); }
	KvStringArray* GetConCommands() { return (KvStringArray*)FindKey("concommands"); }
	KvStringArray* GetConvars() { return (KvStringArray*)FindKey("convars"); }
};

#endif // _DIRECTORSCUT_DXE_FILMCLIP_H_
