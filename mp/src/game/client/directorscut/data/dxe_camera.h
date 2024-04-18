//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: User settings for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#ifndef _DIRECTORSCUT_DXE_CAMERA_H_
#define _DIRECTORSCUT_DXE_CAMERA_H_

#include "dxelement.h"
#include "kvhelpers.h"
#include "dxe_dag.h"

class DxeCamera : public DxeDag
{
public:
    DxeCamera(const char* name);
    DxeCamera(const char* name, const char* typeName);
    void InitElement() override;
    // Attributes
    void SetFieldOfView(float fov) { SetFloat("fieldOfView", fov); }
    float GetFieldOfView() { return GetFloat("fieldOfView"); }
    void SetNearClip(float nearClip) { SetFloat("znear", nearClip); }
    float GetNearClip() { return GetFloat("znear"); }
    void SetFarClip(float farClip) { SetFloat("zfar", farClip); }
    float GetFarClip() { return GetFloat("zfar"); }
    void SetFocalDistance(float focalDistance) { SetFloat("focalDistance", focalDistance); }
    float GetFocalDistance() { return GetFloat("focalDistance"); }
    void SetZeroParallaxDistance(float zeroParallaxDistance) { SetFloat("zeroParallaxDistance", zeroParallaxDistance); }
    float GetZeroParallaxDistance() { return GetFloat("zeroParallaxDistance"); }
    void SetEyeSeparation(float eyeSeparation) { SetFloat("eyeSeparation", eyeSeparation); }
    float GetEyeSeparation() { return GetFloat("eyeSeparation"); }
    void SetAperture(float aperture) { SetFloat("aperture", aperture); }
    float GetAperture() { return GetFloat("aperture"); }
    void SetShutterSpeed(float shutterSpeed) { SetFloat("shutterSpeed", shutterSpeed); }
    float GetShutterSpeed() { return GetFloat("shutterSpeed"); }
    void SetToneMapScale(float toneMapScale) { SetFloat("toneMapScale", toneMapScale); }
    float GetToneMapScale() { return GetFloat("toneMapScale"); }
    void SetSSAOBias(float ssaoBias) { SetFloat("SSAOBias", ssaoBias); }
    float GetSSAOBias() { return GetFloat("SSAOBias"); }
    void SetSSAOStrength(float ssaoStrength) { SetFloat("SSAOStrength", ssaoStrength); }
    float GetSSAOStrength() { return GetFloat("SSAOStrength"); }
    void SetSSAORadius(float ssaoRadius) { SetFloat("SSAORadius", ssaoRadius); }
    float GetSSAORadius() { return GetFloat("SSAORadius"); }
    void SetSSAOTint(Color ssaoTint) { SetColor("SSAOTint", ssaoTint); }
    Color GetSSAOTint() { return GetColor("SSAOTint"); }
    void SetBloomScale(float bloomScale) { SetFloat("bloomScale", bloomScale); }
    float GetBloomScale() { return GetFloat("bloomScale"); }
    void SetDepthOfFieldQuality(int dofQuality) { SetInt("depthOfFieldQuality", dofQuality); }
    int GetDepthOfFieldQuality() { return GetInt("depthOfFieldQuality"); }
    void SetMotionBlurQuality(int motionBlurQuality) { SetInt("motionBlurQuality", motionBlurQuality); }
    int GetMotionBlurQuality() { return GetInt("motionBlurQuality"); }
    void SetBloomWidth(float bloomWidth) { SetFloat("bloomWidth", bloomWidth); }
    float GetBloomWidth() { return GetFloat("bloomWidth"); }
    void SetOrtho(bool ortho) { SetBool("ortho", ortho); }
    bool GetOrtho() { return GetBool("ortho"); }
    void SetAxis(int axis) { SetInt("axis", axis); }
    int GetAxis() { return GetInt("axis"); }
    void SetBehindFrustum(bool behindFrustum) { SetBool("behindFrustum", behindFrustum); }
    bool GetBehindFrustum() { return GetBool("behindFrustum"); }
    void SetDistance(float distance) { SetFloat("distance", distance); }
    float GetDistance() { return GetFloat("distance"); }
    void SetScale0(float scale0) { SetFloat("scale0", scale0); }
    float GetScale0() { return GetFloat("scale0"); }
    KvVector* GetLookAt0() { return (KvVector*)FindKey("lookat0"); }
    void SetScale1(float scale1) { SetFloat("scale1", scale1); }
    float GetScale1() { return GetFloat("scale1"); }
    KvVector* GetLookAt1() { return (KvVector*)FindKey("lookat1"); }
    void SetScale2(float scale2) { SetFloat("scale2", scale2); }
    float GetScale2() { return GetFloat("scale2"); }
    KvVector* GetLookAt2() { return (KvVector*)FindKey("lookat2"); }
    void SetScale3(float scale3) { SetFloat("scale3", scale3); }
    float GetScale3() { return GetFloat("scale3"); }
    KvVector* GetLookAt3() { return (KvVector*)FindKey("lookat3"); }
    void SetScale4(float scale4) { SetFloat("scale4", scale4); }
    float GetScale4() { return GetFloat("scale4"); }
    KvVector* GetLookAt4() { return (KvVector*)FindKey("lookat4"); }
    void SetScale5(float scale5) { SetFloat("scale5", scale5); }
    float GetScale5() { return GetFloat("scale5"); }
    KvVector* GetLookAt5() { return (KvVector*)FindKey("lookat5"); }
};

#endif // _DIRECTORSCUT_DXE_CAMERA_H_
