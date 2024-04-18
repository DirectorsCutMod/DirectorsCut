//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: User settings for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dxe_camera.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

DxeCamera::DxeCamera(const char* name) : DxeDag(name, "DxeCamera")
{
    InitElement();
};

DxeCamera::DxeCamera(const char* name, const char* typeName) : DxeDag(name, typeName)
{
    InitElement();
};

void DxeCamera::InitElement()
{
    DxElement::InitElement();
    // Initial values
    SetFieldOfView(30.0f);
    SetNearClip(3.0f);
    SetFarClip(28377.919921875f);
    SetFocalDistance(72.0f);
    SetZeroParallaxDistance(75.0f);
    SetEyeSeparation(0.75f);
    SetAperture(0.1999999881f);
    SetShutterSpeed(0.0208f);
    SetToneMapScale(1.0f);
    SetSSAOBias(0.0005f);
    SetSSAOStrength(1.0f);
    SetSSAORadius(15.0000009537);
    SetSSAOTint(Color(0, 0, 0, 255));
    SetBloomScale(0.2800000012f);
    SetDepthOfFieldQuality(0);
    SetMotionBlurQuality(0);
    SetBloomWidth(9.0f);
    SetOrtho(false);
    SetAxis(0);
    SetBehindFrustum(false);
    SetDistance(32.0f);
    SetScale0(1.0f);
    AddSubKey(new KvVector("lookat0"));
    SetScale1(1.0f);
    AddSubKey(new KvVector("lookat1"));
    SetScale2(1.0f);
    AddSubKey(new KvVector("lookat2"));
    SetScale3(1.0f);
    AddSubKey(new KvVector("lookat3"));
    SetScale4(1.0f);
    AddSubKey(new KvVector("lookat4"));
    SetScale5(1.0f);
    AddSubKey(new KvVector("lookat5"));
    // Factory attributes
    AddFactoryAttribute("fieldOfView");
    AddFactoryAttribute("znear");
    AddFactoryAttribute("zfar");
    AddFactoryAttribute("focalDistance");
    AddFactoryAttribute("zeroParallaxDistance");
    AddFactoryAttribute("eyeSeparation");
    AddFactoryAttribute("aperture");
    AddFactoryAttribute("shutterSpeed");
    AddFactoryAttribute("toneMapScale");
    AddFactoryAttribute("SSAOBias");
    AddFactoryAttribute("SSAOStrength");
    AddFactoryAttribute("SSAORadius");
    AddFactoryAttribute("SSAOTint");
    AddFactoryAttribute("bloomScale");
    AddFactoryAttribute("depthOfFieldQuality");
    AddFactoryAttribute("motionBlurQuality");
    AddFactoryAttribute("bloomWidth");
    AddFactoryAttribute("ortho");
    AddFactoryAttribute("axis");
    AddFactoryAttribute("behindFrustum");
    AddFactoryAttribute("distance");
    AddFactoryAttribute("scale0");
    AddFactoryAttribute("lookat0");
    AddFactoryAttribute("scale1");
    AddFactoryAttribute("lookat1");
    AddFactoryAttribute("scale2");
    AddFactoryAttribute("lookat2");
    AddFactoryAttribute("scale3");
    AddFactoryAttribute("lookat3");
    AddFactoryAttribute("scale4");
    AddFactoryAttribute("lookat4");
    AddFactoryAttribute("scale5");
    AddFactoryAttribute("lookat5");
}
